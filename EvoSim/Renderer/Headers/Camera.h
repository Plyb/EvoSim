#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera {
public:
	Camera(int screenWidth, int screenHeight);
	glm::mat4 getViewProjectionTransform();
	
	void update();
private:
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 1.0f);
	float scale = 1.0f;
	int screenWidth, screenHeight;

	const float SPEED = 500.0f;
	const float FAST_MULTIPLIER = 10.0f;
	// moves the camera in a direction. Normalizes the direction vector
	void translate(float x, float y, bool fast = false);
	void processInput();
};

#endif // !CAMERA_H
