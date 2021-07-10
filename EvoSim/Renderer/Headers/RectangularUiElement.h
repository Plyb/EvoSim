#ifndef RECTANGULAR_UI_ELEMENT_H
#define RECTANGULAR_UI_ELEMENT_H

#include "UiElement.h"

class RectangularUiElement : public UiElement {
public:
	RectangularUiElement(float x, float y, float height, float width, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
protected:
	virtual bool clickHits() const override;
	Sprite* basePanelSprite;
};

#endif // !RECTANGULAR_UI_ELEMENT_H

