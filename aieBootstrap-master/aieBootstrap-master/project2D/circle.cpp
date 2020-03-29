#include "circle.h"
#include <cmath>
#include "collision_manager.h"
#include <iostream>


circle::circle(const glm::vec2 a_position, glm::vec2 newVelocity, float newMass, float newRadius, glm::vec4 newColour):
	rigidbody(shapeType::circle, a_position, newVelocity, newMass), radius(newRadius), colour(newColour)
{

}

circle::~circle(){}

const float circle::getRadius() const
{
	return radius;
}
void circle::set_radius(const float a_radius)
{
	radius = abs(a_radius);
}

bool circle::checkCollision(physicsObject* otherObject)
{
		return collision_manager::circle_vs_circle(*this, (circle&)*otherObject);
}

bool circle::checkLineCollision(physicsObject* otherObject)//added
{
	return collision_manager::circle_vs_line(*this,(line&)*otherObject);
}

void circle::makeGizmo()
{
	aie::Gizmos::add2DCircle(position, radius, 32, colour);
}

glm::vec4 circle::getColour()
{
	return colour;
}