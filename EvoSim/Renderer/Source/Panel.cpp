#include "../Headers/Panel.h"

Panel::Panel(int x, int y, int height, int width, Camera* camera, glm::vec3 color) {
	sprite = new Sprite(
		"panel.png",
		glm::vec2(0, camera->getScreenHeight() - 100.0f),
		0.0f,
		glm::vec2(camera->getScreenWidth(), 100.0f),
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
	return true;
}