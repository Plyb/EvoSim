#include "../Headers/Presenter.h"

#include "../Headers/Time.h"

Sprite* tempSprites[] = { // TODO: this is temporary for testing
	new Sprite("awesomeface.png", glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(100.0f, 100.0f)),
	new Sprite("awesomeface.png", glm::vec2(200.0f, 0.0f), 0.0f, glm::vec2(100.0f, 100.0f)),
	new Sprite("awesomeface.png", glm::vec2(100.0f, 300.0f), 0.0f, glm::vec2(100.0f, 100.0f)),
	NULL
};

Presenter::Presenter(Camera* camera, Timeline* timeline) : camera(camera), timeline(timeline) {
	timeline->tryGetStateAtFrame(0, worldState);
}

void Presenter::update() {
	camera->update();
	timeline->tryGetStateAtFrame(Time::getFrames(), worldState);
}

Sprite** Presenter::getSprites(Sprite** sprites, unsigned int maxSprites) {
	for (unsigned int i = 0; i < worldState.numCreatures; ++i) {
		CreatureState creature = worldState.creatures[i];
		sprites[i] = new Sprite("awesomeface.png", glm::vec2(creature.xpos, creature.ypos), creature.rot, glm::vec2(100.0f, 100.0f));
	}
	sprites[worldState.numCreatures] = nullptr;
	return sprites;
}