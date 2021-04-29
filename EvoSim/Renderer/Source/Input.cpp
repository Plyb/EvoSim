#include "../Headers/Input.h"

bool Input::keys[Input::NUM_KEYS];

void Input::update(GLFWwindow* window) {
	for (unsigned int i = 0; i < NUM_KEYS; i++) {
		keys[i] = glfwGetKey(window, i);
	}
}

bool Input::getKey(int key) {
	return keys[key];
}