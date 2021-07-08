#ifndef UI_ELEMENT_H
#define UI_ELEMENT_H

#include "Sprite.h"

class UiElement {
public:
	virtual void onClick() = 0;
	virtual void insertSprites(Sprite** spriteArray) const = 0;
	virtual unsigned int getNumSprites() const = 0;
	virtual bool clickHits() const = 0;
};

#endif // !UI_ELEMENT_H
