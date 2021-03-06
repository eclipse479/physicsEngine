#include "physicsScene.h"
#include "physicsObject.h"
#include "collision_manager.h"
#include <list>
#include <algorithm>

//all the possible collisions between objects
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
	//removes all objects starting from the back of the list
	for( int i = 0; i < objects.size(); ++i)
	{
		delete objects[i];
		objects[i] = nullptr;
	}
	objects.clear();
}

void physicsScene::addActor(physicsObject* actor)
{
	//add object to teh back of the list
	objects.push_back(actor);
}

void physicsScene::removeActor(physicsObject* actor)
{
	//removes specified actor from list
	auto location = std::find(objects.begin(),objects.end(),actor);
	objects.erase(location);
	delete actor;
	actor = nullptr;
}

void physicsScene::update(float deltaTime)
{
	
	acculimlatedTime += deltaTime;
	//only happens on the time step
	while (acculimlatedTime >= timeStep)
	{
		for (auto theObjects : objects)
		{
			theObjects->fixedUpdate(gravity, timeStep);
		}
		acculimlatedTime -= timeStep;
	}
		static std::list<physicsObject*> dirty;
		//how many objects are in the physics scene
		size_t objectCount = objects.size();

		for (size_t outer = 0; outer < objectCount - 1;outer++)
		{
			for (size_t inner = outer + 1; inner < objectCount; inner++)
			{
				//grabs the colliding objects
				physicsObject* object1 = objects[outer];
				physicsObject* object2 = objects[inner];
				//gets the shape type of the objects
				int shapeID1 = (int)object1->getShape();
				int shapeID2 = (int)object2->getShape();

				//using function pointers
				int functionIndex = (int(shapeID1) * int(shapeType::shapeCount)) + int(shapeID2);
				collisionFunction collisionFunctionPtr = collisionFunctionArray[functionIndex]; // calls the collision check between the two objects
				if (collisionFunctionPtr != nullptr)
				{
					auto  result = collisionFunctionPtr(object1, object2);
					if (glm::length(result) > 0.001f)
					{
						//checks if the objects have a rigidbody
						rigidbody* r1 = dynamic_cast<rigidbody*>(object1);
						rigidbody* r2 = dynamic_cast<rigidbody*>(object2);


						if (r1 && r2)//if both ahave a rigidbody
						{
							//separates objects 
							r1->setPosition(r1->getPosition() + 0.5f * result);
							r2->setPosition(r2->getPosition() - 0.5f * result);
							//apply force for bounce
							r1->resloveCollision(r2, result);
						}
						else if (r1)//if only r1 ahave a rigidbody
						{
							r1->setPosition(r1->getPosition() + 0.5f * result);
							line* l = dynamic_cast<line*>(object2);
							l->resloveCollision(r1);
						
						}
						else if (r2)//if only r2 ahave a rigidbody
						{
							r2->setPosition(r2->getPosition() - 0.5f * result);
							line* l = dynamic_cast<line*>(object1);
							l->resloveCollision(r2);
						}
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
	//calls each objects makeGizmo function to draw it in its new place each frame
	for (auto theObjects : objects)
	{
		theObjects->makeGizmo();
	}
}

void physicsScene::setGravity(glm::vec2 newGravity)
{
	gravity = newGravity;
}
