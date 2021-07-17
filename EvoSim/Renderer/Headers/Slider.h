#ifndef SLIDER_H
#define SLIDER_H

#include "RectangularUiElement.h"

class Slider : public RectangularUiElement {
public:
	Slider(float x, float y, float height, float width);

	virtual bool onClick() override;
	virtual void insertSprites(Sprite** spriteArray) override;
	virtual unsigned int getNumSprites() const override;

	float getValue() const;
private:
	Sprite* handleSprite;
	float handlePos;
	bool dragging = false;

	void updateHandlePos();
};

#endif // !SLIDER_H
