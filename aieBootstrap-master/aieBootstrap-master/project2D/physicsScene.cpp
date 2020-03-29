#include "physicsScene.h"
#include "physicsObject.h"
#include <list>
#include <algorithm>

physicsScene::physicsScene() : timeStep(0.01f), gravity(glm::vec2(0,0))
{

}

physicsScene::~physicsScene()
{
	while (!objects.empty())
	{
		objects.erase(objects.end());
	}
}

void physicsScene::addActor(physicsObject* actor)
{
	objects.push_back(actor);
}

void physicsScene::removeActor(physicsObject* actor)
{
	auto location = std::find(objects.begin(),objects.end(),actor);
	objects.erase(location);
	delete actor;
	actor = nullptr;
}

void physicsScene::update(float deltaTime)
{
	
	acculimlatedTime += deltaTime;
	while (acculimlatedTime >= timeStep)
	{
		for (auto theObjects : objects)
		{
			theObjects->fixedUpdate(gravity, timeStep);
		}
		acculimlatedTime -= timeStep;
	}
		static std::list<physicsObject*> dirty;

		for (auto object : objects)
		{ 
			for (auto otherObject : objects)
			{ 
				if (object == otherObject)
					continue; 

				if (std::find(dirty.begin(), dirty.end(), object) != dirty.end() && 
					std::find(dirty.begin(), dirty.end(), otherObject) != dirty.end())
					continue;

				rigidbody* objectRigidbody = dynamic_cast<rigidbody*>(otherObject);

				if (objectRigidbody->checkCollision(object)) 
				{
					objectRigidbody->applySeparationForce(dynamic_cast<rigidbody*>(object), objectRigidbody->getVelocity() * objectRigidbody->getMass()); 
					dirty.push_back(objectRigidbody); 
					dirty.push_back(otherObject); 
				}
			} 
		}
		dirty.clear();

}


void physicsScene::updateGizmos()
{
	for (auto theObjects : objects)
	{
		theObjects->makeGizmo();
	}
}

void physicsScene::setGravity(glm::vec2 newGravity)
{
	gravity = newGravity;
}
