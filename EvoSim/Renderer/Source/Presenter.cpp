#include "../Headers/Presenter.h"

#include "../Headers/Time.h"

Presenter::Presenter(Camera* camera, Timeline* timeline) : camera(camera), timeline(timeline) {
	Time::start();
	timeline->tryGetStateAtFrame(0, worldState);
}

void Presenter::update() {
	camera->update();
	timeline->tryGetStateAtFrame(Time::getFrames(), worldState);
}

Sprite** Presenter::getSprites(Sprite** sprites, unsigned int maxSprites) {
	for (unsigned int i = 0; i < worldState.creatures.size(); ++i) {
		CreatureState creature = worldState.creatures[i];
		sprites[i] = new Sprite("awesomeface.png", glm::vec2(creature.xpos, creature.ypos), creature.rot, glm::vec2(100.0f, 100.0f));
	}
	sprites[worldState.creatures.size()] = nullptr;
	return sprites;
}