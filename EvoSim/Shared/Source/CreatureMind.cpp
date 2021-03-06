#include "../Headers/CreatureMind.h"

#define _USE_MATH_DEFINES

#include <math.h>

const double CreatureMind::MUTATION_RATE = 0.1f;

CreatureMind::CreatureMind(long long seed) {
	const double min_weight = -1.0; // Should probably increase this.
	const double max_weight = 1.0;

	std::uniform_real_distribution<double> unif(min_weight, max_weight);
	random = std::default_random_engine(seed);

	std::vector<Eigen::MatrixXd> weights = std::vector<Eigen::MatrixXd>(HIDDEN_LAYER_COUNT + 1);

	const int secondLayerCount = HIDDEN_LAYER_COUNT > 1 ? NODES_PER_LAYER : Outputs::NUM_OUTPUTS;
	weights.at(0) = Eigen::MatrixXd(Inputs::NUM_INPUTS, secondLayerCount + 1);
	for (int i = 0; i < (secondLayerCount + 1) * (Inputs::NUM_INPUTS); i++) {
			weights.at(0)(i) = unif(random);
	}

	for (int i = 1; i < HIDDEN_LAYER_COUNT; i++) {
		weights.at(i) = Eigen::MatrixXd(NODES_PER_LAYER + 1, NODES_PER_LAYER);
		for (int j = 0; j < NODES_PER_LAYER * (NODES_PER_LAYER + 1); j++) {
				weights.at(i)(j) = unif(random);
		}
	}
	weights.at(HIDDEN_LAYER_COUNT) = Eigen::MatrixXd(NODES_PER_LAYER, Outputs::NUM_OUTPUTS + 1);
	for (int i = 0; i < (Outputs::NUM_OUTPUTS + 1) * NODES_PER_LAYER; i++) {
			weights.at(HIDDEN_LAYER_COUNT)(i) = unif(random);
	}

	this->weights = weights;
}

CreatureMind::CreatureMind(CreatureMind* parent) {
	weights = parent->weights;
	mutate();
}

CreatureMind::CreatureMind(std::vector<Eigen::MatrixXd> weights) : weights(weights) {}

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
	rawInputs.push_back(neighbors);
	rawInputs.push_back(cellFood / 100.0); // 100.0 should be max food.
	rawInputs.push_back(cellRed);
	rawInputs.push_back(cellGreen);
	rawInputs.push_back(cellBlue);
	rawInputs.push_back(age);
	rawInputs.push_back(1.0);
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
	Eigen::VectorXd values = Eigen::Map<Eigen::Matrix<double, Inputs::NUM_INPUTS + 1, 1>>(inputs.getRaw().data());
	for (Eigen::MatrixXd matrix : weights) {
		values = sigmoid(matrix * values);
		values[values.size() - 1] = 1.0f;
	}
	return Outputs(std::vector<double>(values.data(), values.data() + values.size()));
}

void CreatureMind::mutate() {
	std::uniform_real_distribution<double> multiplierDist(-MUTATION_RATE, MUTATION_RATE);
	std::uniform_real_distribution<double> negatorDist(0.0, 1.0);
	for (Eigen::MatrixXd& matrix : weights) {
		for (unsigned int i = 0; i < matrix.size(); i++) {
			matrix(i) += multiplierDist(random) * matrix(i);
			if (negatorDist(random) > MUTATION_RATE) {
				matrix(i) *= -1;
			}
		}
	}
}

Eigen::VectorXd CreatureMind::sigmoid(const Eigen::VectorXd& values) {
	Eigen::VectorXd sigmoidValues(values.size() + 1);
	for (unsigned int i = 0; i < values.size(); i++) {
		sigmoidValues[i] = 1.0 / (1.0 + exp(-values(i)));
	}
	return sigmoidValues;
}