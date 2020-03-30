#pragma once
#include "glm/glm.hpp"
#include "Gizmos.h"

enum class shapeType : char
{
    //none = 0,
    circle = 0,
    square,
    plane,
    shapeCount
};

class physicsObject
{
protected:
    shapeType theShape;
    physicsObject(shapeType a_shape) 
    {
        theShape = a_shape;
    }

public:
    virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0;
    virtual void debug() = 0;
    virtual void makeGizmo() = 0;
    virtual void resetPosition() {};
    shapeType getShape() { return theShape;}
};