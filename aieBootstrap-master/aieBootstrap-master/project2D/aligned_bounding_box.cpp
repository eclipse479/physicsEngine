#include "aligned_bounding_box.h"
#include "collision_manager.h"
#include <cmath>



//aligned_bounding_box::aligned_bounding_box(const glm::vec2& a_position /*= vector_2()*/,
//										   const glm::vec2& a_extents /*= DEFAULT_EXTENTS*/) :
//	extents(a_extents),
//	rigidbody(shapeType::square, a_position)
//{}

aligned_bounding_box::aligned_bounding_box(const glm::vec2 a_position, glm::vec2 newVelocity, glm::vec2 newExtents, float newMass, glm::vec4 newColour) :
	rigidbody(shapeType::square, a_position, newVelocity, newMass), colour(newColour), extents(newExtents)
{

}

const glm::vec2 aligned_bounding_box::get_position() const
{
	return m_position;
}

void aligned_bounding_box::set_position(const glm::vec2& a_position)
{
	m_position = a_position;
}

const glm::vec2 aligned_bounding_box::get_extents() const
{
	return extents;
}

void aligned_bounding_box::set_extents(const glm::vec2& a_extents)
{
	extents = { abs(a_extents.x), abs(a_extents.y) };
}

const float aligned_bounding_box::get_width() const
{
	return width;
}

const float aligned_bounding_box::get_height() const
{
	return height;
}

const glm::vec2 aligned_bounding_box::get_min() const
{
	return m_position - 0.5f * extents;
}

const glm::vec2 aligned_bounding_box::get_max() const
{
	return m_position + 0.5f * extents;
}

void aligned_bounding_box::makeGizmo()
{
	aie::Gizmos::add2DAABBFilled(position, (extents * 0.5f), colour);
}

bool aligned_bounding_box::checkCollision(physicsObject* otherObject)
{
	return collision_manager::aabb_vs_circle(*this, (circle&)*otherObject);
}