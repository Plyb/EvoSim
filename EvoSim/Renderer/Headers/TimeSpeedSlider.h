#ifndef TIME_SPEED_SLIDER_H
#define TIME_SPEED_SLIDER_H

#include "slider.h"

class TimeSpeedSlider : public Slider {
public:
	TimeSpeedSlider(float x, float y, float w, float h);

	void insertTextItems(TextItem** textItemArray) override;
	int getNumTextItems() const override;
private:
	void onSliderUpdated() override;
	float getSpeed(float sliderPos);

	const float BASE = 2.0f;
	const float EXPONENT = 5.0f;
	float DEFAULT_SPEED_VALUE;
};
#endif // !TIME_SPEED_SLIDER_H

