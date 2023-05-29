#include "Collision.h"
#include "../CircleShape.h"
#include "../../Engine/Random.h"

Contact Collision::GenerateContact(Body* BodyA, Body* BodyB)
{
    Contact Con; //KHAAAAAAN!
    Con.bodyA = BodyA;
    Con.bodyB = BodyB;

    glm::vec2 dir = BodyA->position - BodyB->position;
    float dist = glm::length(dir);
	if (dist == 0) {
		dir = { randomf(-.05f, .05f), randomf(-.05f, .05f) };
	}

	float rad = dynamic_cast<CircleShape*>(BodyA->shape)->radius + dynamic_cast<CircleShape*>(BodyB->shape)->radius;

    Con.depth = rad - dist;
    Con.normal = glm::normalize(dir);
	Con.restitution = (BodyA->restitution + BodyB->restitution) * 0.5f;

    return Con;
}

void Collision::CreateContacts(std::vector<Body*> bods, std::vector<Contact>& cons)
{
	for (size_t i = 0; i < bods.size() - 1; i++)
	{
		for (size_t j = i + 1; j < bods.size(); j++)
		{
			Body* bodyA = bods[i];
			Body* bodyB = bods[j];

			// contact needs at least one dynamic body
			if (bodyA->type != Body::Dynamic && bodyB->type != Body::Dynamic) continue;

			// check for intersection between bodies
			if (bodyA->Intersects(bodyB))
			{
				// create contact
				Contact contact = Collision::GenerateContact(bodyA, bodyB);
				cons.push_back(contact);
			}
		}
	}
}

void Collision::SeparateContacts(std::vector<Contact>& contacts)
{
	for (auto& contact : contacts) {
		float totalInvMass = contact.bodyA->invMass + contact.bodyB->invMass;

		glm::vec2 separation = contact.normal * (contact.depth / totalInvMass);
		contact.bodyA->position += separation * contact.bodyA->invMass;
		contact.bodyB->position -= separation * contact.bodyB->invMass;
	}
}

void Collision::ResolveContacts(std::vector<Contact>& contacts)
{
	for (auto& contact : contacts) {
		glm::vec2 relVelo = contact.bodyA->velocity - contact.bodyB->velocity;
		float normVelo = glm::dot(relVelo, contact.normal);

		if (normVelo > 0) continue;

		float totalInvMass = contact.bodyA->invMass + contact.bodyB->invMass;
		float impulseMagnitude = -(1.0f + contact.restitution) * normVelo / totalInvMass;

		glm::vec2 impulse = contact.normal * impulseMagnitude;
		contact.bodyA->velocity += (impulse * contact.bodyA->invMass);
		contact.bodyB->velocity -= (impulse * contact.bodyB->invMass);
	}
	
}
