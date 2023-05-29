#include "DragForce.h"
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include "Body.h"
#include "Shape.h"

void DragForce::Apply(std::vector<class Body*> bodies)
{
	for (auto body : bodies)
	{
		if (!m_body->Intersects(body)) continue;

		if (body->velocity == glm::vec2{ 0, 0 }) continue;

		//float l = m_body->shape->size;
		float f = 0.5f * m_drag * glm::length2(body->velocity);
		glm::vec2 force = glm::normalize(body->velocity);
		body->applyForce(force * -f);
	}

}
