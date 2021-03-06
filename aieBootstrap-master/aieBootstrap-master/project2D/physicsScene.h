#pragma once
#include "glm\glm.hpp"
#include "physicsObject.h"
#include "rigidbody.h"
#include "collision_manager.h"
#include <vector>
#include <functional>
using collisionFunction = std::function < glm::vec2(const physicsObject*, const physicsObject*)>;


class physicsObject;

class physicsScene
{
public:
	physicsScene();
	~physicsScene();

	void addActor(physicsObject* actor);
	void removeActor(physicsObject* actor);
	void update(float deltaTime);
	void updateGizmos();

	void setGravity(glm::vec2 newGravity);
	glm::vec2 getGravity() const { return gravity; }

	void setTimeStep(const float newTimeStep) {timeStep = newTimeStep; }
	float getTimeStep() const { return timeStep; }

	

	static const collisionFunction collisionFunctionArray[];
	
private:
	glm::vec2 gravity;
	float timeStep;
	std::vector<physicsObject*> objects;
	float acculimlatedTime = 0.0f;
};

