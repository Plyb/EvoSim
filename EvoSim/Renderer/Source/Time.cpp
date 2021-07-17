#include "../Headers/Time.h"

#include <GLFW/glfw3.h>
#include <iostream>

float Time::deltaTime = 0.0f;
float Time::lastFrame = 0.0f;
unsigned int Time::basisFrame = 0;

void Time::start() {
	setBasisFrame(getFrames());
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
	return (int)(glfwGetTime() * FPS) - basisFrame;
}

void Time::setBasisFrame(unsigned int frame) {
	basisFrame = frame;
}