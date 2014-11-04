#include "Label.h"

namespace RE_NAMESPACE {

	void Label::onRender(RenderEventArgument eventArgument) {
		FontManager::getInstance()->selectFont(_font);

		int nLen = MultiByteToWideChar(CP_ACP, 0, &_text[0], _text.size(), NULL, NULL);
		wstring text(nLen, 0);
		MultiByteToWideChar(CP_ACP, 0, &_text[0], _text.size(), &text[0], nLen);

		glPushMatrix();
		glPushAttrib(GL_ALL_ATTRIB_BITS);

		glColor3f(1, 0, 0);
		
		TEXTMETRIC textMetric;
		GetTextMetrics(OpenGL::_hdc, &textMetric);

		if (textMetric.tmAscent > 0)
			eventArgument.origin.y += textMetric.tmAscent;

		glTranslatef(eventArgument.origin.x, eventArgument.origin.y, 0.0f);
		glScalef((float) textMetric.tmHeight, (float) -textMetric.tmHeight, 0.0);

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