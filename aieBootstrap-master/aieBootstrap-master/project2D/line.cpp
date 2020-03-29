#include "line.h"
#include <limits>

line::line(const glm::vec2& a_normal /* = { 0.0f, 1.0f }*/,
			const float a_distance /*= 0.0f*/) :
	normal(a_normal),
	distance(a_distance),
	physicsObject(shapeType::plane)
{
	set_normal(normal);
}

const glm::vec2 line::get_normal() const
{
	return normal;
}

void line::set_normal(const glm::vec2& a_normal)
{
	if (glm::length(a_normal) <= 0)
	{

	}
	else
	{
		normal = glm::normalize(a_normal);
	}
}

const float line::get_distance() const
{
	return distance;
}

void line::set_distance(const float a_distance)
{
	distance = a_distance;
}

void line::drawLine()
{
	aie::Gizmos::add2DLine(glm::vec2(10, 500), glm::vec2(10, -500), colour);
}