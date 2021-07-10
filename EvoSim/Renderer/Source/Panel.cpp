#include "../Headers/Panel.h"
#include "../Headers/Input.h"

Panel::Panel(float x, float y, float height, float width, glm::vec3 color)
	: RectangularUiElement(x, y, height, width, color) {}

void Panel::onClick() {}

void Panel::insertSprites(Sprite** spriteArray) const {
	spriteArray[0] = basePanelSprite;
}

unsigned int Panel::getNumSprites() const {
	return 1;
}