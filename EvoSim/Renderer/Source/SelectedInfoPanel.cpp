#include "../Headers/SelectedInfoPanel.h"

#include <stdexcept>
#include <sstream>

SelectedInfoPanel::SelectedInfoPanel(float x, float y, float w, float h) : RectangularUiElement(x, y, w, h) {}

void SelectedInfoPanel::insertSprites(Sprite** spriteArray) {
	if (selectedCreature != nullptr) {
		spriteArray[0] = basePanelSprite;
	}
}

unsigned int SelectedInfoPanel::getNumSprites() const {
	return selectedCreature != nullptr;
}

void SelectedInfoPanel::insertTextItems(TextItem** textItemArray) {
	if (selectedCreature != nullptr) {
		std::stringstream energyStream;
		energyStream << "Energy: " << std::to_string((int)selectedCreature->energy);

		textItemArray[0] = new TextItem(
			energyStream.str(),
			basePanelSprite->position.x + 10.0f,
			basePanelSprite->position.y + 10.0f,
			1.0f,
			glm::vec3(0.0f, 0.0f, 0.0f)
		);
	}
}

int SelectedInfoPanel::getNumTextItems() const {
	return selectedCreature != nullptr;
}

bool SelectedInfoPanel::onClick() {
	return clickHits();
}

void SelectedInfoPanel::setSelected(long long id) {
	selectedCreatureId = id;
}

void SelectedInfoPanel::update(WorldState* worldState) {
	if (selectedCreatureId == -1) {
		selectedCreature = nullptr;
	}
	else {
		try {
			selectedCreature = &worldState->creatures.at(selectedCreatureId);
		}
		catch (const std::out_of_range& oor) {
			// Keep the current selection
		}
	}
}