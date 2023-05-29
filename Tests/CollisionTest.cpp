#include "CollisionTest.h"
#include "../Physics/Body.h"
#include "../Physics/CircleShape.h"

void CollisionTest::Initialize()
{
	Test::Initialize();

	m_user = new Body(new CircleShape(1, { 0, 0, 1, 1 }), { 0, 0 }, { 0, 0 }, 1, Body::Kinematic);
	m_world->AddBody(m_user);

	glm::vec2 extents = m_graphics->GetWorldExtents();

	auto body = new Body(new CircleShape(200, glm::vec4{ 1.0f }), { 0, -(200 + extents.y) }, { 0, 0 }, 1, Body::Static);
	body->restitution = 0;
	m_world->AddBody(body);

	body = new Body(new CircleShape(200, glm::vec4{ 1.0f }), { 200 + extents.x, 0.0 }, { 0, 0 }, 1, Body::Static);
	body->restitution = 0;
	m_world->AddBody(body);

	body = new Body(new CircleShape(200, glm::vec4{ 1.0f }), { -(200 + extents.x), 0.0 }, { 0, 0 }, 1, Body::Static);
	body->restitution = 0;
	m_world->AddBody(body);
}

void CollisionTest::Update()
{
	Test::Update();

	glm::vec2 position = m_graphics->ScreenToWorld(m_input->GetMousePosition());
	m_user->velocity = position - m_user->position;
	m_user->position = position;

	if (m_input->GetMouseButton(0))
	{
		glm::vec2 velocity = randomUnitCircle() * randomf(0, 0);
		float size = 0.1f;//randomf(0.1f, f);

		auto body = new Body(new CircleShape(size, { randomf(), randomf(), randomf(), 1 }), position, velocity, size);
		body->damping = 0;
		body->gravityScale = 1;

		m_world->AddBody(body);
	}
}

void CollisionTest::FixedUpdate()
{
	m_world->Step(m_time->GetFixedDeltaTime());
}

void CollisionTest::Render()
{
	m_world->Draw(m_graphics);
}