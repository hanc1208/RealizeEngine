#pragma once
#include "Node.h"
#include "FontManager.h"

namespace RE_NAMESPACE {

	class Label : public Node {
	private:
		string _text;
		string _font;
	public:
		Label(string text = "", string font = "");

		void onRender(RenderEventArgument eventArgument) override;
	};

	inline Label::Label(string text, string font) : _text(text), _font(font) {

	}

}