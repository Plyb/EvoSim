#include "../Headers/Time.h"

#include <GLFW/glfw3.h>
#include <iostream>

float Time::deltaTime = 0.0f;
float Time::lastFrame = 0.0f;
double Time::anchor = 0.0f;
unsigned int Time::offset = 0;
double Time::speed = 1.0f;


void Time::start() {
	anchor = glfwGetTime();
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
	return (int)((glfwGetTime() - anchor) * FPS * speed) + offset;
}

int Time::getFps() {
	return FPS;
}

void Time::timeTravelTo(unsigned int frame) {
	anchor = glfwGetTime();
	offset = frame;
}

void Time::setSpeed(double speed) {
	timeTravelTo(getFrames());
	Time::speed = speed;
}