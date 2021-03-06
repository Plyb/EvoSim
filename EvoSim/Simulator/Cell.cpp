#include "Cell.h"

const float Cell::FOOD_BOOST_CHANCE = 0.05f;

Cell::Cell() {
	state = CellState();
	state.food = 10; // TODO: magic number
}

const CellState* Cell::getState() const {
	return &state;
}



void Cell::update() {
	unsigned char& food = state.food;
	
	unsigned char foodIncrease = FOOD_BOOST * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) < FOOD_BOOST_CHANCE);
	if (food == 255 && foodIncrease) {
		food = 255;
	}
	if ((unsigned char)(food + foodIncrease) > food) {
		food += foodIncrease;
	}

	for (CreatureState* creature : visitingCreatures) {
		if (food - creature->eaten <= creature->eaten) {
			food -= creature->eaten;
		}
		else {
			food = 0;
		}
	}
}

void Cell::clearVisitingCreatures() {
	visitingCreatures.clear();
}

void Cell::pushVisitingCreature(CreatureState* creature) {
	visitingCreatures.push_back(creature);
}

const std::vector<CreatureState*> Cell::getVisitingCreatures()
{
	return visitingCreatures;
}

double Cell::get_color_r()
{
	if (visitingCreatures.size() == 0)
		return 0.0;
	double total = 0.0;
	for (CreatureState* cs : visitingCreatures) {
		total += cs->r;
	}
	return total / visitingCreatures.size();
}

double Cell::get_color_g()
{
	if (visitingCreatures.size() == 0)
		return 0.0;
	double total = 0.0;
	for (CreatureState* cs : visitingCreatures) {
		total += cs->r;
	}
	return total / visitingCreatures.size();
}

double Cell::get_color_b()
{
	if (visitingCreatures.size() == 0)
		return 0.0;
	double total = 0.0;
	for (CreatureState* cs : visitingCreatures) {
		total += cs->r;
	}
	return total / visitingCreatures.size();
}
