#include "../Headers/Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Headers/Time.h"
#include "../Headers/Input.h"

Camera::Camera(int screenWidth, int screenHeight) 
	: screenWidth(screenWidth), screenHeight(screenHeight) {
}

void Camera::update() {
    processInput();
}

glm::mat4 Camera::getViewProjectionTransform() {
	const glm::vec3 lookPos = position + glm::vec3(0.0f, 0.0f, -1.0f);
	const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 viewTransform = glm::lookAt(position, lookPos, up);

	glm::mat4 projectionTransform = glm::ortho(
		static_cast<float>(screenWidth * -0.5f / scale), 
		static_cast<float>(screenWidth * 0.5f / scale), 
		static_cast<float>(screenHeight * -0.5f / scale),
		static_cast<float>(screenHeight * 0.5f / scale), 
		-1.0f, 
		1.0f);
	return projectionTransform * viewTransform;
}

glm::vec2 Camera::screenToWorld(double screenX, double screenY) const {
	return glm::vec2((screenX - screenWidth / 2.0f) / scale + position.x, (screenHeight / 2.0f - screenY) / scale + position.y) / pixelsPerUnit;
}

void Camera::translate(glm::vec2 direction, bool fast) {
	float multiplier = (fast ? FAST_MULTIPLIER : 1.0f) / scale;
	position += glm::normalize(glm::vec3(direction, 0.0f)) * SPEED * multiplier * Time::getDeltaTime();
}

void Camera::zoom(double amount) {
	double multiplier = pow(ZOOM_SPEED, amount);
	scale *= multiplier;
}

void Camera::processInput() {
    bool shiftHeld = false;
    if (Input::getKey(GLFW_KEY_LEFT_SHIFT)) {
        shiftHeld = true;
    }
	for (std::map<int, glm::vec2>::const_iterator iter = movementKeyMap.begin(); iter != movementKeyMap.end(); iter++) {
		if (Input::getKey(iter->first)) {
			translate(iter->second, shiftHeld);
		}
	}

	if (Input::getScroll()) {
		zoom(Input::getScroll());
	}
}

int Camera::getScreenWidth() {
	return screenWidth;
}

int Camera::getScreenHeight() {
	return screenHeight;
}