#include "../Headers/Renderer.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Headers/ResourceManager.h"
#include "../Headers/Time.h"
#include "../Headers/Input.h"
#include "../Headers/BackgroundCell.h"

/**
 * Much of this code is adapted from the OpenGL tutorials at learnopengl.com
 */

Renderer::Renderer(Timeline& timeline) {
    configureOpenGL();
    loadResources();
    presenter = new Presenter(&camera, &timeline);
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
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // OpenGL configuration
    // --------------------
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::loadResources() {
    ResourceManager::init();
    ResourceManager::setResourceRoot("Renderer/Resources/");

    ResourceManager::loadShader("sprite.vert", "sprite.frag", nullptr, "sprite");
    ResourceManager::loadShader("bg.vert", "bg.frag", nullptr, "bg");

    glm::mat4 transform = camera.getViewProjectionTransform();
    ResourceManager::getShader("sprite").use().set("image", 0, true);
    ResourceManager::getShader("sprite").set("projection", transform);
    ResourceManager::getShader("bg").set("projection", transform, true);

    Shader spriteShader = ResourceManager::getShader("sprite");
    Shader backgroundShader = ResourceManager::getShader("bg");
    spriteRenderer = new SpriteRenderer(spriteShader);
    backgroundRenderer = new BackgroundRenderer(backgroundShader);

    textRenderer = new TextRenderer(SCREEN_WIDTH, SCREEN_HEIGHT);
    textRenderer->Load("Renderer/Resources/OCRAEXT.TTF", 24); 
}

int Renderer::run() {
    while (!presenter->isReady()) {
        presenter->update();
    }
    Time::start();
    ResourceManager::loadTexture("panel.png", true, "panel.png");

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        Time::updateDeltaTime();

        Input::update(window);
        presenter->update();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
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
    renderBackground();
    renderSprites();
    renderUi();
    renderText();
}

void Renderer::renderBackground() {
    ResourceManager::getShader("bg").set("projection", camera.getViewProjectionTransform(), true);
    BackgroundCell** background = presenter->getBackground();
    backgroundRenderer->drawBackground(background);
}

void Renderer::renderSprites() {
    ResourceManager::getShader("sprite").set("projection", camera.getViewProjectionTransform(), true);

    Sprite* sprites[10000]; // TODO stack corruption occurs because this is too small. Will need to move to heap.
    presenter->getSprites(sprites, 10000);
    renderSpriteArray(sprites, true);
}

void Renderer::renderUi() {
    ResourceManager::getShader("sprite").set("projection", glm::ortho(0.0f, static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT), 0.0f), true);


    Sprite* sprites[10000]; // TODO stack corruption occurs because this is too small. Will need to move to heap.
    presenter->getUi(sprites, 10000);
    renderSpriteArray(sprites, false);
}

void Renderer::renderText() {
    TextItem* textItems[128];
    presenter->getTextItems(textItems, 128);

    for (unsigned int i = 0; textItems[i] != nullptr; ++i) {
        TextItem* textItem = textItems[i];
        textRenderer->RenderText(textItem->text, textItem->x, textItem->y, textItem->scale);
        delete textItem;
    }
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

void Renderer::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    Input::scrollCallback(yoffset);
}

void Renderer::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS) {
        Input::mouseCallback(button);
    }
    else if (action == GLFW_RELEASE) {
        Input::mouseUpCallback(button);
    }
}

void Renderer::renderSpriteArray(Sprite** sprites, bool deleteSprites) {
    for (unsigned int i = 0; sprites[i] != nullptr; ++i) {
        Sprite* sprite = sprites[i];
        Texture2D texture;
        try {
            // Possible optimization: create a sprite collection system that groups sprites by their image so we don't need to load it every time.
            // That or load all textures needed in loadResources
            texture = ResourceManager::getTexture(sprite->image);
        }
        catch (const std::out_of_range& ex) {
            texture = ResourceManager::loadTexture((sprite->image).c_str(), true, sprite->image);
        }

        spriteRenderer->drawSprite(texture, sprite->position, sprite->scale, sprite->rotation, sprite->color);
        if (deleteSprites) {
            delete sprite;
        }
    }
}