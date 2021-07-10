#include "../Headers/Slider.h"

#include "../Headers/Input.h"

Slider::Slider(float x, float y, float height, float width) 
		: RectangularUiElement(x, y, height, width, glm::vec3(0.9f, 0.9f, 0.9f)) {
	handleSprite = new Sprite(
		"panel.png", 
		glm::vec2(x, y),
		45.0f, 
		glm::vec2(height, height), 
		glm::vec3(0.5f, 0.5f, 0.5f)
	);
	handlePos = x;
}

void Slider::onClick() {
	double mouseX, mouseY;
	Input::getMousePosition(&mouseX, &mouseY);
	handlePos = mouseX - handleSprite->scale.y / 2;
}

void Slider::insertSprites(Sprite** spriteArray) const {
	handleSprite->position.x = handlePos;
	spriteArray[0] = basePanelSprite;
	spriteArray[1] = handleSprite;
}

unsigned int Slider::getNumSprites() const
{
    return 2;
}
