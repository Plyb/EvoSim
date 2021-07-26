#ifndef PRESENTER_H
#define PRESENTER_H

#include "Camera.h"
#include "Sprite.h"
#include "TextItem.h"
#include "BackgroundCell.h"
#include "Slider.h"
#include "SelectedInfoPanel.h"
#include "../../Shared/Headers/Timeline.h"

class Presenter {
public:
	Presenter(Camera* camera, Timeline* timeline);
	// TODO create a destructor

	void update();
	void processClicks();

	// become a null terminated array of pointers
	Sprite** getSprites(Sprite** sprites, unsigned int maxSprites);
	Sprite** getUi(Sprite** sprites, unsigned int maxSprites);
	TextItem** getTextItems(TextItem** textItems, unsigned int maxTextItems);

	// 2D array of backgound cells
	BackgroundCell** getBackground();

	bool isReady();

private:
	Camera* camera;
	WorldState* worldState = NULL;
	Timeline* timeline;
	BackgroundCell** background;

	std::vector<UiElement*> uiElements;
	Slider* timelineSlider;
	Slider* timeSpeedSlider;
	SelectedInfoPanel* selectedInfoPanel;

	bool batchGetTimelineData();
};

#endif // !PRESENTER_H

