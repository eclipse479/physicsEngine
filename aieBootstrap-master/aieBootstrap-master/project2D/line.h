#pragma once
#include "physicsObject.h"


#ifndef _LINE_H_
#define _LINE_H_

class line : physicsObject
{
public:

	line(const glm::vec2& a_normal,
		 const float a_distance = 0.0f);

	const glm::vec2 get_normal() const;
	void set_normal(const glm::vec2& a_normal);

	const float get_distance() const;
	void set_distance(const float a_distance);
	void drawLine();
private:
	glm::vec2 normal = glm::vec2(0, 1);
	glm::vec2 center = glm::vec2(0, 0);
	glm::vec4 colour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	float distance = 0.0f;
};


#endif // _LINE_H_