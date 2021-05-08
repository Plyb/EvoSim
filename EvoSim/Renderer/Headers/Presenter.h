#ifndef PRESENTER_H
#define PRESENTER_H

#include "Camera.h"
#include "Sprite.h"
#include "Timeline.h"
#include "../../Shared/Headers/WorldState.h"

class Presenter {
public:
	Presenter();

	void update();
	void setCamera(Camera* camera);

	// Sprites becomes a null terminated array of sprite pointers
	Sprite** getSprites(Sprite** sprites, unsigned int maxSprites);

private:
	Camera* camera;
	WorldState worldState;
	Timeline timeline;
};

#endif // !PRESENTER_H

