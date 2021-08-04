#include "../Headers/CreatureMind.h"

#define _USE_MATH_DEFINES

#include <math.h>
#include <random>

CreatureMind::CreatureMind(unsigned int seed) {
	const int INPUT_COUNT = 7;
	const int OUTPUT_COUNT = 7;
	const int HIDDEN_LAYER_COUNT = 1;
	const int NODES_PER_LAYER = 12;

	const double min_weight = -1.0; // Should probably increase this.
	const double max_weight = 1.0;

	std::uniform_real_distribution<double> unif(min_weight, max_weight);
	std::default_random_engine re(seed);

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

	this->weights = weights;
}

CreatureMind::CreatureMind(CreatureMind* parent) {
	weights = parent->weights;
}

CreatureMind::Inputs::Inputs(
	float energy,
	unsigned int neighbors,
	unsigned char cellFood,
	double cellRed,
	double cellGreen,
	double cellBlue,
	unsigned int age
) {
	rawInputs.push_back(energy / 100.0);
	rawInputs.push_back(CreatureMind::sigmoid(neighbors) * 2.0 - 1.0);
	rawInputs.push_back(cellFood / 100.0); // 100.0 should be max food.
	rawInputs.push_back(cellRed);
	rawInputs.push_back(cellGreen);
	rawInputs.push_back(cellBlue);
	rawInputs.push_back(age);
}

std::vector<double> CreatureMind::Inputs::getRaw() const {
	return rawInputs;
}

CreatureMind::Outputs::Outputs(std::vector<double> rawOutputs)
	: rawOutputs(rawOutputs) {}

unsigned int CreatureMind::Outputs::getReproWillingNum() const {
	unsigned int willingNum = 0;
	if (rawOutputs.at(3) > 0.5) {
		willingNum = 4;
	}
	else if (rawOutputs.at(2) > 0.5) {
		willingNum = 3;
	}
	else if (rawOutputs.at(1) > 0.5) {
		willingNum = 2;
	}
	else if (rawOutputs.at(0) > 0.5) {
		willingNum = 1;
	}

	return willingNum;
}

double CreatureMind::Outputs::getSpeed() const {
	return (rawOutputs.at(4) * 2.0 - 1.0) * 40.0f;
}

double CreatureMind::Outputs::getRotChange() const {
	return rawOutputs.at(5) * 2.0 - 1.0;
}

double CreatureMind::Outputs::getEatenPercent() const {
	return rawOutputs.at(6);
}

CreatureMind::Outputs CreatureMind::calculate(CreatureMind::Inputs inputs) const {
	std::vector<double> values = inputs.getRaw();
	for (std::vector<std::vector<double>> matrix : weights) {
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
	return Outputs(values);
}

void CreatureMind::mutate() {
	// TODO implement
}

double CreatureMind::sigmoid(double value) {
	return 1.0 / (1.0 + exp(-value));
}