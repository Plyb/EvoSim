#include "Creature.h"

#define _USE_MATH_DEFINES

#include <math.h>
#include <random>
#include "../Shared/Headers/CreatureMind.h"

const float Creature::BASE_ENERGY_CONSUMPTION = 0.001f;
const float Creature::BASE_ABSORPTION_RATE = 0.05f;

Creature::Creature(CreatureState* state) : state(state) {};

void Creature::update(Cell ground[WorldState::WORLD_WIDTH][WorldState::WORLD_WIDTH]) {
	Cell* currentCell = getCurrentCell(ground);
	if (currentCell == NULL) {
		state->energy = 0;
		return;
	}

	CreatureMind::Inputs inputs(
		state->energy,
		currentCell->getVisitingCreatures().size(),
		currentCell->getState()->food,
		currentCell->get_color_r(),
		currentCell->get_color_g(),
		currentCell->get_color_b(),
		state->age
	);

	CreatureMind::Outputs outputs = state->mind->calculate(inputs);
	
	state->reproduce_count = outputs.getReproWillingNum();
	if (state->reproduce_count) {
		state->energy -= 0.5;
	}

	float speed = outputs.getSpeed();
	float rotChange = outputs.getRotChange();
	state->rot += rotChange;
	state->xpos += cos(state->rot * M_PI / 180) / 100.0f * speed;
	state->ypos += sin(state->rot * M_PI / 180) / 100.0f * speed;

	state->eaten = (currentCell->getState()->food / 
			(currentCell->getVisitingCreatures().size() ? currentCell->getVisitingCreatures().size() : 1)
		) * outputs.getEatenPercent();
	state->energy += state->eaten - BASE_ENERGY_CONSUMPTION;
	state->age++;
}

Cell* Creature::getCurrentCell(Cell ground[WorldState::WORLD_WIDTH][WorldState::WORLD_WIDTH]) const {
	int xcoord = (int)(state->xpos + 0.5f);
	int ycoord = (int)(state->ypos + 0.5f);

	if (xcoord < 0 || xcoord >= WorldState::WORLD_WIDTH || ycoord < 0 || ycoord >= WorldState::WORLD_WIDTH) {
		return NULL;
	}

	return &(ground[xcoord][ycoord]);
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
	childState->id = ++CreatureState::LAST_ID;
	childState->mind = new CreatureMind(state->mind);
	
	childState->energy = state->energy / 2.0f;

	state->energy -= state->energy / 2.0f;

	return new Creature(childState);
}

bool Creature::isDying() const
{
	return state->energy <= 0.0;
}

bool Creature::isReproducing(Cell ground[WorldState::WORLD_WIDTH][WorldState::WORLD_WIDTH]) const
{
	if (state->reproduce_count == 0 || getCurrentCell(ground) == nullptr) return false;
	int count = 0;
	for (CreatureState* cs : getCurrentCell(ground)->getVisitingCreatures())
		if (cs->reproduce_count == state->reproduce_count)
			count += 1;
	return count == state->reproduce_count; // TODO Make only one of the N creatures respond true.
}
