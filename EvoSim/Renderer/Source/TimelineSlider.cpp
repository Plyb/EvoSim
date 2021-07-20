#include "../Headers/TimelineSlider.h"

#include "../Headers/Time.h"

TimelineSlider::TimelineSlider(float x, float y, float w, float h, Timeline* timeline) 
	: timeline(timeline), Slider(x, y, w, h) {}

void TimelineSlider::onSliderUpdated() {
	const unsigned int frame = timeline->getNumFramesAvailable() * getValue();
	Time::timeTravelTo(frame);
}