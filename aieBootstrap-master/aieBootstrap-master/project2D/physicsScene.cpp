#include "physicsScene.h"
#include "physicsObject.h"
#include "collision_manager.h"
#include <list>
#include <algorithm>

const collisionFunction physicsScene::collisionFunctionArray[] =
{
	collision_manager::circle_vs_circle, collision_manager::circle_vs_aabb, collision_manager::circle_vs_line,
	collision_manager::aabb_vs_circle,   collision_manager::aabb_vs_aabb,   collision_manager::aabb_vs_line,
	collision_manager::line_vs_circle,   collision_manager::line_vs_aabb,   collision_manager::line_vs_line,
};

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
		int objectCount = objects.size();

		for (int outer = 0; outer < objectCount-1;outer++)
		{
			for (int inner = outer+1;inner < objectCount; inner++)
			{
				physicsObject* object1 = objects[outer];
				physicsObject* object2 = objects[inner];

				int shapeID1 = (int)object1->getShape();
				int shapeID2 = (int)object2->getShape();


				int functionIndex = (int(shapeID1) * int(shapeType::shapeCount)) + int(shapeID2);
				collisionFunction collisionFunctionPtr = collisionFunctionArray[collisionFunctionPtr];
				if (collisionFunctionPtr != nullptr)
				{
					auto  result = collisionFunctionPtr(object1, object2);
					if (glm::length(result) > 0.001f)
					{
						int dummyAssignmentForDebugMode = 1;
					}
				}
			}
		}
		/*for (auto object : objects)
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
		}*/
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
