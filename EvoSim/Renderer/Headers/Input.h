#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

class Input {
public:
	static void update(GLFWwindow* window);
	static bool getKey(int key);
private:
	static const int NUM_KEYS = 1024;
	static bool keys[NUM_KEYS];
};

#endif // !INPUT_H