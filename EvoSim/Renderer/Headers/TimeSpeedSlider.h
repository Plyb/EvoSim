#ifndef TIME_SPEED_SLIDER_H
#define TIME_SPEED_SLIDER_H

#include "slider.h"

class TimeSpeedSlider : public Slider {
public:
	TimeSpeedSlider(float x, float y, float w, float h);
private:
	void onSliderUpdated() override;

	const float BASE = 2.0f;
	const float EXPONENT = 5.0f;
};
#endif // !TIME_SPEED_SLIDER_H

