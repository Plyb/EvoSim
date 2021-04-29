#include "../Headers/Presenter.h"


void Presenter::update() {
	camera->update();
}

void Presenter::setCamera(Camera* camera) {
	this->camera = camera;
}