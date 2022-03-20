#include "hdr.h"
#include "render.h"

#include <iostream>

rendering::HDR::HDR(const char* blur_v, const char* blur_f, const char* screen_v, const char* screen_f):
	m_blur_shader(blur_v, blur_f), m_screen_shader(screen_v, screen_f), m_rbo_depth(), m_blur_index(1),
    m_colour_buffers(), m_pingpong_fbos(), m_pingpong_colour_buffers() {

	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    unsigned int buffers[2];
	glGenTextures(2, buffers);
    m_colour_buffers.push_back(buffers[0]);
    m_colour_buffers.push_back(buffers[1]);

    for (unsigned int i = 0; i < 2; i++)
    {
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_colour_buffers[i]);
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, SAMPLES, GL_RGBA16F, scr_width, scr_height, GL_TRUE);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D_MULTISAMPLE, m_colour_buffers[i], 0);
    }

    glGenRenderbuffers(1, &m_rbo_depth);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo_depth);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, SAMPLES, GL_DEPTH_COMPONENT, scr_width, scr_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_rbo_depth);

    unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
    glDrawBuffers(2, attachments);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Failed to setup HDR frame buffer" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glGenFramebuffers(2, buffers);
    m_pingpong_fbos.push_back(buffers[0]);
    m_pingpong_fbos.push_back(buffers[1]);
    glGenTextures(2, buffers);
    m_pingpong_colour_buffers.push_back(buffers[0]);
    m_pingpong_colour_buffers.push_back(buffers[1]);

    for (unsigned int i = 0; i < 2; i++)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_pingpong_fbos[i]);
        glBindTexture(GL_TEXTURE_2D, m_pingpong_colour_buffers[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, scr_width, scr_height, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_pingpong_colour_buffers[i], 0);
        
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "Failed to setup HDR frame buffer " << i << std::endl;
    }

    m_blur_shader.use();
    m_blur_shader.set_int("u_image", 0);
    m_screen_shader.use();
    m_screen_shader.set_int("u_scene", 0);
    m_screen_shader.set_int("u_bloomBlur", 1);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    float vertices[] = {
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
         1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
         1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    };
    
    glGenVertexArrays(1, &m_quad_vao);
    glBindVertexArray(m_quad_vao);
    glGenBuffers(1, &m_quad_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_quad_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
}

void rendering::HDR::prerender() {
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void rendering::HDR::apply_blur() {
    bool first_iteration = true;
    unsigned int amount = 7;

    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo);
    glReadBuffer(GL_COLOR_ATTACHMENT1);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_pingpong_fbos[!m_blur_index]);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    glBlitFramebuffer(0, 0, scr_width, scr_height, 0, 0, scr_width, scr_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);

    m_blur_shader.use();
    for (unsigned int i = 0; i < amount; i++)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_pingpong_fbos[m_blur_index]);
        m_blur_shader.set_int("u_horizontal", m_blur_index);
        glBindTexture(GL_TEXTURE_2D, m_pingpong_colour_buffers[!m_blur_index]);
        draw_quad();
        m_blur_index = (m_blur_index+1) & 1;
        if (first_iteration)
            first_iteration = false;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void rendering::HDR::draw_quad() {
    glBindVertexArray(m_quad_vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

void rendering::HDR::render_to_screen() {

    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo);
    glReadBuffer(GL_COLOR_ATTACHMENT0);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_pingpong_fbos[!m_blur_index]);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    glBlitFramebuffer(0, 0, scr_width, scr_height, 0, 0, scr_width, scr_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    m_screen_shader.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_pingpong_colour_buffers[!m_blur_index]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_pingpong_colour_buffers[m_blur_index]);
    m_screen_shader.set_float("u_exposure", 1.0f);
    
    draw_quad();
}