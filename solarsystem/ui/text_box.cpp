#include "text_box.h"
#include "../rendering/render.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

ui::TextBox::TextBox(glm::vec3 colour, glm::vec3 position, rendering::Quad& quad, 
	objects::ShaderProgram& shader, const char * font, std::string text, float scale):
	Element(0, 0, colour, position, quad, shader), m_glyphs(ui::load_font(font))
    , m_text(text), m_scale(scale) {
	
    std::string::const_iterator c;
    for (c = m_text.begin(); c != m_text.end(); c++) {
        Glyph ch = m_glyphs[*c];

        float h = ch.height * m_scale;

        m_width += ((ch.advance >> 6)) * m_scale;
        m_height = std::max(m_height, h);
    }
    m_width /= rendering::scr_width / 2.0f;
    m_height /= rendering::scr_height / 2.0f;
}

void ui::TextBox::draw() {
    m_shader.use();
    glm::mat4 projection = glm::ortho(0.0f, (float)rendering::scr_width, 0.0f, (float)rendering::scr_height, 0.0f, 100.0f);
    m_shader.set_mat4("u_projection", projection);
    m_shader.set_vec3("u_colour", m_colour);
    glActiveTexture(GL_TEXTURE0);
    m_quad.bind_vao();

    float x = (rendering::scr_width + m_position.x * (float)rendering::scr_width)/2.0f;
    float y = (rendering::scr_height + m_position.y * (float)rendering::scr_height)/2.0f;

    std::string::const_iterator c;
    for (c = m_text.begin(); c != m_text.end(); c++) {
        Glyph ch = m_glyphs[*c];

        float xpos = x  + ch.bearing.x * m_scale;
        float ypos = y - (ch.height - ch.bearing.y) * m_scale;

        float w = ch.width * m_scale;
        float h = ch.height * m_scale;

        glBindTexture(GL_TEXTURE_2D, ch.texture);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDepthFunc(GL_ALWAYS);
        m_shader.use();
        glm::mat4 model = glm::mat4(1.0f);

        model = glm::translate(model, glm::vec3(xpos, ypos, 0.0f));
        model = glm::scale(model, glm::vec3(w, h, 0.0f));
        m_shader.set_mat4("u_model", model);
        m_shader.set_vec3("u_colour", m_colour);
        m_quad.draw();
        glDepthFunc(GL_LESS);
        glDisable(GL_BLEND);

        x += ((ch.advance >> 6 )) * m_scale;

        //std::cout << (ch.advance >> 6) << std::endl;
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}