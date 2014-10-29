#pragma once
#include "Constant.h"
#include <stdio.h>

namespace RE_NAMESPACE {

	class Reference {
	private:
		int _referenceCounter;
	public:
		Reference();
		virtual ~Reference() {}
		void retain();
		void release();
	};

	inline Reference::Reference() : _referenceCounter(0) {

	}

}