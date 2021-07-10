#ifndef UI_ELEMENT_H
#define UI_ELEMENT_H

#include "Sprite.h"

class UiElement {
public:
	// Returns true if should block click
	virtual bool onClick() = 0;
	virtual void insertSprites(Sprite** spriteArray) = 0;
	virtual unsigned int getNumSprites() const = 0;
protected:
	virtual bool clickHits() const = 0;
};

#endif // !UI_ELEMENT_H
