#ifndef BACKGROUND_RENDERER_H
#define BACKGROUND_RENDERER_H

#include "BackgroundCell.h"
#include "Shader.h"
#include "../../Shared/Headers/WorldState.h"

class BackgroundRenderer {
public:
	BackgroundRenderer(Shader& shader);
	~BackgroundRenderer();

	void drawBackground(BackgroundCell** bg);
private:
	Shader shader;
	unsigned int VAO, VBO;
	float* vertices;
	unsigned int* indices;

	void initRenderData();
	void copyColors(BackgroundCell** bg);
};

#endif // !BACKGROUND_RENDERER_H
