#include "../Headers/Presenter.h"

#include "../Headers/Time.h"
#include <sstream>

Presenter::Presenter(Camera* camera, Timeline* timeline) : camera(camera), timeline(timeline) {
	Time::start();
	timeline->tryGetStateAtFrame(0, worldState);

	background = new BackgroundCell*[WorldState::WORLD_WIDTH];
	for (unsigned int i = 0; i < WorldState::WORLD_WIDTH; i++) {
		background[i] = new BackgroundCell[WorldState::WORLD_WIDTH];
	}
}

void Presenter::update() {
	camera->update();
	timeline->tryGetStateAtFrame(Time::getFrames(), worldState);
}

Sprite** Presenter::getSprites(Sprite** sprites, unsigned int maxSprites) {
	for (unsigned int i = 0; i < worldState->creatures.size(); ++i) {
		CreatureState creature = worldState->creatures[i];
		sprites[i] = new Sprite(
			"awesomeface.png",
			glm::vec2(creature.xpos * 100.0f, creature.ypos * 100.0f),
			creature.rot,
			glm::vec2(100.0f, 100.0f),
			glm::vec3(creature.energy / 300.0f, creature.energy / 300.0f, creature.energy / 300.0f)
		);
	}
	sprites[worldState->creatures.size()] = nullptr;
	return sprites;
}

TextItem** Presenter::getTextItems(TextItem** textItems, unsigned int maxTextItems) {
	std::stringstream numCreaturesTextStream;
	numCreaturesTextStream << "Creatures: " << worldState->creatures.size();

	TextItem* numCreatures = new TextItem();
	numCreatures->x = 5.0f;
	numCreatures->y = 5.0f;
	numCreatures->scale = 1.0f;
	numCreatures->text = numCreaturesTextStream.str();

	textItems[0] = numCreatures;
	textItems[1] = nullptr;
	return textItems;
}

BackgroundCell** Presenter::getBackground() {
	for (unsigned int x = 0; x < WorldState::WORLD_WIDTH; x++) {
		for (unsigned int y = 0; y < WorldState::WORLD_WIDTH; y++) {
			background[x][y].r = worldState->ground[x][y].food;
			background[x][y].g = worldState->ground[x][y].food;
			background[x][y].b = worldState->ground[x][y].food;
		}
	}
	return background;
}

bool Presenter::isReady() {
	return worldState != NULL;
}