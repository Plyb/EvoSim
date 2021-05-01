#include "../Headers/Presenter.h"

#include <atomic_queue/atomic_queue.h>

#define MAX_NUM_WORLD_STATES 1024
atomic_queue::AtomicQueue2<WorldState, MAX_NUM_WORLD_STATES> worldStateQueue;

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

CreatureState states2[] = {
	creature1,
	creature2
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
	WorldState worldState2 = {
		{
			states
		},
		{
			3
		}
	};
	worldState = {
		{
			states2
		},
		{
			2
		}
	};

	for (unsigned int i = 0; i < MAX_NUM_WORLD_STATES; i++) {
		if ((i / 10) % 2) {
			worldStateQueue.push(worldState);
		}
		else {
			worldStateQueue.push(worldState2);
		}
	}
	camera = nullptr;
}

void Presenter::update() {
	camera->update();
	worldStateQueue.try_pop(worldState);
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