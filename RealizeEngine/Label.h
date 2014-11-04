#pragma once
#include "Node.h"
#include "FontManager.h"

namespace RE_NAMESPACE {

	enum class TextHAlignment {
		LEFT, CENTER, RIGHT
	};

	enum class TextVAlignment {
		TOP, CENTER, BOTTOM
	};

	class Label : public Node {
	private:
		string _text;
		string _font;
		Color _fontColor;
		TextHAlignment _textHAlignment;
		TextVAlignment _textVAlignment;
	public:
		Label(string text = "", string font = "");

		Color getFontColor() const;
		void setFontColor(Color fontColor);
		TextHAlignment getTextHAlignment() const;
		void setTextHAlignment(TextHAlignment textHAlignment);
		TextVAlignment getTextVAlignment() const;
		void setTextVAlignment(TextVAlignment textVAlignment);

		void onRender(RenderEventArgument eventArgument) override;
	};

	inline Label::Label(string text, string font) : _text(text), _font(font), _fontColor(Color(0.0f, 0.0f, 0.0f)), _textHAlignment(TextHAlignment::LEFT), _textVAlignment(TextVAlignment::TOP) {

	}

	inline Color Label::getFontColor() const {
		return _fontColor;
	}

	inline void Label::setFontColor(Color fontColor) {
		_fontColor = fontColor;
	}

	inline TextHAlignment Label::getTextHAlignment() const {
		return _textHAlignment;
	}

	inline void Label::setTextHAlignment(TextHAlignment textHAlignment) {
		_textHAlignment = textHAlignment;
	}

	inline TextVAlignment Label::getTextVAlignment() const {
		return _textVAlignment;
	}

	inline void Label::setTextVAlignment(TextVAlignment textVAlignment) {
		_textVAlignment = textVAlignment;
	}

}