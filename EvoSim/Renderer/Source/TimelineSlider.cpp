#include "../Headers/TimelineSlider.h"

#include "../Headers/Time.h"

TimelineSlider::TimelineSlider(float x, float y, float w, float h, Timeline* timeline) 
	: timeline(timeline), Slider(x, y, w, h) {}

void TimelineSlider::onSliderUpdated() {
	const unsigned int frame = timeline->getNumFramesAvailable() * getValue();
	Time::timeTravelTo(frame);
}

void TimelineSlider::insertTextItems(TextItem** textItemArray) {
	textItemArray[0] = new TextItem(
		"0", 
		basePanelSprite->position.x, 
		basePanelSprite->position.y + 15.0f, 
		1.0f, 
		glm::vec3(0.0f, 0.0f, 0.0f)
	);

	textItemArray[1] = new TextItem(
		std::to_string(timeline->getNumFramesAvailable() / Time::getFps()),
		basePanelSprite->position.x + basePanelSprite->scale.x,
		basePanelSprite->position.y + 15.0f,
		1.0f,
		glm::vec3(0.0f, 0.0f, 0.0f),
		true
	);
}

int TimelineSlider::getNumTextItems() const {
	return 2;
}