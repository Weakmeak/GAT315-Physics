#include "ForceGenerator.h"
#include "Body.h"
#include "../Engine/Graphics.h"

void ForceGenerator::Draw(Graphics* graphics)
{
	if (m_body) m_body->Draw(graphics);
}
