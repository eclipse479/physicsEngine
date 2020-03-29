#pragma once
#include "circle.h"
#include "line.h"
#include "aligned_bounding_box.h"


class collision_manager
{
public:
	static bool circle_vs_circle(const circle& a_circle_A,
								 const circle& a_circle_B);

	static bool aabb_vs_aabb(const aligned_bounding_box& a_aabb_A,
							 const aligned_bounding_box& a_aabb_B);

	static bool aabb_vs_circle(const aligned_bounding_box& a_aabb,
							   const circle& a_circle);

	static bool circle_vs_line(const circle& a_circle,
							   const line& a_line);

	static bool aabb_vs_line(const aligned_bounding_box& a_aabb,
							 const line& a_line);

private:
	static glm::vec2 clamp(const glm::vec2& a_vector_2,
						  const glm::vec2& a_min,
						  const glm::vec2& a_max);
};

