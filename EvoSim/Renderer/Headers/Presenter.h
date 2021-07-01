#ifndef PRESENTER_H
#define PRESENTER_H

#include "Camera.h"
#include "Sprite.h"
#include "TextItem.h"
#include "BackgroundCell.h"
#include "../../Shared/Headers/Timeline.h"

class Presenter {
public:
	Presenter(Camera* camera, Timeline* timeline);
	// TODO create a destructor

	void update();

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
};

#endif // !PRESENTER_H

