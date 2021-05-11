#include "Renderer/Headers/Renderer.h"
#include "Shared/Headers/Timeline.h"

#include <iostream>

int main() {
	Timeline timeline; //TODO make subclasses depending on the mode


	// TODO: Run this in a separate thread
	Renderer renderer = Renderer(timeline);
	renderer.run();
	return 0;
}