#include "ForceTest.h"
#include "../Physics/CircleShape.h"
#include "../Physics/Body.h"
#include "../Physics/GravityField.h"
#include "../Physics/PointForce.h"
#include "../Physics/AreaForce.h"
#include "../Physics/DragForce.h"

#include <iostream>

//#define POINT_FORCE
//#define AREA_FORCE
//#define DRAG_FORCE

void ForceTest::Initialize()
{
	Test::Initialize();

	#if defined(POINT_FORCE)
		auto body = new Body(new CircleShape(75, { 1, 1, 1, 0.2f }), { 0, 0 }, { 0, 0 }, 0, Body::Static);
		ForceGenerator* forceGenerator = new PointForce(body, 2000);
		m_world->AddForceGen(forceGenerator);
	#elif defined(AREA_FORCE)
		auto body = new Body(new CircleShape(200, { 1, 1, 1, 0.2f }), { 0, 0 }, { 0, 0 }, 0, Body::Static);
		ForceGenerator* forceGenerator = new AreaForce(body, 2000, -90);
		m_world->AddForceGen(forceGenerator);
	#elif defined(DRAG_FORCE)
		auto body = new Body(new CircleShape(200, { 1, 1, 1, 0.2f }), { 0, 0 }, { 0, 0 }, 0, Body::Static);
		ForceGenerator* forceGenerator = new DragForce(body, 0.5f);
		m_world->AddForceGen(forceGenerator);
	#endif
}

void ForceTest::Update()
{
	Test::Update();
	if (m_input->GetMouseButton(0))
	{
		float size = randomf(0.1f, 0.5f);
		glm::vec2 velocity = randomUnitCircle() * randomf(1, 3);

		auto bod = new Body(new CircleShape(size, randomColor()), m_graphics->ScreenToWorld(m_input->GetMousePosition()), {0,0}, size * 2);
		//bod->damping = 0.5f;
		bod->gravityScale = 0;
		m_world->AddBody(bod);
	}
}

void ForceTest::FixedUpdate()
{
	m_world->Step(m_time->GetFixedDeltaTime());
}

void ForceTest::Render()
{
	m_graphics->DrawCircle(m_input->GetMousePosition(), 30, randomColor());

	m_world->Draw(m_graphics);
}
