#include "../Headers/Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Headers/Time.h"

Camera::Camera(int screenWidth, int screenHeight) 
	: screenWidth(screenWidth), screenHeight(screenHeight) {
}

glm::mat4 Camera::getViewProjectionTransform() {
	const glm::vec3 lookPos = position + glm::vec3(0.0f, 0.0f, -1.0f);
	const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 viewTransform = glm::lookAt(position, lookPos, up);

	glm::mat4 projectionTransform = glm::ortho(0.0f, static_cast<float>(screenWidth), 0.0f, static_cast<float>(screenHeight), -1.0f, 1.0f);
	return projectionTransform * viewTransform;
}

void Camera::translate(float x, float y, bool fast) {
	float multiplier = fast ? FAST_MULTIPLIER: 1.0f;
	position += glm::normalize(glm::vec3(x, y, 0.0f)) * SPEED * multiplier * Time::getDeltaTime();
}