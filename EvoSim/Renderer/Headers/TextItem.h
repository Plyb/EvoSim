#ifndef TEXT_ITEM_H
#define TEXT_ITEM_H

#include <string>
#include <glm/glm.hpp>

struct TextItem {
	TextItem(
		std::string text,
		float x,
		float y,
		float scale,
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f),
		bool centered = false
	);

	std::string text;
	float x;
	float y;
	float scale;
	glm::vec3 color;
	bool centered;
};

#endif // !TEXT_ITEM_H

