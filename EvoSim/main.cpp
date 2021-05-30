#include "Renderer/Headers/Renderer.h"
#include "Shared/Headers/Timeline.h"
#include "Simulator/Simulator.h"

#include <iostream>
#include <Windows.h>


unsigned int __stdcall renderThread(void* timelinePtr);
unsigned int __stdcall simulateThread(void* timelinePtr);

int main() {
	Timeline timeline; //TODO make subclasses depending on the mode

	HANDLE renderHandle = (HANDLE)_beginthreadex(0, 0, &renderThread, &timeline, 0, 0);
	if (renderHandle == 0) {
		std::cerr << "There was an error creating the render thread" << std::endl;
		return -1;
	}
	SetThreadPriority(renderHandle, THREAD_PRIORITY_HIGHEST);

	HANDLE simulateHandle = (HANDLE)_beginthreadex(0, 0, &simulateThread, &timeline, 0, 0);
	if (simulateHandle == 0) {
		std::cerr << "There was an error creating the simulate thread" << std::endl;
		return -1;
	}
	SetThreadPriority(simulateHandle, THREAD_PRIORITY_IDLE);

	WaitForSingleObject(renderHandle, INFINITE);
	WaitForSingleObject(simulateHandle, INFINITE);
	return 0;
}

unsigned int __stdcall renderThread(void* timelinePtr) {
	Timeline& timeline = *((Timeline*)timelinePtr);

	Renderer renderer = Renderer(timeline);
	renderer.run();
	return 0;
}

unsigned int __stdcall simulateThread(void* timelinePtr) {
	Timeline& timeline = *((Timeline*)timelinePtr);

	Simulator simulator(timeline);
	simulator.run();
	return 0;
}