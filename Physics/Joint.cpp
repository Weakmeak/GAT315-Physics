#include "Joint.h"
#include "Body.h"
#include "../Engine/Graphics.h"

Joint::Joint(Body* BodA, Body* BodB, float stiffness, float restLength) :
	BodyA{BodA},
	BodyB{BodB},
	m_stiffness{stiffness},
	m_restLength{restLength}
{
	if (m_restLength == 0) m_restLength = glm::distance(BodyA->position, BodyB->position);
}

void Joint::Step(float dt)
{
	glm::vec2 dir = BodyA->position - BodyB->position;
	float len = glm::length(dir);
	if (len == 0) return;
	// f = -k x
	float x = len - m_restLength;
	//if (x < 0) return;
	float f = -m_stiffness * x;
	glm::vec2 norm = glm::normalize(dir);
	BodyA->applyForce( norm * f);
	BodyB->applyForce(-norm * f);
}

void Joint::Draw(Graphics* graphics)
{
	graphics->DrawLine(graphics->WorldToScreen(BodyA->position), graphics->WorldToScreen(BodyB->position), {1, 1, 1, 1});
}
