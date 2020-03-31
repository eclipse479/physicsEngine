#pragma once
#include "rigidbody.h"
#ifndef _CIRCLE_H_
#define _CIRCLE_H_


class circle : public rigidbody
{
public:
	

	circle(const glm::vec2 a_position, glm::vec2 newVelocity, float newMass, float newRadius, glm::vec4 newColour);
	~circle();
	const float getRadius() const;
	
	/*	@brief Sets the radius to the absolute value of the argument
		@param The new radius as float
	*/
	void setRadius(const float a_radius);

	glm::vec4 getColour();

	virtual void makeGizmo();
	void debug() {}
private:
	float radius = 0.0f;
	glm::vec4 colour = glm::vec4(1,1,1,1);
	};



#endif // !_CIRCLE_H_