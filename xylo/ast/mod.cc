#include "mod.h"

using namespace xylo;

void Module::onRefZero() noexcept {
	peff::destroyAndRelease<Module>(selfAllocator.get(), this, sizeof(std::max_align_t));
}
