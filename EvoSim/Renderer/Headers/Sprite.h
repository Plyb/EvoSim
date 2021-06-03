#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <glm/glm.hpp>

class Sprite {
public:
	Sprite(std::string image, glm::vec2 position, float rotation, glm::vec2 scale, glm::vec3 color);

	std::string image;
	glm::vec2 position;
	float rotation;
	glm::vec2 scale;
	glm::vec3 color;
};

#endif // !SPRITE_H


