#define GLM_FORCE_RADIANS
#define GLM_ENABLE_EXPERIMENTAL
#include "GeomTriangle.h"

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include "Intersection.h"
#include "Ray.h"

GeomTriangle::GeomTriangle(std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals) {
    this->vertices[0] = vertices[0];
    this->vertices[1] = vertices[1];
    this->vertices[2] = vertices[2];

    this->normals[0] = normals[0];
    this->normals[1] = normals[1];
    this->normals[2] = normals[2];
}

std::vector<Intersection> GeomTriangle::intersect(Ray &ray) {
    using namespace glm;
    /**
     * NOTE: Ray is already transformed to the Model coordinate space.
     */

    // vector to store the intersections
    std::vector<Intersection> intersections;

    /**
     * TODO: Implement the Ray intersection with the current geometry
     */

    /**
     * Once you find the intersection, add it to the `intersections` vector.
     *
     * Example:
     * Suppose the ray intersects the current geometry at a point `vec3 point`
     * at a distance `float t`, and the unit normal vector at the intersection
     * point is `vec3 normal`. You would then insert an intersection into the
     * vector as follows:
     *
     * intersections.push_back({t, point, normal, this, nullptr});
     *
     * Note:
     * - Here we pass the Model pointer as `nullptr` because it will be
     *   populated by the Model::intersect() function call.
     * - Only add intersections that are in front of the camera, i.e.,
     *   where t > 0.
     */

    /**
     * TODO: Update `intersections`
     */
    // Möller–Trumbore intersection algorithm
    //solve Ax = b| x:[t,u,v]
    const float epsilon = 1e-6f;
    mat3 A(
        -ray.dir,
        this->vertices[1] - this->vertices[0],
        this->vertices[2] - this->vertices[0]
    );

    vec3 b = ray.p0 - this->vertices[0];

    float detA = determinant(A);
    vec3 x;
    if(abs(detA) < epsilon) return intersections; // parallel to the plane
    
    for(int i = 0; i < 3; ++i){
        mat3 matrix = A;
        matrix[i] = b;
        x[i] = determinant(matrix) / detA;
        matrix[i] = A[i];
    }
    if(x[0] < 0|| x[1] < 0 || x[2] < 0 || x[1] + x[2] > 1) return intersections; // outside the triangle
    vec3 point = this->vertices[0] + x[1] * A[1] + x[2] * A[2];
    vec3 normal = normalize(cross(point-this->vertices[0], point-this->vertices[1]));
    intersections.push_back({x[0], point, normal, this, nullptr});
    
    return intersections;
}