#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "SpriteRenderer.h"
#include "BackgroundRenderer.h"
#include "TextRenderer.h"
#include "Camera.h"
#include "Presenter.h"

class Renderer {
public:
	Renderer(Timeline& timeline);

	int run();
private:
	const unsigned int SCREEN_WIDTH = 800;
	const unsigned int SCREEN_HEIGHT = 600;

	SpriteRenderer* spriteRenderer;
	BackgroundRenderer* backgroundRenderer;
	TextRenderer* textRenderer;
	GLFWwindow* window;
	Camera camera = Camera(SCREEN_WIDTH, SCREEN_HEIGHT);
	Presenter* presenter;

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

	void configureOpenGL();
	void loadResources();
	void render();
	void renderSprites();
	void renderBackground();
	void renderUi();
	void renderText();
	void processInput();

	void renderSpriteArray(Sprite** sprites, bool deleteSprites);
};

#endif