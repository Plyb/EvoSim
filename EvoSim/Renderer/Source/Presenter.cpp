#include "../Headers/Presenter.h"

Sprite* sprites[] = { // TODO: this is temporary for testing
	new Sprite("awesomeface.png", glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(100.0f, 100.0f)),
	new Sprite("awesomeface.png", glm::vec2(200.0f, 0.0f), 0.0f, glm::vec2(100.0f, 100.0f)),
	new Sprite("awesomeface.png", glm::vec2(100.0f, 300.0f), 0.0f, glm::vec2(100.0f, 100.0f)),
	NULL
};

void Presenter::update() {
	camera->update();
}

void Presenter::setCamera(Camera* camera) {
	this->camera = camera;
}

Sprite** Presenter::getSprites() {
	return sprites;
}