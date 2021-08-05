#include "../Headers/Presenter.h"

#include "../Headers/Time.h"
#include "../Headers/Panel.h"
#include "../Headers/TimelineSlider.h"
#include "../Headers/TimeSpeedSlider.h"
#include "../Headers/SelectedInfoPanel.h"
#include "../Headers/Input.h"
#include "../../Shared/Headers/MethodCallback.h"
#include <sstream>
#include <iostream>

Presenter::Presenter(Camera* camera, Timeline* timeline) : camera(camera), timeline(timeline) {
	background = new BackgroundCell*[WorldState::WORLD_WIDTH];
	for (unsigned int i = 0; i < WorldState::WORLD_WIDTH; i++) {
		background[i] = new BackgroundCell[WorldState::WORLD_WIDTH];
	}

	timelineSlider = new TimelineSlider(50.0f, camera->getScreenHeight() - 80.0f, camera->getScreenWidth() - 100.0f, 10.0f, timeline);
	timeSpeedSlider = new TimeSpeedSlider(50.0f, camera->getScreenHeight() - 40.0f, 200.0f, 10.0f);
	selectedInfoPanel = new SelectedInfoPanel(camera->getScreenWidth() / 2.0f, 0.0f, camera->getScreenWidth() / 2.0f, 100.0f);

	uiElements.push_back(new Panel(0.0f, camera->getScreenHeight() - 100.0f, camera->getScreenWidth(), 100.0f));
	uiElements.push_back(timelineSlider);
	uiElements.push_back(timeSpeedSlider);
	uiElements.push_back(selectedInfoPanel);
}

void Presenter::update() {
	processClicks();
	camera->update();
	batchGetTimelineData();
	for (UiElement* uiElement : uiElements) {
		uiElement->update(worldState);
	}
	timelineSlider->setValue(Time::getFrames() / (float) timeline->getNumFramesAvailable());
}

void Presenter::processClicks() {
	if (Input::getMouseDown() > -1 || Input::getMouseUp() > -1) {
		bool uiHit = false;
		double mouseX, mouseY;
		Input::getMousePosition(&mouseX, &mouseY);
		for (int i = uiElements.size() - 1; i >= 0; i--) {
			if (uiElements.at(i)->onClick()) {
				uiHit = true;
				break;
			}
		}

		if (!uiHit) {
			bool creatureHit = false;
			for (std::pair<long long, CreatureState> entry : worldState->creatures) {
				CreatureState& creature = entry.second;
				glm::vec2 mouseWorldPos = camera->screenToWorld(mouseX, mouseY);
				if (creature.xpos < mouseWorldPos.x && creature.xpos + 1 > mouseWorldPos.x
						&& creature.ypos < mouseWorldPos.y && creature.ypos + 1 > mouseWorldPos.y) {
					if (Input::getMouseUp() > -1) { // TODO: move to dedicated creature presenter onClick method
						selectedInfoPanel->setSelected(creature.id);
					}
					creatureHit = true;
					break;
				}
			}

			if (!creatureHit) {
				selectedInfoPanel->setSelected(-1);
			}
		}
	}
}

Sprite** Presenter::getSprites(Sprite** sprites, unsigned int maxSprites) {
	unsigned int i = 0;
	for (std::pair<const long long, CreatureState>& entry : worldState->creatures) { // TODO: this should iterate through creatures, not use an index
		CreatureState& creature = entry.second;
		sprites[i] = new Sprite(
			"awesomeface.png",
			glm::vec2(creature.xpos * camera->pixelsPerUnit, creature.ypos * camera->pixelsPerUnit),
			creature.rot,
			glm::vec2(camera->pixelsPerUnit, camera->pixelsPerUnit),
			glm::vec3(creature.energy / 300.0f, creature.energy / 300.0f, creature.energy / 300.0f)
		);
		i++;
	}
	sprites[worldState->creatures.size()] = nullptr;
	return sprites;
}

Sprite** Presenter::getUi(Sprite** sprites, unsigned int maxSprites) {
	unsigned int spritesInserted = 0;
	for (UiElement* element : uiElements) {
		if (element->getNumSprites() + spritesInserted < maxSprites) {
			element->insertSprites(sprites + spritesInserted);
			spritesInserted += element->getNumSprites();
		}
		else {
			break;
		}
	}
	sprites[spritesInserted] = nullptr;
	return sprites;
}

TextItem** Presenter::getTextItems(TextItem** textItems, unsigned int maxTextItems) {
	std::stringstream numCreaturesTextStream;
	numCreaturesTextStream << "Creatures: " << worldState->creatures.size();

	TextItem* numCreatures = new TextItem(numCreaturesTextStream.str(), 5.0f, 5.0f, 1.0f);
	textItems[0] = numCreatures;
	
	unsigned int textItemsInserted = 1;
	for (UiElement* element : uiElements) {
		if (element->getNumTextItems() + textItemsInserted < maxTextItems) {
			element->insertTextItems(textItems + textItemsInserted);
			textItemsInserted += element->getNumTextItems();
		}
		else {
			break;
		}
	}

	textItems[textItemsInserted] = nullptr;

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

bool Presenter::batchGetTimelineData() {
	try {
		Timeline::Batch batch = Timeline::Batch(timeline);
		return batch.getStateAtFrame(Time::getFrames(), worldState);
	}
	catch (Timeline::Batch::AlreadyLockedException& ex) {
		return false;
	}
}