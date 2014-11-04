#include "Label.h"

namespace RE_NAMESPACE {

	void Label::onRender(RenderEventArgument eventArgument) {
		Node::onRender(eventArgument);

		FontManager::getInstance()->selectFont(_font);

		int nLen = MultiByteToWideChar(CP_ACP, 0, &_text[0], _text.size(), NULL, NULL);
		wstring text(nLen, 0);
		MultiByteToWideChar(CP_ACP, 0, &_text[0], _text.size(), &text[0], nLen);

		glPushMatrix();
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		
		TEXTMETRIC textMetric;
		GetTextMetrics(OpenGL::_hdc, &textMetric);

		if (textMetric.tmAscent > 0)
			eventArgument.origin.y += textMetric.tmAscent;

		SIZE size;
		GetTextExtentPoint32W(OpenGL::_hdc, text.c_str(), nLen, &size);

		switch (_textHAlignment) {
		case TextHAlignment::LEFT:
			break;
		case TextHAlignment::CENTER:
			eventArgument.origin.x += (this->getWidth() - size.cx) / 2;
			break;
		case TextHAlignment::RIGHT:
			eventArgument.origin.x += this->getWidth() - size.cx;
			break;
		}

		switch (_textVAlignment) {
		case TextVAlignment::TOP:
			break;
		case TextVAlignment::CENTER:
			eventArgument.origin.y += (this->getHeight() - textMetric.tmHeight) / 2;
			break;
		case TextVAlignment::BOTTOM:
			eventArgument.origin.y += this->getHeight() - textMetric.tmHeight;
			break;
		}

		glTranslatef(eventArgument.origin.x, eventArgument.origin.y, 0.0f);
		glScalef((float) textMetric.tmHeight, (float) -textMetric.tmHeight, 0.0);

		glColor4f(_fontColor.red, _fontColor.green, _fontColor.blue, _fontColor.alpha);

		for (int i = 0; i < (int) text.size(); i++) {
			int glList = glGenLists(1);
			//wglUseFontBitmapsW(OpenGL::_hdc, text[i], 1, glList);
			wglUseFontOutlinesW(OpenGL::_hdc, text[i], 1, glList, 0.0f, 0.0f, WGL_FONT_POLYGONS, 0);
			glCallList(glList);
			glDeleteLists(glList, 1);
		}

		glPopAttrib();
		glPopMatrix();
	}

}