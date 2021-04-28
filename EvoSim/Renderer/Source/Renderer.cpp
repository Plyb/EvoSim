#include "../Headers/Renderer.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Headers/ResourceManager.h"

/**
 * Much of this code is adapted from the OpenGL tutorials at learnopengl.com
 */

Renderer::Renderer(Renderer::Source source) {
    configureOpenGL();
    loadResources();
	// TODO: The renderer will eventually need to use the source, but it currently doesn't
}

void Renderer::configureOpenGL() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false);

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        exit(1);
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // OpenGL configuration
    // --------------------
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::loadResources() {
    ResourceManager::setResourceRoot("Renderer/Resources/");

    ResourceManager::loadShader("sprite.vert", "sprite.frag", nullptr, "sprite");

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->SCREEN_WIDTH), static_cast<float>(this->SCREEN_HEIGHT), 0.0f, -1.0f, 1.0f);
    ResourceManager::getShader("sprite").use().set("image", 0);
    ResourceManager::getShader("sprite").set("projection", projection);

    Shader spriteShader = ResourceManager::getShader("sprite");
    spriteRenderer = new SpriteRenderer(spriteShader);

    ResourceManager::loadTexture("awesomeface.png", true, "face");
}

int Renderer::run() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        render();

        glfwSwapBuffers(window);
    }

    ResourceManager::clear();
    delete spriteRenderer;

    glfwTerminate();
    return 0;
}

void Renderer::render() {
    Texture2D faceTexture = ResourceManager::getTexture("face");
    spriteRenderer->drawSprite(faceTexture, glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Renderer::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void Renderer::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}