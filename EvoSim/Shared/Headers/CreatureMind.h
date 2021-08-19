#ifndef CREATURE_MIND_H
#define CREATURE_MIND_H

#include <vector>
#include <Eigen/Dense>
#include <random>

class CreatureMind {
public:
	CreatureMind(long long seed);
	CreatureMind(CreatureMind* parent);
	CreatureMind(std::vector<Eigen::MatrixXd> weights);

	static const unsigned int NODES_PER_LAYER = 12;
	static const unsigned int HIDDEN_LAYER_COUNT = 1;

	class Inputs {
	public:
		Inputs(
			float energy,
			unsigned int neighbors,
			unsigned char cellFood,
			double cellRed,
			double cellGreen,
			double cellBlue,
			unsigned int age
		);

		std::vector<double> getRaw() const;

		static const unsigned int NUM_INPUTS = 7;

	private:
		std::vector<double> rawInputs;
	};

	class Outputs {
	public:
		Outputs(std::vector<double> rawOutputs);

		unsigned int getReproWillingNum() const;
		double getSpeed() const;
		double getRotChange() const;
		double getEatenPercent() const;

		static const unsigned int NUM_OUTPUTS = 7;

	private:
		std::vector<double> rawOutputs;
	};

	Outputs calculate(Inputs inputs) const;

private:
	std::vector<Eigen::MatrixXd> weights;
	void mutate();

	static Eigen::VectorXd sigmoid(const Eigen::VectorXd& values);

	static const double MUTATION_RATE;

	std::default_random_engine random;
};

#endif // !CREATURE_MIND_H
