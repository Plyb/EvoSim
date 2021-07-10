#include "../Headers/Panel.h"
#include "../Headers/Input.h"

Panel::Panel(float x, float y, float height, float width, Camera* camera, glm::vec3 color) {
	sprite = new Sprite(
		"panel.png",
		glm::vec2(x, y),
		0.0f,
		glm::vec2(width, height),
		color
	);
}

void Panel::onClick() {
	sprite->color = glm::vec3(1.0f, 0.0f, 0.0f);
}

void Panel::insertSprites(Sprite** spriteArray) const {
	spriteArray[0] = sprite;
}

unsigned int Panel::getNumSprites() const {
	return 1;
}

bool Panel::clickHits() const {
	double mouseX, mouseY;
	Input::getMousePosition(&mouseX, &mouseY);
	return mouseX > sprite->position.x && mouseY < (double)sprite->position.x + sprite->scale.x
		&& mouseY > sprite->position.y && mouseY < (double)sprite->position.y + sprite->scale.y;
}