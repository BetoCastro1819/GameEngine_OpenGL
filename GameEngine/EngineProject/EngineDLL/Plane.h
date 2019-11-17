#pragma once
#include "glm/glm.hpp"

struct Plane {
	float a, b, c, d;

	void NormalizePlane();
	float SignedDistanceToPlane(const Plane& plane, const glm::vec3& point) const;
	glm::vec3 ClosestPointOnPlaneFromPosition(const Plane& plane, const glm::vec3& position) const;
	Plane CreatePlaneFromPointAndNormal(const glm::vec3& point, const glm::vec3& normal);
};


