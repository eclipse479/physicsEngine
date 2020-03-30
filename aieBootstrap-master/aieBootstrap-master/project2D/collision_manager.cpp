#include "collision_manager.h"
#include <cmath>

glm::vec2 collision_manager::circle_vs_circle(const physicsObject* a_circle_A, const physicsObject* a_circle_B)
{
	const circle* c1 = dynamic_cast<const circle*>(a_circle_A);
	const circle* c2 = dynamic_cast<const circle*>(a_circle_B);

	assert(c1&&c2&&"a circle was null in collision check");

	glm::vec2 displacement = (c1->getPosition() - c2->getPosition());
	float sum_of_radii = c1->getRadius() + c2->getRadius();
	float overlap = (sum_of_radii)-glm::length(displacement);

	if (overlap > 0.0f)
	{
		return glm::normalize(displacement) * overlap;
	}
	return glm::vec2(0, 0);
}

glm::vec2 collision_manager::aabb_vs_aabb(const physicsObject* a_aabb_A, const physicsObject* a_aabb_B)
{
	const aligned_bounding_box* aabb1 = dynamic_cast<const aligned_bounding_box*>(a_aabb_A);
	const aligned_bounding_box* aabb2 = dynamic_cast<const aligned_bounding_box*>(a_aabb_B);

	const float maxOverlap = 10000000.0f;
	float overlap = maxOverlap; //<- neumeric float limit would be a better choice

	glm::vec2 overlapVector = glm::vec2(0.0f);

	//checks the X values for collision
	if (aabb1->get_max().x > aabb2->get_min().x)
	{
		float amax = aabb1->get_max().x;
		float amin = aabb2->get_min().x;
		float localOverlap = abs(aabb1->get_max().x - aabb2->get_min().x);
		if (localOverlap < overlap)
		{
			overlap = localOverlap;
			overlapVector = glm::vec2(-overlap, 0);
		}
	}
	else
	{
		return glm::vec2(0, 0);
	}

	if (aabb1->get_min().x < aabb2->get_max().x)
	{
		float localOverlap = abs(aabb1->get_min().x - aabb2->get_max().x);
		if (localOverlap < overlap)
		{
			overlap = localOverlap;
			overlapVector = glm::vec2(	overlap, 0);
		}
	}
	else
	{
		return glm::vec2(0, 0);
	}
	//checks the Y values for collision
	if (aabb1->get_max().y > aabb2->get_min().y)
	{
		float localOverlap = abs(aabb1->get_max().y - aabb2->get_min().y);
		if (localOverlap < overlap)
		{
			overlap = localOverlap;
			overlapVector = glm::vec2(0, -overlap);
		}
	}
	else
	{
		return glm::vec2(0, 0);
	}
	if (aabb1->get_min().y < aabb2->get_max().y)
	{
		float localOverlap = abs(aabb1->get_min().y - aabb2->get_max().y);
		if (localOverlap < overlap)
		{
			overlap = localOverlap;
			overlapVector = glm::vec2(0, overlap);
		}
	}
	else
	{
		return glm::vec2(0, 0);
	}
	return overlapVector;
}

glm::vec2 collision_manager::line_vs_line(const physicsObject* lineA, const physicsObject* lineB)
{
	return glm::vec2(0);
}

glm::vec2 collision_manager::aabb_vs_circle(const physicsObject* a_aabb, const physicsObject* a_circle)
{
	const aligned_bounding_box* aabb = dynamic_cast<const aligned_bounding_box*>(a_aabb);
	const circle* c = dynamic_cast<const circle*>(a_circle);

	glm::vec2 clampedCenter = glm::clamp(c->getPosition(), aabb->get_min(), aabb->get_max());

	glm::vec2 displacement = clampedCenter - c->getPosition();
	float overlap = c->getRadius() - glm::length(displacement);

	if (overlap > 0.0f)
		return glm::normalize((displacement) * overlap);
	else
		return glm::vec2(0);
}


glm::vec2 collision_manager::aabb_vs_line(const physicsObject* a_aabb, const physicsObject* a_line)
{
	const aligned_bounding_box* aabb = dynamic_cast<const aligned_bounding_box*>(a_aabb);
	const line* l = dynamic_cast<const line*>(a_line);

	glm::vec2 extents = 0.5f * aabb->get_extents();
	glm::vec2 extents_neg_x = 0.5f * glm::vec2(-aabb->get_extents().x, aabb->get_extents().y);
	;
	float dotExtents = glm::dot(extents, l->get_normal());
	float dotNegExtents = glm::dot(extents_neg_x, l->get_normal());

	float radius = fmaxf(fabsf(dotExtents), fabsf(dotNegExtents));
	circle projection(aabb->getPosition(), glm::vec2(0.0f), aabb->getMass(), radius, glm::vec4(0.0f));

	return circle_vs_line(&projection, a_line);
}


glm::vec2 collision_manager::circle_vs_aabb(const physicsObject* a_circle, const physicsObject* a_aabb)
{
	return aabb_vs_circle(a_aabb, a_circle);
}

glm::vec2 collision_manager::circle_vs_line(const physicsObject* a_circle, const physicsObject* a_line)
{
	const circle* c = dynamic_cast<const circle*>(a_circle);
	const line* l = dynamic_cast<const line*>(a_line);

	assert(c && l && "circle or line was null in collision check");

	float positionDotNormal = glm::dot(c->getPosition(), l->get_normal());

	float distance = positionDotNormal - (l->get_distance() + c->getRadius());
	if (distance < 0)
		return l->get_normal() * -distance;
	else
		return glm::vec2(0.0f);
}

glm::vec2 collision_manager::line_vs_aabb(const physicsObject* a_line, const physicsObject* a_aabb)
{
	return aabb_vs_line(a_aabb, a_line);
}

glm::vec2 collision_manager::line_vs_circle(const physicsObject* a_line, const physicsObject* a_circle)
{
	return circle_vs_line(a_circle, a_line);
}


glm::vec2 collision_manager::clamp(const glm::vec2& a_vector_2,	const glm::vec2& a_min,	const glm::vec2& a_max)
{
	return { fminf(fmaxf(a_vector_2.x, a_min.x), a_max.x),
			 fminf(fmaxf(a_vector_2.y, a_min.y), a_max.y) };
}