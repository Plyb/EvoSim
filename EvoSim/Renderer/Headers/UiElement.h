#ifndef UI_ELEMENT_H
#define UI_ELEMENT_H

#include "Sprite.h"

class UiElement {
public:
	virtual void onClick() = 0;
	Sprite* getSprite();

protected:
	Sprite* sprite;
};

#endif // !UI_ELEMENT_H
