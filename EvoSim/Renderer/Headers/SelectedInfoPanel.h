#ifndef SELECTED_INFO_PANEL
#define SELECTED_INFO_PANEL

#include "RectangularUiElement.h"
#include "../../Shared/Headers/WorldState.h"

class SelectedInfoPanel : public RectangularUiElement {
public:
	SelectedInfoPanel(float x, float y, float w, float h);

	void setSelected(long long id);

	void insertSprites(Sprite** spriteArray) override;
	unsigned int getNumSprites() const override;

	void insertTextItems(TextItem** textItemArray) override;
	int getNumTextItems() const override;

	bool onClick() override;

	void update(WorldState* worldState) override;
private:
	long long selectedCreatureId = -1;
	CreatureState* selectedCreature = nullptr;
};

#endif // !SELECTED_INFO_PANEL

