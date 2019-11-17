#include "Plane.h"

void Plane::NormalizePlane() {
	float Distance = sqrtf(a * a + b * b + c * c);
	a /= Distance;
	b /= Distance;
	c /= Distance;
	d /= Distance;
}

float Plane::SignedDistanceToPlane(const Plane& plane, const glm::vec3& point) const {
	return (plane.a * point.x + plane.b * point.y + plane.c * point.z + plane.d);
}

glm::vec3 Plane::ClosestPointOnPlaneFromPosition(const Plane& plane, const glm::vec3& position) const {
	glm::vec3 planeNormal = glm::vec3(plane.a, plane.b, plane.c);
	return (position - planeNormal * SignedDistanceToPlane(plane, position));
}

Plane Plane::CreatePlaneFromPointAndNormal(const glm::vec3& point, const glm::vec3& normal) {
	Plane plane;
	plane.a = normal.x;
	plane.b = normal.y;
	plane.c = normal.z;
	plane.d = -glm::dot(normal, point);
	return plane;
}
