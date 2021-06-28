#include "Creature.h"

#define _USE_MATH_DEFINES

#include <math.h>

const float Creature::BASE_ENERGY_CONSUMPTION = 0.25f;
const float Creature::BASE_ABSORPTION_RATE = 0.05f;

Creature::Creature(CreatureState* state) : state(state) {};

void Creature::update(Cell ground[WorldState::WORLD_WIDTH][WorldState::WORLD_WIDTH]) {
	state->rot += 0.1f;
	state->xpos += cos(state->rot * M_PI / 180) / 100.0f;
	state->ypos += sin(state->rot * M_PI / 180) / 100.0f;

	const CellState* currentCell = getCurrentCellState(ground);
	if (currentCell != NULL) {
		state->eaten = currentCell->food * BASE_ABSORPTION_RATE;
	}
	else {
		state->eaten = 0.0f;
	}
	state->energy += state->eaten - BASE_ENERGY_CONSUMPTION;
}

Cell* Creature::getCurrentCell(Cell ground[WorldState::WORLD_WIDTH][WorldState::WORLD_WIDTH]) const {
	int xcoord = (int)(state->xpos + 0.5f);
	int ycoord = (int)(state->ypos + 0.5f);

	if (xcoord < 0 || xcoord >= WorldState::WORLD_WIDTH || ycoord < 0 || ycoord >= WorldState::WORLD_WIDTH) {
		return NULL;
	}

	return &ground[xcoord][ycoord];
}

const CellState* Creature::getCurrentCellState(Cell ground[WorldState::WORLD_WIDTH][WorldState::WORLD_WIDTH]) const {
	Cell* cell = getCurrentCell(ground);
	if (cell == NULL) {
		return NULL;
	}
	return getCurrentCell(ground)->getState();
}

CreatureState* Creature::getState() const {
	return state;
}

void Creature::remapCell(Cell ground[WorldState::WORLD_WIDTH][WorldState::WORLD_WIDTH]) {
	Cell* cell = getCurrentCell(ground);
	if (cell == NULL) {
		return;
	}

	cell->pushVisitingCreature(getState());
}

Creature* Creature::reproduce() const {
	CreatureState* childState = new CreatureState();
	childState->xpos = state->xpos;
	childState->ypos = state->ypos;
	childState->rot = rand();

	childState->energy = state->reproductionEnergy / 2.0f;

	state->energy -= state->reproductionEnergy / 2.0f;

	return new Creature(childState);
}