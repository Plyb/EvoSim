#ifndef PANEL_H
#define PANEL_H

#include "RectangularUiElement.h"
#include "Camera.h"

class Panel : public RectangularUiElement {
public:
	Panel(float x, float y, float height, float width, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
	void onClick() override;
	void insertSprites(Sprite** spriteArray) override;
	unsigned int getNumSprites() const override;
};

#endif // !PANEL_H

