#pragma once
#include "Shape.h" 
class CircleShape : public Shape {
	public:
		CircleShape(float radius, const glm::vec4& Color) : radius{ radius }, Shape(Color) {}
		virtual void Draw(Graphics* Graphics, const glm::vec2& position) override;
	public:
		float radius;
};