#ifndef TIMELINE_SLIDER_H
#define TIMELINE_SLIDER_H

#include "Slider.h"
#include "../../Shared/Headers/Timeline.h"

class TimelineSlider : public Slider {
public:
	TimelineSlider(float x, float y, float w, float h, Timeline* timeline);
private:
	void onSliderUpdated() override;

	Timeline* timeline;
};

#endif // !TIMELINE_SLIDER_H
