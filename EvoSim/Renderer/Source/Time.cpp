#include "../Headers/Time.h"

#include <GLFW/glfw3.h>
#include <iostream>

float Time::deltaTime = 0.0f;
float Time::lastFrame = 0.0f;
float Time::startTime = glfwGetTime();

void Time::start() {
	startTime = glfwGetTime();
}

void Time::updateDeltaTime() {
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

float Time::getDeltaTime() {
	return deltaTime;
}

int Time::getFrames() {
	return (int)(glfwGetTime() * FPS);
}