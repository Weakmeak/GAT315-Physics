#include "JointTest.h"
#include "../Physics/CircleShape.h"
#include "../Physics/Body.h"
#include "../Physics/Joint.h"

#define SPRING_STIFFNESS 100
#define SPRING_LENGTH 2
#define BODY_DAMPING 10
#define CHAIN_LENGTH 4

#define Chain
//#define Grid

void JointTest::Initialize()
{
	Test::Initialize();

	m_anchor = new Body(new CircleShape(1, { 1, 1, 1, 1 }), { 0, 0 }, { 0, 0 }, 0, Body::Kinematic);
	m_world->AddBody(m_anchor);

	#if defined (Chain)

	auto prevBody = m_anchor;

	for (size_t i = 0; i < CHAIN_LENGTH; i++)
	{
		auto body = new Body(new CircleShape(0.5, { 1, 1, 1, 1 }), { 0,0 }, {0, 0}, 1, Body::Dynamic);
		body->damping = BODY_DAMPING;
		m_world->AddBody(body);
		auto joint = new Joint(prevBody, body, SPRING_STIFFNESS, SPRING_LENGTH);
		m_world->AddJoint(joint);
		prevBody = body;
	}

	#elif defined (Grid)

	auto prevLeft = m_anchor;
	auto prevRight = m_anchor;

	for (size_t i = 0; i < CHAIN_LENGTH; i++)
	{
		auto bodyL = new Body(new CircleShape(20, { 1, 1, 1, 1 }), { 0,0 }, { 0, 0 }, 1, Body::Dynamic);
		bodyL->damping = BODY_DAMPING;
		m_world->AddBody(bodyL);

		auto bodyR = new Body(new CircleShape(20, { 1, 1, 1, 1 }), { (400 + SPRING_LENGTH), 100 + (SPRING_LENGTH * i) }, { 0, 0 }, 1, Body::Dynamic);
		bodyR->damping = BODY_DAMPING;
		m_world->AddBody(bodyR);


		//connect left and right to each other
		auto joint = new Joint(bodyL, bodyR, SPRING_STIFFNESS/4, SPRING_LENGTH * 2);
		m_world->AddJoint(joint);
		//connect left to prevLeft
		joint = new Joint(bodyL, prevLeft, SPRING_STIFFNESS, SPRING_LENGTH);
		m_world->AddJoint(joint);
		//connect right to prevRight
		joint = new Joint(bodyR, prevRight, SPRING_STIFFNESS, SPRING_LENGTH);
		m_world->AddJoint(joint);
		//if prevLeft/prevRight is not m_anchor, connect left to prevRight and vice-versa
		if (prevLeft != prevRight) {
			joint = new Joint(bodyL, prevRight, SPRING_STIFFNESS, SPRING_LENGTH);
			m_world->AddJoint(joint);
			joint = new Joint(bodyR, prevLeft, SPRING_STIFFNESS, SPRING_LENGTH);
			m_world->AddJoint(joint);
		}

		
		prevLeft = bodyL;
		prevRight = bodyR;
	}

	#endif
}

void JointTest::Update()
{
	Test::Update();
	m_anchor->position = m_graphics->ScreenToWorld(m_input->GetMousePosition());
}

void JointTest::FixedUpdate()
{
	m_world->Step(m_time->GetFixedDeltaTime());
}

void JointTest::Render()
{
	m_world->Draw(m_graphics);
	m_graphics->DrawCircle(m_input->GetMousePosition(), 10, { randomf(), randomf(), randomf(), 1 });
}