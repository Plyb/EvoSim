#ifndef CREATURE_MIND_H
#define CREATURE_MIND_H

#include <vector>
#include <Eigen/Dense>

class CreatureMind {
public:
	CreatureMind(long long seed);
	CreatureMind(CreatureMind* parent);
	CreatureMind(std::vector<Eigen::MatrixXd> weights);

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
	private:
		std::vector<double> rawOutputs;
	};

	Outputs calculate(Inputs inputs) const;

private:
	std::vector<Eigen::MatrixXd> weights;
	void mutate();

	static Eigen::VectorXd sigmoid(const Eigen::VectorXd& values);

	static const int NODES_PER_LAYER = 12;
};

#endif // !CREATURE_MIND_H
