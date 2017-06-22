//
// Created by wangyang on 2017/5/24.
//

#include "../ELRenderPipline.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <cassert>

bool createProgram(const char *vertexShader, const char *fragmentShader, GLuint *pProgram);
bool compileShader(GLuint *shader, GLenum type, const GLchar *source);
bool validateProgram(GLuint prog);
bool linkProgram(GLuint prog);

crossplatform_var_int(program)
crossplatform_var_int(maxTextureUnits)

// 用来进行纹理资源计数
static int gl_texture_id_counter = 0;

ELRenderPiplinePtr ELRenderPipline::init(std::string vertexShader, std::string fragmentShader) {
    GLuint program;
    createProgram(vertexShader.c_str(), fragmentShader.c_str(), &program);
    programSet(this, program);

    int maxTextureUnits;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnits);
    maxTextureUnitsSet(this, maxTextureUnits);
    return selv;
}

ELRenderPipline::~ELRenderPipline() {
    ELInt program = programGet(this);
    glDeleteProgram(program);
}

ELInt ELRenderPipline::getUniformLocation(std::string uniformName) {
    std::string uniformKey = "uniform_" + uniformName;
    if (__crossplatformIntExist(uniformKey)) {
        return __crossplatformFetchInt(uniformKey);
    }
    GLuint location = glGetUniformLocation(programGet(this), uniformName.c_str());
    __crossplatformAttach(uniformKey, (ELInt)location);
    return (ELInt)location;
}

void ELRenderPipline::setUniform(ELInt val, ELInt location) {
    glUniform1i(location, (GLuint)val);
}

void ELRenderPipline::setUniform(ELFloat val, ELInt location) {
    glUniform1f(location, (GLfloat)val);
}

void ELRenderPipline::setUniform(ELVector2 val, ELInt location) {
    glUniform2fv(location, 1, val.v);
}

void ELRenderPipline::setUniform(ELVector3 val, ELInt location) {
    glUniform3fv(location, 1, val.v);
}

void ELRenderPipline::setUniform(ELVector4 val, ELInt location) {
    glUniform4fv(location, 1, val.v);
}

void ELRenderPipline::setUniform(ELMatrix2 val, ELInt location) {
    glUniformMatrix2fv(location, 1, false, val.m);
}

void ELRenderPipline::setUniform(ELMatrix3 val, ELInt location) {
    glUniformMatrix3fv(location, 1, false, val.m);
}

void ELRenderPipline::setUniform(ELMatrix4 val, ELInt location) {
    glUniformMatrix4fv(location, 1, false, val.m);
}

void ELRenderPipline::bindTexture(ELTexturePtr texture, ELInt uniformLocation) {
    assert (gl_texture_id_counter < maxTextureUnitsGet(this));
    ELInt glTextureVal = texture->__crossplatformFetchInt("glVal");
    if (glTextureVal >= 0) {
        glUniform1i(uniformLocation, gl_texture_id_counter);
        glActiveTexture(GL_TEXTURE0 + gl_texture_id_counter);
        glBindTexture(GL_TEXTURE_2D, glTextureVal);
    }
    gl_texture_id_counter++;
}

void ELRenderPipline::clearState() {
    gl_texture_id_counter = 0;
}


// Create Program
bool createProgram(const char *vertexShader, const char *fragmentShader, GLuint *pProgram) {
    GLuint program, vertShader, fragShader;
    // Create shader program.
    program = glCreateProgram();

    const GLchar *vssource = (GLchar *)vertexShader;
    const GLchar *fssource = (GLchar *)fragmentShader;

    if (!compileShader(&vertShader, GL_VERTEX_SHADER, vssource)) {
        printf("Failed to compile vertex shader");
        return false;
    }

    if (!compileShader(&fragShader, GL_FRAGMENT_SHADER, fssource)) {
        printf("Failed to compile fragment shader");
        return false;
    }

    // Attach vertex shader to program.
    glAttachShader(program, vertShader);

    // Attach fragment shader to program.
    glAttachShader(program, fragShader);

    // Link program.
    if (!linkProgram(program)) {
        printf("Failed to link program: %d", program);

        if (vertShader) {
            glDeleteShader(vertShader);
            vertShader = 0;
        }
        if (fragShader) {
            glDeleteShader(fragShader);
            fragShader = 0;
        }
        if (program) {
            glDeleteProgram(program);
            program = 0;
        }
        return false;
    }

    // Release vertex and fragment shaders.
    if (vertShader) {
        glDetachShader(program, vertShader);
        glDeleteShader(vertShader);
    }
    if (fragShader) {
        glDetachShader(program, fragShader);
        glDeleteShader(fragShader);
    }

    *pProgram = program;
    return true;
}


bool compileShader(GLuint *shader, GLenum type, const GLchar *source) {
    GLint status;

    if (!source) {
        printf("Failed to load vertex shader");
        return false;
    }

    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &source, NULL);
    glCompileShader(*shader);

    GLint logLength;
    glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &logLength);

#if Debug
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetShaderInfoLog(*shader, logLength, &logLength, log);
        printf("Shader compile log:\n%s", log);
        printf("Shader: \n %s\n", source);
        free(log);
    }
#endif

    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
    if (status == 0) {
        glDeleteShader(*shader);
        return false;
    }

    return true;
}

bool linkProgram(GLuint prog) {
    GLint status;
    glLinkProgram(prog);

#if Debug
    GLint logLength;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(prog, logLength, &logLength, log);
        printf("Program link log:\n%s", log);
        free(log);
    }
#endif

    glGetProgramiv(prog, GL_LINK_STATUS, &status);
    if (status == 0) {
        return false;
    }

    return true;
}

bool validateProgram(GLuint prog) {
    GLint logLength, status;

    glValidateProgram(prog);
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(prog, logLength, &logLength, log);
        printf("Program validate log:\n%s", log);
        free(log);
    }

    glGetProgramiv(prog, GL_VALIDATE_STATUS, &status);
    if (status == 0) {
        return false;
    }

    return true;
}