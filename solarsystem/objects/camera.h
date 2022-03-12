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
        glm::vec3 m_map_position;
        glm::vec3 m_front;
        glm::vec3 m_up;
        glm::vec3 m_right;
        glm::vec3 m_worldUp;

        float m_yaw;
        float m_pitch;
        float m_map_pitch;

        float m_speed;
        float m_sensitivity;
        float m_zoom;

        bool m_map_mode;

        Camera(glm::vec3 position, glm::vec3 front, glm::vec3 worldUp);

        glm::mat4 get_view_matrix();
        void process_keyboard_input(CameraDirection, float );
        void process_mouse_movement(float xoffset, float yoffset, bool constain_pitch = true);
        void process_mouse_scroll(float scroll_offset);
        void toggle_map_mode();

    private:

        void update_camera_vectors();

    };
}

#endif // !CAMERA_H
