#include "object.h"

using namespace trotvm;

TROTVM_API VMObject::VMObject(VM *associatedVm) noexcept
	: associatedVm(associatedVm) {
}
