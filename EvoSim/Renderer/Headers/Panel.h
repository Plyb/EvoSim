#ifndef PANEL_H
#define PANEL_H

#include "UiElement.h"
#include "Camera.h"

class Panel : public UiElement {
public:
	Panel(float x, float y, float height, float width, Camera* camera, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
	void onClick() override;
	void insertSprites(Sprite** spriteArray) const override;
	unsigned int getNumSprites() const override;
	bool clickHits() const override;
private:
	Sprite* sprite;
};

#endif // !PANEL_H

