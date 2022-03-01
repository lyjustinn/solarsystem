#include "sphere.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>
#include <tuple>
#include <iostream>

rendering::Sphere::Sphere() {
    unsigned int vbo;
    glGenVertexArrays(1, &m_vao);

    const float PI = 3.14159265359f;

    std::vector<glm::vec3> positions;
    std::vector<unsigned int> indices;

    std::vector<float> data;
    const unsigned int segments = 8;

    const float cos45 = glm::cos(PI * 0.25f);

    for (int y = 0; y < segments; y++) {

        for (int x = 0; x < y; x++) {
            triangulate(x, y, segments, positions);
            triangulate(x, y + 1, segments, positions);
            triangulate(x + 1, y + 1, segments, positions);

            triangulate(x, y, segments, positions);
            triangulate(x + 1, y, segments, positions);
            triangulate(x + 1, y + 1, segments, positions);
        }

        triangulate(y, y, segments, positions);
        triangulate(y, y + 1, segments, positions);
        triangulate(y + 1, y + 1, segments, positions);
    }

    std::vector < std::tuple <float, float, float >> cardinalities;
    cardinalities.emplace_back(1.0f, 1.0f, 1.0f);
    cardinalities.emplace_back(1.0f, -1.0f, 1.0f);
    cardinalities.emplace_back(1.0f, 1.0f, -1.0f);
    cardinalities.emplace_back(1.0f, -1.0f, -1.0f);
    cardinalities.emplace_back(-1.0f, 1.0f, 1.0f);
    cardinalities.emplace_back(-1.0f, -1.0f, 1.0f);
    cardinalities.emplace_back(-1.0f, 1.0f, -1.0f);
    cardinalities.emplace_back(-1.0f, -1.0f, -1.0f);

    for (std::vector < std::tuple <float, float, float >>::const_iterator i = cardinalities.begin(); i != cardinalities.end(); ++i) {
        for (glm::vec3 point : positions) {
            data.push_back(std::get<0>(*i) * point.x);
            data.push_back(std::get<1>(*i) * point.y);
            data.push_back(std::get<2>(*i) * point.z);
        }
    }

    glBindVertexArray(m_vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    m_vertex_count = static_cast<unsigned int>(data.size()) / 3;

    std::cout << "sphere vao: " << m_vao << std::endl;
    std::cout << m_vertex_count << std::endl;
}

void rendering::Sphere::draw_sphere() {
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, m_vertex_count);
    glBindVertexArray(0);
}

void rendering::Sphere::triangulate(float x, float y, const int segments, std::vector<glm::vec3>& data) {

    const float PI = 3.14159265359f;
    const float cos45 = glm::cos(PI * 0.25f);

    float ySeg = (float)y / (float)segments;
    float distance = ySeg / cos45;

    float xSeg = y == 0 ? 0 : (float)x / (float)y;
    float zSeg = y == 0 ? 0 : (float)(y - x) / (float)y;

    float xCoord = xSeg * distance * cos45;
    float yCoord = 1.0f - ySeg;
    float zCoord = zSeg * distance * cos45;

    float radialDistance = glm::distance(glm::vec3(xCoord, zCoord, yCoord), glm::vec3(0.0f));

    xCoord /= radialDistance;
    yCoord /= radialDistance;
    zCoord /= radialDistance;

    // push back top point of triangle
    data.push_back(glm::vec3(xCoord, yCoord, zCoord));
}
