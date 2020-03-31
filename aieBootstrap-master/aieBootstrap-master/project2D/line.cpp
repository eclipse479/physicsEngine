#include "line.h"
#include "rigidbody.h"
#include <limits>

line::line(glm::vec4 newColour, const glm::vec2& a_normal,	const float a_distance /*= 0.0f*/) :
	normal(a_normal),
	distance(a_distance),
	colour(newColour),
	physicsObject(shapeType::plane)
{
	setNormal(normal);
}

const glm::vec2 line::getNormal() const
{
	return normal;
}

void line::setNormal(const glm::vec2& a_normal)
{
	if (glm::length(a_normal) <= 0)
	{

	}
	else
	{
		normal = glm::normalize(a_normal);
	}
}

const float line::getDistance() const
{
	return distance;
}

void line::setDistance(const float a_distance)
{
	distance = a_distance;
}

void line::makeGizmo()
{
	center = normal * distance;
	glm::vec2 drawDirection(normal.y, - normal.x);
	aie::Gizmos::add2DLine((center + (drawDirection * 500.0f)), (center - (drawDirection * 500.0f)), colour);
}

void line::resloveCollision(rigidbody* other)
{

	glm::vec2 relativeVelocity = other->getVelocity();

	float elasticity = 1.0f;

	float j = glm::dot(-(1 + elasticity) * (relativeVelocity), normal)
								/    /*divided by*/
		glm::dot(normal, normal * (1 / other->getMass()));

	glm::vec2 force = normal * j;
	other->applyForce(force);
}