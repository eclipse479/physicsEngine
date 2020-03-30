#include "rigidbody.h"


rigidbody::rigidbody(shapeType shapeID, glm::vec2 newPosition, glm::vec2 newVelocity, float newMass) :
	physicsObject (shapeID), position(newPosition), velocity(newVelocity),mass(newMass)
{
}


void rigidbody::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	applyForce(gravity * mass * timeStep);
	position += velocity * timeStep;
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
	position = newPosition;
}