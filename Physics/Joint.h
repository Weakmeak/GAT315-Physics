#pragma once

class Body;
class Graphics;
class Joint
{
	public:
		Joint(Body* BodA, Body* BodB, float stiffness, float restLength = 0);
		void Step(float dt);
		void Draw(Graphics* graphics);
	protected:
		float m_restLength{ 0 };
		float m_stiffness{ 0 };

		Body* BodyA{ nullptr };
		Body* BodyB{ nullptr };
};

