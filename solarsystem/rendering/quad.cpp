#include "quad.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

rendering::Quad::Quad() {

	glGenVertexArrays(1, &m_vao);
	
	unsigned int buffers[2];
	glGenBuffers(2, buffers);
	m_vbo = buffers[0], m_ebo = buffers[1];

	float vertices[] = {
		 1.0f,  1.0f, 0.0f, 1.0f, 0.0f,
		 1.0f,  0.0f, 0.0f, 1.0f, 1.0f,
		 0.0f,  0.0f, 0.0f, 0.0f, 1.0f,
		 0.0f,  1.0f, 0.0f, 0.0f, 0.0f
	};

	unsigned int indices[] = { 3, 2, 1, 3, 1, 0 };

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void rendering::Quad::draw() {
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void rendering::Quad::bind_vao() {
	glBindVertexArray(m_vao);
}