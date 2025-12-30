#pragma once

#include <glad/glad.h>

void APIENTRY gl_debug_message_callback(GLenum source, GLenum type, GLuint id,
                            GLenum severity, GLsizei length,
                            const GLchar *msg, const void *data);

