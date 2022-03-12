#include "camera.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

// implementation modifed from https://github.com/JoeyDeVries/LearnOpenGL

objects::Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 worldUp) :
	m_position(position), m_map_position(0.0f, 10.0f, 0.0f), m_front(front), m_worldUp(worldUp),
	m_yaw(-90.0f), m_pitch(0.0f), m_map_pitch(-89.0f), m_speed(2.5f), m_sensitivity(0.1f), m_zoom(45.0f), m_map_mode(false) {
	update_camera_vectors();
}

glm::mat4 objects::Camera::get_view_matrix() {
	return glm::lookAt(m_position, m_position + m_front, m_up);
}

void objects::Camera::process_keyboard_input(CameraDirection direction, float time_span)
{
    float velocity = m_speed * time_span;

    glm::vec3 front = m_front;

    if (m_map_mode) front = glm::normalize(glm::cross(m_worldUp, m_right));

    if (direction == CameraDirection::FORWARD)
        m_position += front * velocity;
    if (direction == CameraDirection::BACKWARD)
        m_position -= front * velocity;
    if (direction == CameraDirection::LEFT)
        m_position -= m_right * velocity;
    if (direction == CameraDirection::RIGHT)
        m_position += m_right * velocity;
    if (direction == CameraDirection::UP)
        m_position += m_worldUp * velocity;
    if (direction == CameraDirection::DOWN)
        m_position -= m_worldUp * velocity;
}

void objects::Camera::process_mouse_movement(float xoffset, float yoffset, bool constrain_pitch) {
    xoffset *= m_sensitivity;
    yoffset *= m_sensitivity;

    m_yaw += xoffset;
    m_pitch += yoffset;

    // constrain the pitch between 89 and -89 degrees
    if (constrain_pitch)
    {
        if (m_pitch > 89.0f)
            m_pitch = 89.0f;
        if (m_pitch < -89.0f)
            m_pitch = -89.0f;
    }

    update_camera_vectors();
}

void objects::Camera::process_mouse_scroll(float offset) {
    m_zoom -= offset;
    if (m_zoom < 1.0f)
        m_zoom = 1.0f;
    if (m_zoom > 45.0f)
        m_zoom = 45.0f;
}

void objects::Camera::update_camera_vectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

    m_front = glm::normalize(front);
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}

void objects::Camera::toggle_map_mode() {
    glm::vec3 temp = m_position;
    m_position = m_map_position;
    m_map_position = temp;

    float tmp = m_pitch;
    m_pitch = m_map_pitch;
    m_map_pitch = tmp;

    m_map_mode = !m_map_mode;

    update_camera_vectors();

}