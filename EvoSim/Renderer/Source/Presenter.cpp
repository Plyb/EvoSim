#include "../Headers/Presenter.h"

Sprite* tempSprites[] = { // TODO: this is temporary for testing
	new Sprite("awesomeface.png", glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(100.0f, 100.0f)),
	new Sprite("awesomeface.png", glm::vec2(200.0f, 0.0f), 0.0f, glm::vec2(100.0f, 100.0f)),
	new Sprite("awesomeface.png", glm::vec2(100.0f, 300.0f), 0.0f, glm::vec2(100.0f, 100.0f)),
	NULL
};

// TODO: this is temporary for testing
CreatureState creature1 = {
	0.0f, 0.0f, 0.0f
};

CreatureState creature2 = {
200.0f, 100.0f, 0.0f
};

CreatureState creature3 = {
100.0f, 300.0f, 0.0f
};

CreatureState states[] = {
	creature1,
	creature2,
	creature3
};

Presenter::Presenter() {
	worldState = {
		{ 
			states
		},
		{
			3
		}
	};
	camera = nullptr;
}

void Presenter::update() {
	camera->update();
}

void Presenter::setCamera(Camera* camera) {
	this->camera = camera;
}

Sprite** Presenter::getSprites(Sprite** sprites, unsigned int maxSprites) {
	for (unsigned int i = 0; i < worldState.numCreatures; ++i) {
		CreatureState creature = worldState.creatures[i];
		sprites[i] = new Sprite("awesomeface.png", glm::vec2(creature.xpos, creature.ypos), creature.rot, glm::vec2(100.0f, 100.0f));
	}
	sprites[worldState.numCreatures] = nullptr;
	return sprites;
}