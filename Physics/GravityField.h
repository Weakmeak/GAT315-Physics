#pragma once
#include "ForceGenerator.h"
#include <vector>

class GravityField : public ForceGenerator {

	public:
		GravityField(float strength) : strength{ strength } {};
		void Apply(std::vector<class Body*> bodies) override;
	private:
		float strength{ 0 };
		//const double G{6.6743 * (0.00000000001)};
};