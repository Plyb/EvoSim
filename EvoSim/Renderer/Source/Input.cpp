#include "../Headers/Input.h"

bool Input::keys[Input::NUM_KEYS];
double Input::scroll = 0.0f;
double Input::scrollEvent = 0.0f;
double Input::mouseX = 0.0f;
double Input::mouseY = 0.0f;
int Input::mouseClick = -1;
int Input::mouseClickEvent = -1;
int Input::mouseUp = -1;
int Input::mouseUpEvent = -1;

void Input::update(GLFWwindow* window) {
	for (unsigned int i = 0; i < NUM_KEYS; i++) {
		keys[i] = glfwGetKey(window, i);
	}

	scroll = scrollEvent;
	scrollEvent = 0.0f;

	glfwGetCursorPos(window, &mouseX, &mouseY);
	mouseClick = mouseClickEvent;
	mouseClickEvent = -1;
	mouseUp = mouseUpEvent;
	mouseUpEvent = -1;
}

bool Input::getKey(int key) {
	return keys[key];
}

void Input::scrollCallback(double newScroll) {
	scrollEvent = newScroll;
}

void Input::mouseCallback(int button) {
	mouseClickEvent = button;
}

void Input::mouseUpCallback(int button) {
	mouseUpEvent = button;
}

double Input::getScroll() {
	return scroll;
}

int Input::getMouseClick() {
	return mouseClick;
}

int Input::getMouseUp() {
	return mouseUp;
}

void Input::getMousePosition(double* xpos, double* ypos) {
	*xpos = mouseX;
	*ypos = mouseY;
}