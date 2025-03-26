#include "object.h"

using namespace trotir;

TROTIR_API VMObject::VMObject(VM *associatedVm) noexcept
	: associatedVm(associatedVm) {
}
