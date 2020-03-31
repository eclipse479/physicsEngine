#include "rigidbody.h"


rigidbody::rigidbody(shapeType shapeID, glm::vec2 newPosition, glm::vec2 newVelocity, float newMass) :
	physicsObject (shapeID), m_position(newPosition), velocity(newVelocity),mass(newMass)
{
}


void rigidbody::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	applyForce(gravity * mass * timeStep);
	m_position += velocity * timeStep;
}

void rigidbody::debug()
{

}

void rigidbody::applyForce(glm::vec2 force)
{
	velocity += (force / mass);
}

void rigidbody::applySeparationForce(rigidbody* actor2, glm::vec2 force)
{
	actor2->applyForce(force);
	applyForce(-force);
}

void rigidbody::setVelocity(glm::vec2 newVelocity)
{
	velocity = newVelocity;
}

void rigidbody::setPosition(glm::vec2 newPosition)
{
	m_position = newPosition;
}

void rigidbody::resloveCollision(rigidbody* other, glm::vec2 collisionNormal)
{
	glm::vec2 normal = glm::normalize(collisionNormal);

	glm::vec2 relativeVelocity = other->getVelocity() - velocity;

	float elasticity = 1.0f;

	float j = glm::dot(-(1 + elasticity) * (relativeVelocity), normal)
							/    /*divided by*/
	glm::dot(normal, normal * ((1 / mass) + (1 / other->getMass())));

	glm::vec2 force = normal * j;
	applySeparationForce(other, force);
}