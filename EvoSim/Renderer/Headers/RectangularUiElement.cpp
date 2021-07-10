#include "../Headers/RectangularUiElement.h"

#include "../Headers/Input.h"

RectangularUiElement::RectangularUiElement(float x, float y, float height, float width, glm::vec3 color) {
	basePanelSprite = new Sprite(
		"panel.png",
		glm::vec2(x, y),
		0.0f,
		glm::vec2(width, height),
		color
	);
}

bool RectangularUiElement::clickHits() const {
	double mouseX, mouseY;
	Input::getMousePosition(&mouseX, &mouseY);
	return mouseX > basePanelSprite->position.x && mouseX < (double)basePanelSprite->position.x + basePanelSprite->scale.x
		&& mouseY > basePanelSprite->position.y && mouseY < (double)basePanelSprite->position.y + basePanelSprite->scale.y;
}