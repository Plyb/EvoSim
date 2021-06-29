#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <map>

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
	const float ZOOM_SPEED = 1.1f;
	// moves the camera in a direction. Normalizes the direction vector
	void translate(glm::vec2 direction, bool fast = false);
	void zoom(double amount);
	void processInput();

	struct {
		glm::vec2 up = glm::vec2(0.0f, 1.0f);
		glm::vec2 down = glm::vec2(0.0f, -1.0f);
		glm::vec2 left = glm::vec2(-1.0f, 0.0f);
		glm::vec2 right = glm::vec2(1.0f, 0.0f);
	} directions;

	const std::map<int, glm::vec2> movementKeyMap = {
		{GLFW_KEY_W, directions.up},
		{GLFW_KEY_S, directions.down},
		{GLFW_KEY_A, directions.left},
		{GLFW_KEY_D, directions.right},
		{GLFW_KEY_UP, directions.up},
		{GLFW_KEY_DOWN, directions.down},
		{GLFW_KEY_LEFT, directions.left},
		{GLFW_KEY_RIGHT, directions.right},
	};
};

#endif // !CAMERA_H
