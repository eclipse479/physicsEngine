#pragma once
#include "physicsObject.h"

class rigidbody;

#ifndef _LINE_H_
#define _LINE_H_

class line : public physicsObject
{
public:

	line(glm::vec4 newColour, const glm::vec2& a_normal,
		 const float a_distance = 0.0f);

	const glm::vec2 getNormal() const;
	void setNormal(const glm::vec2& a_normal);

	const float getDistance() const;
	void setDistance(const float a_distance);

	virtual void debug() override {}
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) override {};
	virtual void makeGizmo() override;
	void resloveCollision(rigidbody* other);
private:
	glm::vec2 normal = glm::vec2(0, 1);
	glm::vec2 center = glm::vec2(0, 0);
	glm::vec4 colour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	float distance = 0.0f;
};


#endif // _LINE_H_