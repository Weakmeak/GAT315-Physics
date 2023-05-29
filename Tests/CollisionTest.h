#pragma once
#include "Test.h"

class CollisionTest : public Test {
public:
	void Initialize() override;

	// Inherited via Test
	void Update() override;
	void FixedUpdate() override;
	void Render() override;

	class Body* m_user;
};