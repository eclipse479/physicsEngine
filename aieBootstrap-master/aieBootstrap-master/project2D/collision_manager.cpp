#include "collision_manager.h"
#include <cmath>

glm::vec2 collision_manager::circle_vs_circle(const physicsObject& a_circle_A, const physicsObject& a_circle_B)
{
	const circle* c1 = dynamic_cast<const circle*>(a_circle_A);
	const circle* c2 = dynamic_cast<const circle*>(a_circle_B);

	assert(c1&&c2&&"a circle was null in collision check");

	glm::vec2 displacement = (c1.getPosition() - c2.getPosition());
	float sum_of_radii = c1.getRadius() + c2.getRadius();
	float overlap = (sum_of_radii)-glm::length(displacement);

	if (overlap > 0.0f)
	{
		return glm::normalize(displacement) * overlap;
	}
	return glm::vec2(0, 0);
}

glm::vec2 collision_manager::aabb_vs_aabb(const physicsObject& a_aabb_A, const physicsObject& a_aabb_B)
{
	return glm::vec2(0);
}

glm::vec2 collision_manager::line_vs_line(const physicsObject& lineA, const physicsObject& lineB)
{
	return glm::vec2(0);
}

glm::vec2 collision_manager::aabb_vs_circle(const physicsObject& a_aabb, const physicsObject& a_circle)
{
return glm::vec2(0);

}


glm::vec2 collision_manager::aabb_vs_line(const physicsObject& a_aabb, const physicsObject& a_line)
{
	/*const aligned_bounding_box* aabb1 = dynamic_cast<const aligned_bounding_box*>(a_aabb);
	const aligned_bounding_box* aabb2 = dynamic_cast<const aligned_bounding_box*>(a_line);

	glm::vec2 extents = 0.5 * a_aabb.getExtents();
	glm::vec2 extents_neg_x = 0.5 *  glm::vec2()*/
	return glm::vec2(0);
}


glm::vec2 collision_manager::circle_vs_aabb(const physicsObject& a_circle, const physicsObject& a_aabb)
{

	return glm::vec2(0, 0);
}

glm::vec2 collision_manager::circle_vs_line(const physicsObject& a_circle, const physicsObject& a_line)
{
	const circle* c = dynamic_cast<const circle*>(a_circle);
	const line* l = dynamic_cast<const line*>(a_line);

	assert(c && l && "circle or line was null in collision check");

	float positionDotNormal = c.getPosition().dot(l.getNormal());
	float distance = positionDotNormal - (l.getDistance() + c.getRadius());
	if (distance < 0)
		return l->get_normal() * distance;
	else
		return glm::vec2(0.0f);
}

glm::vec2 collision_manager::line_vs_aabb(const physicsObject& a_line, const physicsObject& a_aabb)
{
	return glm::vec2(0);
}

glm::vec2 collision_manager::line_vs_circle(const physicsObject& a_line, const physicsObject& a_circle)
{
	return glm::vec2(0);
}


glm::vec2 collision_manager::clamp(
			const glm::vec2& a_vector_2,
			const glm::vec2& a_min,
			const glm::vec2& a_max)
{
	return { fminf(fmaxf(a_vector_2.x, a_min.x), a_max.x),
			 fminf(fmaxf(a_vector_2.y, a_min.y), a_max.y) };
}