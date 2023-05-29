#pragma once
#include <glm/glm.hpp>

class Shape {
	public:
		Shape() {};
		Shape(glm::vec4 Color) : color{ Color } {};

		virtual void Draw(class Graphics* Graphics, const glm::vec2& position) = 0;
	public:
		float size{ 1 };
		glm::vec4 color{ 1, 1, 1, 1 };
};