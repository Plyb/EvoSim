#include "../Headers/Input.h"

bool Input::keys[Input::NUM_KEYS];
double Input::scroll = 0.0f;
double Input::scrollEvent = 0.0f;

void Input::update(GLFWwindow* window) {
	for (unsigned int i = 0; i < NUM_KEYS; i++) {
		keys[i] = glfwGetKey(window, i);
	}

	scroll = scrollEvent;
	scrollEvent = 0.0f;
}

bool Input::getKey(int key) {
	return keys[key];
}

void Input::scrollCallback(double newScroll) {
	scrollEvent = newScroll;
}

double Input::getScroll() {
	return scroll;
}