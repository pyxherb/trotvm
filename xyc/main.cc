#include <xylo/ast.h>
#include <initializer_list>
#include <cstdio>

struct OptionMatchContext {
	const int argc;
	char ** const argv;
	int i;
	void *userData;
};

struct SingleArgOption;

typedef bool (*ArglessOptionCallback)(const OptionMatchContext &matchContext, const char *option);
typedef bool (*SingleArgOptionCallback)(const OptionMatchContext &matchContext, const char *option, const char *arg);
typedef bool (*CustomOptionCallback)(OptionMatchContext &matchContext, const char *option);
typedef bool (*FallbackOptionCallback)(OptionMatchContext &matchContext, const char *option);
typedef void (*RequireOptionArgCallback)(const OptionMatchContext &matchContext, const SingleArgOption &option);

struct ArglessOption {
	const char *name;
	ArglessOptionCallback callback;
};

struct SingleArgOption {
	const char *name;
	SingleArgOptionCallback callback;
};

struct CustomOption {
	const char *name;
	CustomOptionCallback callback;
};

using ArglessOptionMap = std::initializer_list<ArglessOption>;
using SingleArgOptionMap = std::initializer_list<SingleArgOption>;
using CustomOptionMap = std::initializer_list<CustomOption>;

struct CompiledOptionMap {
	peff::HashMap<std::string_view, const ArglessOption *> arglessOptions;
	peff::HashMap<std::string_view, const SingleArgOption *> singleArgOptions;
	peff::HashMap<std::string_view, const CustomOption *> customOptions;
	FallbackOptionCallback fallbackOptionCallback;
	RequireOptionArgCallback requireOptionArgCallback;

	XYLO_FORCEINLINE CompiledOptionMap(peff::Alloc *alloc, FallbackOptionCallback fallbackOptionCallback, RequireOptionArgCallback requireOptionArgCallback) noexcept : arglessOptions(alloc), singleArgOptions(alloc), customOptions(alloc), fallbackOptionCallback(fallbackOptionCallback) {}
};

[[nodiscard]] bool buildOptionMap(
	CompiledOptionMap &optionMapOut,
	const ArglessOptionMap &arglessOptions,
	const SingleArgOptionMap &singleArgOptions,
	const CustomOptionMap &customOptions) {
	for (const auto &i : arglessOptions) {
		if (!optionMapOut.arglessOptions.insert(std::string_view(i.name), &i)) {
			return false;
		}
	}

	for (const auto &i : singleArgOptions) {
		if (!optionMapOut.singleArgOptions.insert(std::string_view(i.name), &i)) {
			return false;
		}
	}

	for (const auto &i : customOptions) {
		if (!optionMapOut.customOptions.insert(std::string_view(i.name), &i)) {
			return false;
		}
	}

	return true;
}

[[nodiscard]] bool matchArgs(const CompiledOptionMap &optionMap, int argc, char **argv, void *userData) {
	OptionMatchContext matchContext = { argc, argv, 0, userData };
	for (int i = 1; i < argc; ++i) {
		if (auto it = optionMap.arglessOptions.find(std::string_view(argv[i])); it != optionMap.arglessOptions.end()) {
			if (!it.value()->callback(matchContext, argv[i])) {
				return false;
			}

			continue;
		}

		if (auto it = optionMap.singleArgOptions.find(std::string_view(argv[i])); it != optionMap.singleArgOptions.end()) {
			const char *opt = argv[i];
			if (++i == argc) {
				optionMap.requireOptionArgCallback(matchContext, *it.value());
				return false;
			}

			if (!it.value()->callback(matchContext, opt, argv[i])) {
				return false;
			}

			continue;
		}

		if (auto it = optionMap.customOptions.find(std::string_view(argv[i])); it != optionMap.customOptions.end()) {
			if (!it.value()->callback(matchContext, argv[i])) {
				return false;
			}

			continue;
		}

		if (!optionMap.fallbackOptionCallback(matchContext, argv[i])) {
			break;
		}
	}

	return true;
}

#define printError(fmt, ...) fprintf(stderr, "Error: " fmt, ##__VA_ARGS__)

const ArglessOptionMap g_arglessOptions = {

};

const SingleArgOptionMap g_singleArgOptions = {

};

const CustomOptionMap g_customOptions = {

};

const char *g_modFileName = nullptr;

int main(int argc, char *argv[]) {
	CompiledOptionMap optionMap(
		peff::getDefaultAlloc(),
		[](OptionMatchContext &matchContext, const char *option) -> bool {
			if (g_modFileName) {
				printError("Duplicated target file name");
				return false;
			}

			g_modFileName = option;

			return true;
		},
		[](const OptionMatchContext &matchContext, const SingleArgOption &option) {
			printError("Option `%s' requires more arguments", option.name);
		});

	if (!buildOptionMap(optionMap, g_arglessOptions, g_singleArgOptions, g_customOptions)) {
		printError("Out of memory");
		return ENOMEM;
	}

	if (!matchArgs(optionMap, argc, argv, nullptr)) {
		return EINVAL;
	}

	if (!g_modFileName) {
		printError("Missing target file name");
		return EINVAL;
	}

	return 0;
}
