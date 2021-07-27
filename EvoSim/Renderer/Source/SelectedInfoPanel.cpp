#include "../Headers/SelectedInfoPanel.h"

#include <stdexcept>

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

}

int SelectedInfoPanel::getNumTextItems() const {
	return 0;
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
			selectedCreature = nullptr;
		}
	}
}