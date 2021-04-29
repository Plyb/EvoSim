#ifndef PRESENTER_H
#define PRESENTER_H

#include "Camera.h"

class Presenter {
public:
	void update();
	void setCamera(Camera* camera);

private:
	Camera* camera;
};

#endif // !PRESENTER_H

