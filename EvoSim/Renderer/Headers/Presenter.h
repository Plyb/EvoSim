#ifndef PRESENTER_H
#define PRESENTER_H

#include "Camera.h"
#include "Sprite.h"
#include "../../Shared/Headers/Timeline.h"

class Presenter {
public:
	Presenter(Camera* camera, Timeline* timeline);

	void update();

	// Sprites becomes a null terminated array of sprite pointers
	Sprite** getSprites(Sprite** sprites, unsigned int maxSprites);

private:
	Camera* camera;
	WorldState worldState;
	Timeline* timeline;
};

#endif // !PRESENTER_H

