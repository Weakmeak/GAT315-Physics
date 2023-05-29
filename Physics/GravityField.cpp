#include "GravityField.h"
#include "Body.h"


void GravityField::Apply(std::vector<Body*> bodies) {
	for (size_t i = 0; i < bodies.size() - 1; i++)
	{
		for (size_t j = i + 1; j < bodies.size(); j++)
		{
			Body* bodyA = bodies[i];
			Body* bodyB = bodies[j];

			// apply gravitational force
			glm::vec2 direction = bodyA->position - bodyB->position;
			float distance = glm::length(direction);

			if (distance == 0) continue;

			distance = glm::max(1.0f, distance);
			float force = strength * ((bodyA->mass * bodyB->mass) / distance);

			glm::vec2 ndirection = glm::normalize(direction);
			bodyA->applyForce(-ndirection * force);
			bodyB->applyForce(ndirection * force);
		}
	}

}