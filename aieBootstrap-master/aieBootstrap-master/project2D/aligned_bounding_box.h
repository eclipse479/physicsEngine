#pragma once
#include "rigidbody.h"


#ifndef _ALIGNED_BOUNDING_BOX_H_
#define _ALIGNED_BOUNDING_BOX_H_

class aligned_bounding_box : public rigidbody
{
public:


	aligned_bounding_box(const glm::vec2& a_position, const glm::vec2& newVelocity,  glm::vec4 newColour, const float newMass, const glm::vec2& newExtents  = glm::vec2(1.0f));

	const glm::vec2 getPosition() const;
	void setPosition(const glm::vec2& a_position);

	const glm::vec2 getExtents() const;
	void setExtents(const glm::vec2& a_extents);

	const float getWidth() const;
	const float getHeight() const;

	const glm::vec2 getMin() const;
	const glm::vec2 getMax() const;

	void debug() {}
	void makeGizmo();

private:
	//union -> vec2 extents and width/height float share the same memory
	union
	{
		glm::vec2 extents;
		struct
		{
			float width;
			float height;
		};
	};
	glm::vec4 colour = glm::vec4(1.0f);
};


#endif // !_ALIGNED_BOUNDING_BOX_H_