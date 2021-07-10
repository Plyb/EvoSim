#ifndef SLIDER_H
#define SLIDER_H

#include "RectangularUiElement.h"

class Slider : public RectangularUiElement {
public:
	Slider(float x, float y, float height, float width);

	virtual void onClick() override;
	virtual void insertSprites(Sprite** spriteArray) const override;
	virtual unsigned int getNumSprites() const override;
private:
	Sprite* handleSprite;
	float handlePos;
};

#endif // !SLIDER_H
