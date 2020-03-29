#pragma once
#ifndef _RIGID_BODY_H_
#define _RIGID_BODY_H_


#include "glm/glm.hpp"
#include "physicsObject.h"


class rigidbody :	public physicsObject
{
public:

    glm::vec2 position = glm::vec2 (0,0);
    glm::vec2 velocity = glm::vec2(0, 0);
    float mass = 1.0f;

    ~rigidbody() {};
    
    virtual void fixedUpdate(glm::vec2 gravity, float timeStep); 
    
    virtual void debug(); 
    
    virtual bool checkCollision(physicsObject* pOther) = 0;
    
    void applyForce(glm::vec2 force);
    void applySeparationForce(rigidbody* actor2, glm::vec2 force); 
    
    glm::vec2 getPosition() const { return position; }
    glm::vec2 getVelocity() const { return velocity; }
    float getMass() { return mass; }
        
protected:
    rigidbody(shapeType shapeID, glm::vec2 newPosition, glm::vec2 newVelocity, float newMass);


    rigidbody(shapeType a_shape, const glm::vec2& newPosition) : position(newPosition), physicsObject(a_shape) {}
};

#endif // !1