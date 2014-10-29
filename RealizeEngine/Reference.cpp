#include "Reference.h"

namespace RE_NAMESPACE {

	void Reference::retain() {
		_referenceCounter++;
		printf("retain  :: _referenceCounter = %d, %x", _referenceCounter, this);
	}

	void Reference::release() {
		_referenceCounter--;
		printf("release :: _referenceCounter = %d, %x", _referenceCounter, this);

		if (_referenceCounter == 0) {
			delete this;
		}
	}

}