#include "../Headers/BackgroundRenderer.h"
#include <limits.h>

BackgroundRenderer::BackgroundRenderer(Shader& shader) {
	this->shader = shader;
	this->initRenderData();
}

BackgroundRenderer::~BackgroundRenderer() {
	delete vertices;
	delete indices;
}

void BackgroundRenderer::drawBackground(BackgroundCell** bg) {
	this->shader.use();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(100.0f, 100.0f, 1.0f)); //TODO give this some not magic numbers
	this->shader.set("model", model);

	copyColors(bg);

	glBindVertexArray(this->VAO);
	const int quadWidth = 6; // TODO combine this with the one in initRenderData()
	glDrawElements(GL_TRIANGLES, quadWidth * WorldState::WORLD_WIDTH * WorldState::WORLD_WIDTH, GL_UNSIGNED_INT, 0);
}

void BackgroundRenderer::copyColors(BackgroundCell** bg) {
	const int coordWidth = 2;
	const int colorWidth = 3;
	const int vertWidth = coordWidth + colorWidth; // Combine these with their initRenderData versions
	const int rOffset = 2;
	const int gOffset = 3;
	const int bOffset = 4;
	for (unsigned int x = 0; x < WorldState::WORLD_WIDTH; x++) {
		for (unsigned int y = 0; y < WorldState::WORLD_WIDTH; y++) {
			unsigned int vertIndex = (x + y * (WorldState::WORLD_WIDTH)) * vertWidth;
			vertices[vertIndex + rOffset] = ((float)bg[x][y].r) / UCHAR_MAX;
			vertices[vertIndex + gOffset] = ((float)bg[x][y].g) / UCHAR_MAX;
			vertices[vertIndex + bOffset] = ((float)bg[x][y].b) / UCHAR_MAX;
		}
	}

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	unsigned int verticesSize = sizeof(float) * (WorldState::WORLD_WIDTH) * (WorldState::WORLD_WIDTH) * vertWidth;
	glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STREAM_DRAW);
}

void BackgroundRenderer::initRenderData() {
	const int coordWidth = 2;
	const int colorWidth = 3;
	const int vertWidth = coordWidth + colorWidth;
	vertices = new float[(WorldState::WORLD_WIDTH) * (WorldState::WORLD_WIDTH) * vertWidth];
	for (unsigned int x = 0; x < WorldState::WORLD_WIDTH; x++) {
		for (unsigned int y = 0; y < WorldState::WORLD_WIDTH; y++) {
			unsigned int index = (x + y * (WorldState::WORLD_WIDTH)) * vertWidth;
			vertices[index] = x;
			vertices[index + 1] = y;
		}
	}

	const int quadWidth = 6;
	indices = new unsigned int[(WorldState::WORLD_WIDTH - 1) * (WorldState::WORLD_WIDTH - 1) * quadWidth];
	for (unsigned int x = 0; x < WorldState::WORLD_WIDTH - 1; x++) {
		for (unsigned int y = 0; y < WorldState::WORLD_WIDTH - 1; y++) {
			unsigned int topRight = (x + 1) + y * (WorldState::WORLD_WIDTH);
			unsigned int bottomRight = (x + 1) + (y + 1) * (WorldState::WORLD_WIDTH);
			unsigned int bottomLeft = x + (y + 1) * (WorldState::WORLD_WIDTH);
			unsigned int topLeft = x + y * (WorldState::WORLD_WIDTH);
			
			unsigned int index = (x + y * (WorldState::WORLD_WIDTH - 1)) * quadWidth;
			indices[index] = topRight;
			indices[index + 1] = bottomRight;
			indices[index + 2] = topLeft;
			indices[index + 3] = bottomRight;
			indices[index + 4] = bottomLeft;
			indices[index + 5] = topLeft;
		}
	}

	unsigned int EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	unsigned int verticesSize = sizeof(float) * (WorldState::WORLD_WIDTH) * (WorldState::WORLD_WIDTH) * vertWidth;
	glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STREAM_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	unsigned int indicesSize = sizeof(unsigned int) * (WorldState::WORLD_WIDTH - 1) * (WorldState::WORLD_WIDTH - 1) * quadWidth;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STREAM_DRAW);

	glVertexAttribPointer(0, coordWidth, GL_FLOAT, GL_FALSE, vertWidth * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, colorWidth, GL_FLOAT, GL_FALSE, vertWidth * sizeof(float), (void*)(coordWidth * sizeof(float)));
	glEnableVertexAttribArray(1);
}