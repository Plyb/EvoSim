#include "Creature.h"

#define _USE_MATH_DEFINES

#include <math.h>

const float Creature::BASE_ENERGY_CONSUMPTION = 1.0f;
const float Creature::BASE_ABSORPTION_RATE = 0.05f;

Creature::Creature(CreatureState* state, WorldState* worldState) : state(state), worldState(worldState) {};

void Creature::update() {
	state->rot += 0.1f;
	state->xpos += cos(state->rot * M_PI / 180) / 100.0f;
	state->ypos += sin(state->rot * M_PI / 180) / 100.0f;

	CellState* currentCell = worldState->cellAt(*state);
	if (currentCell != NULL) {
		state->eaten = currentCell->food * BASE_ABSORPTION_RATE;
	}
	else {
		state->eaten = 0.0f;
	}
	state->energy += state->eaten - BASE_ENERGY_CONSUMPTION;
}