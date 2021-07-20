#include "../Headers/TimeSpeedSlider.h"

#include "../Headers/Time.h"

TimeSpeedSlider::TimeSpeedSlider(float x, float y, float w, float h) : Slider(x, y, w, h) {
	const float defaultSpeedValue = (log(2.0f) / log(BASE)) / EXPONENT;
	setValue(defaultSpeedValue);
}

void TimeSpeedSlider::onSliderUpdated() {
	const float newSpeed = pow(BASE, getValue() * EXPONENT) - 1.0f;
	Time::setSpeed(newSpeed);
}