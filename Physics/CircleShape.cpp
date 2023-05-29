#include "CircleShape.h"
#include "../Engine/Graphics.h"

void CircleShape::Draw(Graphics* Graphics, const glm::vec2& position)
{
	int r = Graphics->WorldToPixels(radius);
	Graphics->DrawFilledCircle(Graphics->WorldToScreen(position), r, color);
}
