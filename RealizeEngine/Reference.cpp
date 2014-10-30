#include "Reference.h"

namespace RE_NAMESPACE {

	void Reference::retain() {
		_referenceCounter++;
	}

	void Reference::release() {
		_referenceCounter--;

		if (_referenceCounter == 0) {
			delete this;
		}
	}

}