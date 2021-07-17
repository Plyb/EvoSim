#include "Creature.h"

#define _USE_MATH_DEFINES

#include <math.h>

const float Creature::BASE_ENERGY_CONSUMPTION = 0.25f;
const float Creature::BASE_ABSORPTION_RATE = 0.05f;


std::vector<double> Creature::runNN(std::vector<double> input) {
	std::vector<double> values = input;
	for (std::vector<std::vector<double>> matrix : state->weights) {
		values.push_back(1.0);
		std::vector<double> next = std::vector<double>();
		for (int i = 0; i < matrix.size(); i++) {
			double total = 0.0;
			for (int j = 0; j < matrix.at(i).size(); j++) {
				total += matrix.at(i).at(j) * values.at(j);
			}
			next.push_back(sigmoid(total));
		}
		values = next;
	}
	return values;
}

double Creature::sigmoid(double value) {
	return 1.0 / (1.0 + exp(-value));
}

Creature::Creature(CreatureState* state) : state(state) {
	const int INPUT_COUNT = 6;
	const int OUTPUT_COUNT = 7;
	const int HIDDEN_LAYER_COUNT = 12;
	const int NODES_PER_LAYER = 12;

	const double min_weight = -1.0; // Should probably increase this.
	const double max_weight = 1.0;

	std::uniform_real_distribution<double> unif(min_weight, max_weight);
	std::default_random_engine re;

	std::vector<std::vector<std::vector<double>>> weights;
	weights = std::vector<std::vector<std::vector<double>>>(HIDDEN_LAYER_COUNT + 1);

	weights.at(0) = std::vector<std::vector<double>>(NODES_PER_LAYER);
	for (int i = 0; i < NODES_PER_LAYER; i++) {
		weights.at(0).at(i) = std::vector<double>(INPUT_COUNT + 1);
		for (int j = 0; j < INPUT_COUNT + 1; j++) {
			weights.at(0).at(i).at(j) = unif(re);
		}
	}

	for (int i = 1; i < HIDDEN_LAYER_COUNT; i++) {
		weights.at(i) = std::vector<std::vector<double>>(NODES_PER_LAYER);
		for (int j = 0; j < NODES_PER_LAYER; j++) {
			weights.at(i).at(j) = std::vector<double>(NODES_PER_LAYER + 1);
			for (int k = 0; k < NODES_PER_LAYER + 1; k++) {
				weights.at(i).at(j).at(k) = unif(re);
			}
		}
	}
	weights.at(HIDDEN_LAYER_COUNT) = std::vector<std::vector<double>>(OUTPUT_COUNT);
	for (int i = 0; i < OUTPUT_COUNT; i++) {
		weights.at(HIDDEN_LAYER_COUNT).at(i) = std::vector<double>(NODES_PER_LAYER + 1);
		for (int j = 0; j < NODES_PER_LAYER + 1; j++) {
			weights.at(HIDDEN_LAYER_COUNT).at(i).at(j) = unif(re);
		}
	}

	state->weights = weights;
};

void Creature::update(Cell ground[WorldState::WORLD_WIDTH][WorldState::WORLD_WIDTH]) {
	/*state->rot += 0.1f;
	state->xpos += cos(state->rot * M_PI / 180) / 100.0f;
	state->ypos += sin(state->rot * M_PI / 180) / 100.0f;

	const CellState* currentCell = getCurrentCellState(ground);
	if (currentCell != NULL) {
		state->eaten = currentCell->food * BASE_ABSORPTION_RATE;
	}
	else {
		state->eaten = 0.0f;
	}
	state->energy += state->eaten - BASE_ENERGY_CONSUMPTION;*/

	Cell* currentCell = getCurrentCell(ground);
	if (currentCell == NULL) return;

	std::vector<double> inputs;
	inputs.push_back(state->energy);
	inputs.push_back(sigmoid(currentCell->getVisitingCreatures().size()) * 2.0 - 1.0);
	inputs.push_back(currentCell->getState()->food / 100.0); // 100.0 should be max food.
	inputs.push_back(currentCell->get_color_r());
	inputs.push_back(currentCell->get_color_g());
	inputs.push_back(currentCell->get_color_b());
	
	std::vector<double> outputs;
	outputs = runNN(inputs);
	if (outputs.at(3) > 0.5) {
		state->reproduce_count = 4;
		state->energy -= 0.5; // Magic Number. Should fix.
	}
	else if (outputs.at(2) > 0.5) {
		state->reproduce_count = 3;
		state->energy -= 0.5; // Magic Number. Should fix.
	}
	else if (outputs.at(1) > 0.5) {
		state->reproduce_count = 2;
		state->energy -= 0.5; // Magic Number. Should fix.
	}
	else if (outputs.at(0) > 0.5) {
		state->reproduce_count = 1;
		state->energy -= 0.5; // Magic Number. Should fix.
	}
	else
		state->reproduce_count = 0;

	state->xpos += outputs.at(4) * 2.0 - 1.0 + 0.2; // adding 0.2 just for testing
	state->ypos += outputs.at(5) * 2.0 - 1.0;
	state->energy -= sqrt(pow(outputs.at(4) * 2.0 - 1.0, 2) + pow(outputs.at(5) * 2.0 - 1.0, 2)) / 100.0;

	state->eaten = (currentCell->getState()->food / (currentCell->getVisitingCreatures().size() ? currentCell->getVisitingCreatures().size() : 1)) * outputs.at(6);
	state->energy += state->eaten;
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

bool Creature::isDying() const
{
	return state->energy <= 0.0;
}

bool Creature::isReproducing(Cell ground[WorldState::WORLD_WIDTH][WorldState::WORLD_WIDTH]) const
{
	if (state->reproduce_count == 0) return false;
	return false;
	int count = 0;
	for (CreatureState* cs : getCurrentCell(ground)->getVisitingCreatures())
		if (cs->reproduce_count == state->reproduce_count)
			count += 1;
	return count == state->reproduce_count; // TODO Make only one of the N creatures respond true.
}
