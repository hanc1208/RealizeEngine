#include "Label.h"

namespace RE_NAMESPACE {

	void Label::onRender(RenderEventArgument eventArgument) {
		FontManager::getInstance()->selectFont(_font);

		int nLen = MultiByteToWideChar(CP_ACP, 0, &_text[0], _text.size(), NULL, NULL);
		wstring text(nLen, 0);
		MultiByteToWideChar(CP_ACP, 0, &_text[0], _text.size(), &text[0], nLen);

		glPushAttrib(GL_ALL_ATTRIB_BITS);
		
		TEXTMETRIC textMetric;
		GetTextMetrics(OpenGL::_hdc, &textMetric);

		if (textMetric.tmAscent > 0)
			eventArgument.origin.y += textMetric.tmAscent;

		glRasterPos2f(eventArgument.origin.x, eventArgument.origin.y);

		for (int i = 0; i < (int) text.size(); i++) {
			int glList = glGenLists(1);
			wglUseFontBitmapsW(OpenGL::_hdc, text[i], 1, glList);
			glCallList(glList);
			glDeleteLists(glList, 1);
		}

		glPopAttrib();
	}

}