#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

class Input {
public:
	static void update(GLFWwindow* window);
	static bool getKey(int key);
	static double getScroll();

	static void scrollCallback(double scroll);
private:
	static const int NUM_KEYS = 1024;
	static bool keys[NUM_KEYS];
	static double scroll;
	static double scrollEvent;
};

#endif // !INPUT_H