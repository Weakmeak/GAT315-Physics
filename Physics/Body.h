#pragma once
#include <glm/glm.hpp>

class Body {
	public:
		enum BodyType
		{
			Static, //Unmoving
			Kinematic, //Moved via input
			Dynamic //Physics based
		};
	public:
		Body(class Shape* Shape, const glm::vec2& pos, const glm::vec2& velo = {0.0f, 0.0f}, float mass = 1, BodyType type = BodyType::Dynamic) :
			shape{ Shape }, 
			position{ pos }, 
			velocity{ velo },
			mass {mass},
			type {type}
		{
			//if (type == Static) this->mass = 0;
			invMass = (mass == 0 || type != BodyType::Dynamic) ? 0.0f : (1.0f / mass);
		};

		void Step(float dT);
		void Draw(class Graphics* graphics);

		void applyForce(const glm::vec2& Force);
		void clearForce() { force = { 0,0 }; };

		bool Intersects(class Body* body);

	public:
		class Shape* shape{nullptr};

		glm::vec2 position{ 0,0 };
		glm::vec2 velocity{ 0,0 };
		glm::vec2 force{ 0,0 };

		BodyType type{ BodyType::Dynamic };

		float mass{ 1 };
		float invMass{ 1 };
		float damping{ 0.1f };
		float gravityScale{ 1.0f };
		float restitution{ 0.33f };
};