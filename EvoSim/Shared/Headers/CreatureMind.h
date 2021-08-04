#ifndef CREATURE_MIND_H
#define CREATURE_MIND_H

#include <vector>

class CreatureMind {
public:
	CreatureMind(unsigned int seed);
	CreatureMind(CreatureMind* parent);

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
	std::vector<std::vector<std::vector<double>>> weights;
	void mutate();

	static double sigmoid(double value);
};

#endif // !CREATURE_MIND_H
