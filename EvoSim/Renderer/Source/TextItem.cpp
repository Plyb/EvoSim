#include "../Headers/TextItem.h"

TextItem::TextItem(std::string text, float x, float y, float scale, glm::vec3 color, bool centered) 
	: text(text), x(x), y(y), scale(scale), color(color), centered(centered) {}