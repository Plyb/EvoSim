#include "../Headers/Panel.h"
#include "../Headers/Input.h"

Panel::Panel(float x, float y, float height, float width, glm::vec3 color)
	: RectangularUiElement(x, y, height, width, color) {}

bool Panel::onClick() {
	return Input::getMouseDown() == GLFW_MOUSE_BUTTON_LEFT;
}

void Panel::insertSprites(Sprite** spriteArray) {
	spriteArray[0] = basePanelSprite;
}

unsigned int Panel::getNumSprites() const {
	return 1;
}