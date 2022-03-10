#ifndef MOUSE_PICKER_H
#define MOUSE_PICKER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace objects {
	class MousePIcker {
	private:
		glm::vec3 m_current_ray;
		glm::mat4 projection_matrix;
		glm::mat4 view_matrix;
		
		void calculate_ray();

	public:
		MousePIcker(glm::mat4 projection);

		glm::vec3 get_current_ray();

		void update();
	};
}

#endif // !MOUSE_PICKER_H
