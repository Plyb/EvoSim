#ifndef SLIDER_H
#define SLIDER_H

#include "RectangularUiElement.h"
#include <vector>

class Slider : public RectangularUiElement {
public:
	Slider(float x, float y, float height, float width);

	virtual bool onClick() override;
	virtual void insertSprites(Sprite** spriteArray) override;
	virtual unsigned int getNumSprites() const override;

	float getValue() const;
	void setValue(float value);

	class Listener {
	public:
		virtual void onSliderUpdated(Slider* slider) = 0;
	};

	void registerListener(Listener* listener);
private:
	Sprite* handleSprite;
	float handlePos;
	bool dragging = false;

	std::vector<Listener*> listeners;

	void updateHandlePos();
};

#endif // !SLIDER_H
