#ifndef PANEL_H
#define PANEL_H

#include "UiElement.h"
#include "Camera.h"

class Panel : public UiElement {
public:
	Panel(int x, int y, int height, int width, Camera* camera, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
	void onClick() override;
private:
};

#endif // !PANEL_H

