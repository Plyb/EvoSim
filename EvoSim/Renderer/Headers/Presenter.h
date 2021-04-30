#ifndef PRESENTER_H
#define PRESENTER_H

#include "Camera.h"
#include "Sprite.h"

class Presenter {
public:
	void update();
	void setCamera(Camera* camera);

	// Returns a null terminated array
	Sprite** getSprites();

private:
	Camera* camera;
};

#endif // !PRESENTER_H

