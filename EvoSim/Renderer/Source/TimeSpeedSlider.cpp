#include "../Headers/TimeSpeedSlider.h"

#include "../Headers/Time.h"

TimeSpeedSlider::TimeSpeedSlider(float x, float y, float w, float h) : Slider(x, y, w, h) {
	DEFAULT_SPEED_VALUE = (log(2.0f) / log(BASE)) / EXPONENT;
	setValue(DEFAULT_SPEED_VALUE);
}

void TimeSpeedSlider::onSliderUpdated() {
	const float newSpeed = getSpeed(getValue());
	Time::setSpeed(newSpeed);
}

void TimeSpeedSlider::insertTextItems(TextItem** textItemArray) {
	textItemArray[0] = new TextItem(
		"0",
		basePanelSprite->position.x,
		basePanelSprite->position.y + 15.0f,
		1.0f,
		glm::vec3(0.0f, 0.0f, 0.0f),
		true
	);

	const int maxSpeed = (int)(getSpeed(1.0f) + 0.5f);
	textItemArray[1] = new TextItem(
		std::to_string(maxSpeed),
		basePanelSprite->position.x + basePanelSprite->scale.x,
		basePanelSprite->position.y + 15.0f,
		1.0f,
		glm::vec3(0.0f, 0.0f, 0.0f),
		true
	);

	textItemArray[2] = new TextItem(
		"1",
		basePanelSprite->position.x + basePanelSprite->scale.x * DEFAULT_SPEED_VALUE,
		basePanelSprite->position.y + 15.0f,
		1.0f,
		glm::vec3(0.0f, 0.0f, 0.0f),
		true
	);
}

int TimeSpeedSlider::getNumTextItems() const {
	return 3;
}

float TimeSpeedSlider::getSpeed(float sliderPos) {
	return pow(BASE, sliderPos * EXPONENT) - 1.0f;
}