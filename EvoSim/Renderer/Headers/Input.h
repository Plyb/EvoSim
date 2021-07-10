#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

class Input {
public:
	static void update(GLFWwindow* window);
	static bool getKey(int key);
	static double getScroll();
	static int getMouseClick();
	static int getMouseUp();
	static void getMousePosition(double* xpos, double* ypos);

	static void scrollCallback(double scroll);
	static void mouseCallback(int button);
	static void mouseUpCallback(int button);
private:
	static const int NUM_KEYS = 1024;
	static bool keys[NUM_KEYS];
	static double scroll;
	static double scrollEvent;

	static double mouseX, mouseY;
	static int mouseClick;
	static int mouseClickEvent;
	static int mouseUp;
	static int mouseUpEvent;
};

#endif // !INPUT_H