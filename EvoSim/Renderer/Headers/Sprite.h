#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <glm/glm.hpp>

class Sprite {
public:
	Sprite(std::string image, glm::vec2 position, float rotation, glm::vec2 scale);

	std::string image;
	glm::vec2 position;
	float rotation;
	glm::vec2 scale;
};

#endif // !SPRITE_H


