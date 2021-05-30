#ifndef PRESENTER_H
#define PRESENTER_H

#include "Camera.h"
#include "Sprite.h"
#include "BackgroundCell.h"
#include "../../Shared/Headers/Timeline.h"

class Presenter {
public:
	Presenter(Camera* camera, Timeline* timeline);
	// TODO create a destructor

	void update();

	// Sprites becomes a null terminated array of sprite pointers
	Sprite** getSprites(Sprite** sprites, unsigned int maxSprites);

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

