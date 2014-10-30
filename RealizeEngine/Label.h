#pragma once
#include "Node.h"

namespace RE_NAMESPACE {

	class Label : public Node {
	private:
		string text;
	public:
		Label();

		void onRender(RenderEventArgument eventArgument) override;
	};

}