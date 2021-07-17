#include "../Headers/Slider.h"

#include "../Headers/Input.h"

Slider::Slider(float x, float y, float height, float width) 
		: RectangularUiElement(x, y, height, width, glm::vec3(0.9f, 0.9f, 0.9f)) {
	handleSprite = new Sprite(
		"panel.png", 
		glm::vec2(x, y),
		45.0f, 
		glm::vec2(height, height), 
		glm::vec3(0.5f, 0.5f, 0.5f)
	);
	handlePos = x;
}

bool Slider::onClick() {
	if (clickHits() && Input::getMouseDown() == GLFW_MOUSE_BUTTON_LEFT) {
		dragging = true;
		return true;
	}

	if (Input::getMouseUp() == GLFW_MOUSE_BUTTON_LEFT) {
		dragging = false;
		updateHandlePos();
		for (Listener* listener : listeners) {
			listener->onSliderUpdated(this);
		}
	}

	return false;
}

void Slider::insertSprites(Sprite** spriteArray) {
	updateHandlePos();
	handleSprite->position.x = handlePos;
	spriteArray[0] = basePanelSprite;
	spriteArray[1] = handleSprite;
}

unsigned int Slider::getNumSprites() const {
    return 2;
}

float Slider::getValue() const {
	const float handleCenter = handlePos + handleSprite->scale.y / 2;
	return (handleCenter - basePanelSprite->position.x) / basePanelSprite->scale.x;
}

void Slider::setValue(float value) {
	const float handleMid = basePanelSprite->position.x + basePanelSprite->scale.x * value;
	handlePos = handleMid - handleSprite->scale.x / 2;
}

void Slider::registerListener(Listener* listener) {
	listeners.push_back(listener);
}

void Slider::updateHandlePos() {
	if (dragging) {
		double mouseX, mouseY;
		Input::getMousePosition(&mouseX, &mouseY);
		if (mouseX < basePanelSprite->position.x) {
			handlePos = basePanelSprite->position.x;
		}
		else if (mouseX > basePanelSprite->position.x + basePanelSprite->scale.x) {
			handlePos = basePanelSprite->position.x + basePanelSprite->scale.x;
		}
		else {
			handlePos = mouseX;
		}
		handlePos -= handleSprite->scale.y / 2;
	}
}