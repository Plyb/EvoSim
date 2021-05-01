#include "Renderer/Headers/Renderer.h"

#include <iostream>

int main() {
	// TODO: Choose render source based on the mode and run this in a separate thread
	Renderer renderer = Renderer(Renderer::Source::LIVE);
	renderer.run();
	return 0;
}