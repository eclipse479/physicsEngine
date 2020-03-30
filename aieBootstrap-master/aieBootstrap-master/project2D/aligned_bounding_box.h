#pragma once
#include "rigidbody.h"


#ifndef _ALIGNED_BOUNDING_BOX_H_
#define _ALIGNED_BOUNDING_BOX_H_

class aligned_bounding_box : public rigidbody
{
public:


	aligned_bounding_box(const glm::vec2& a_position, const glm::vec2& newVelocity,  glm::vec4 newColour, const float newMass, const glm::vec2& newExtents  = glm::vec2(1.0f));

	const glm::vec2 get_position() const;
	void set_position(const glm::vec2& a_position);

	const glm::vec2 get_extents() const;
	void set_extents(const glm::vec2& a_extents);

	const float get_width() const;
	const float get_height() const;

	const glm::vec2 get_min() const;
	const glm::vec2 get_max() const;

	void makeGizmo();
	bool checkCollision(physicsObject* otherObject);

private:
	glm::vec2 m_position{ 0.0f, 0.0f };
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