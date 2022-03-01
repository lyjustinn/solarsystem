#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace objects {
    enum class CameraDirection {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    class Camera {
    public:
        glm::vec3 m_position;
        glm::vec3 m_front;
        glm::vec3 m_up;
        glm::vec3 m_right;
        glm::vec3 m_worldUp;

        float m_yaw;
        float m_pitch;

        float m_speed;
        float m_sensitivity;
        float m_zoom;

        Camera(glm::vec3 position, glm::vec3 front, glm::vec3 worldUp);

        glm::mat4 get_view_matrix();
        void process_keyboard_input(CameraDirection direction, float timeSpan);
        void process_mouse_movement(float xOffset, float yOffset, bool constrainPitch);
        void process_mouse_scroll(float scrollOffset);

    private:

        void update_camera_vectors();

    };
}

#endif // !CAMERA_H
