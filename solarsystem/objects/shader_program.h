#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace objects {

	class ShaderProgram {
	public:
		ShaderProgram(const char* vertexPath, const char* fragmentPath, const char* geometryPath);
		ShaderProgram(const char* vertexPath, const char* fragmentPath);

		void use() const;
		unsigned int get_program() const;

		void set_int(const char* name, int value) const;
		void set_float(const char* name, float value) const;
		void set_vec2(const char* name, float x, float y) const;
		void set_vec2(const char* name, glm::vec2 vec) const;
		void set_vec3(const char* name, float x, float y, float z) const;
		void set_vec3(const char* name, glm::vec3 vec) const;
		void set_mat4(const char* name, glm::mat4 value) const;

	private:
		unsigned int m_program;
	};

}

#endif // !SHADER_PROGRAM_H
