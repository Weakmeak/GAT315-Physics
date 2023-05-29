#include "Body.h"
#include "../Engine/Integrator.h"
#include "CircleShape.h"
#include "../Engine/World.h"
#include "../Engine/Graphics.h"
#include "Shape.h"

void Body::Step(float dT)
{
	//grav

	if (type != Dynamic) return;

	applyForce(World::gravity * gravityScale * mass);

	Integrator::SemiImplicitEuler(*this, dT);
	clearForce();

	velocity *= (1.0f / (1.0f + (damping * dT)));
}

void Body::Draw(Graphics* graphics)
{
	shape->Draw(graphics, graphics->WorldToScreen(position));
}

void Body::applyForce(const glm::vec2& Force)
{
	this->force += Force;
}

bool Body::Intersects(Body* body)
{
	glm::vec2 direction = position - body->position;
	float distance = glm::length(direction);
	//float radius = shape->size + body->shape->size;
	float radius = static_cast<CircleShape*>(this->shape)->radius + static_cast<CircleShape*>(body->shape)->radius;
	return distance <= radius;
}
