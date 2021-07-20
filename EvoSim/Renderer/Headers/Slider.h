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
private:
	Sprite* handleSprite;
	float handlePos;
	bool dragging = false;

	void updateHandlePos();

	virtual void onSliderUpdated() = 0;
};

#endif // !SLIDER_H
