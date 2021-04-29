#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "SpriteRenderer.h"
#include "Camera.h"

class Renderer {
public:
	enum class Source {
		FILE,
		LIVE
	};

	Renderer(Renderer::Source source);

	int run();
private:
	const unsigned int SCREEN_WIDTH = 800;
	const unsigned int SCREEN_HEIGHT = 600;

	SpriteRenderer* spriteRenderer;
	GLFWwindow* window;
	Camera camera = Camera(SCREEN_WIDTH, SCREEN_HEIGHT);

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

	void configureOpenGL();
	void loadResources();
	void render();
	void processInput();
};

#endif