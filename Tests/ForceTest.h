#pragma once
#include "Test.h"

class ForceTest : public Test {
public:
	void Initialize() override;

	// Inherited via Test
	void Update() override;
	void FixedUpdate() override;
	void Render() override;
};