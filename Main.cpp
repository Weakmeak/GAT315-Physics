#include <iostream>
#include "Tests/Test.h"
#include "Tests/ParticleTest.h"
#include "Tests/ForceTest.h"
#include "Tests/JointTest.h"
#include "Tests/CollisionTest.h"

#undef main

using namespace std;

int main() {
	
	Test* test = new CollisionTest();

	test->Initialize();
	while (!test->IsQuit()) test->Run();
	delete test;
	

	return 0;
}

