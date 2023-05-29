#include "World.h"
#include "../Physics/Body.h"
#include "../Physics/Joint.h"
#include "../Physics/ForceGenerator.h"
#include "../Physics/Collision/Collision.h"
#include <vector>

glm::vec2 World::gravity{ 0, -9.8f };

World::~World()
{
	// <delete all the objects>
	// <clear the objects form the list clear()>
	for (Body* obj : m_bodies)
	{
		delete obj;
	}
	m_bodies.clear();
}
void World::Step(float dt)
{
	// <call Step() on all the objects>
	std::vector<Body*> bodies(m_bodies.begin(), m_bodies.end());
	if (!m_bodies.empty() && !m_forceGenerators.empty())
	{
		
		for (auto forceGen : m_forceGenerators)
		{
			forceGen->Apply(bodies);
		}
	}
	for (Body* obj : bodies)
	{
		obj->Step(dt);
	}
	for (Joint* obj : m_joints)
	{
		obj->Step(dt);
	}

	if (bodies.size() <= 0) return;
	std::vector<Contact> contacts;
	Collision::CreateContacts(bodies, contacts);
	Collision::SeparateContacts(contacts);
	Collision::ResolveContacts(contacts);
}
void World::Draw(Graphics* graphics)
{
	// <call Draw() on all the objects>
	for (Body* obj : m_bodies) obj->Draw(graphics);
	for (Joint* obj : m_joints) obj->Draw(graphics);
	for (auto forceGen : m_forceGenerators) forceGen->Draw(graphics);
}
void World::AddBody(Body* bod)
{
	// <push back the po onto objects list>
	m_bodies.push_back(bod);
}
void World::RemoveBody(Body* bod)
{
	// <remove po from the objects list>
	m_bodies.remove(bod);
}

void World::AddJoint(Joint* join)
{
	// <push back the po onto objects list>
	m_joints.push_back(join);
}
void World::RemoveJoint(Joint* join)
{
	// <remove po from the objects list>
	m_joints.remove(join);
}

void World::AddForceGen(ForceGenerator* fg)
{
	m_forceGenerators.push_back(fg);
}
