#pragma once
#include "Contact.h"
#include "../Body.h"
#include <vector>

namespace Collision {
	Contact GenerateContact(Body* BodyA, Body* BodyB);
	void CreateContacts(std::vector<Body*> bods, std::vector<Contact>& cons);
	
	void SeparateContacts(std::vector<Contact>& contacts);
	void ResolveContacts(std::vector<Contact>& contacts);
}