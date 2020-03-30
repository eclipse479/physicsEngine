#pragma once
#include "circle.h"
#include "line.h"
#include "aligned_bounding_box.h"


class collision_manager
{
public:
	static glm::vec2 circle_vs_circle(const physicsObject& a_circle_A,
								      const physicsObject& a_circle_B);

	static glm::vec2 aabb_vs_aabb(const physicsObject& a_aabb_A,
						          const physicsObject& a_aabb_B);

	static glm::vec2 line_vs_line(const physicsObject& lineA,
								  const physicsObject& lineB);

	static glm::vec2 aabb_vs_circle(const physicsObject& a_aabb,
							        const physicsObject& a_circle);

	static glm::vec2 aabb_vs_line(const physicsObject& a_aabb,
							      const physicsObject& a_line);

	static glm::vec2 circle_vs_aabb(const physicsObject& a_circle,
									const physicsObject& a_aabb);

	static glm::vec2 circle_vs_line(const physicsObject& a_circle,
							        const physicsObject& a_line);

	static glm::vec2 line_vs_circle(const physicsObject& a_line,
									const physicsObject& a_circle);

	static glm::vec2 line_vs_aabb(const physicsObject& a_line,
								  const physicsObject& a_aabb);


private:
	static glm::vec2 clamp(const glm::vec2& a_vector_2,
						   const glm::vec2& a_min,
						   const glm::vec2& a_max);
};

