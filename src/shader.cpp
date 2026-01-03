#include "shader.h"

#include <glad/glad.h>

#include <fstream>
#include <iostream>
#include <sstream>

#include "util.h"

Shader::Shader(const std::string& vertexPath, const std::string fragmentPath)
{
    std::string vertexShaderCode = ReadShaderCode(vertexPath);
    std::string fragmentShaderCode = ReadShaderCode(fragmentPath);
    if (vertexShaderCode.empty() || fragmentShaderCode.empty()) {
        std::cout << "Shader::Shader: shader code is empty." << std::endl;
        return;
    }

    _id = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShaderCode);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderCode);

    glAttachShader(_id, vs);
    glAttachShader(_id, fs);
    glLinkProgram(_id);

    int success;
    glGetProgramiv(_id, GL_LINK_STATUS, &success);
    if (!success) {
        int length;
        glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &length);
        char* msg = new char[length];
        glGetProgramInfoLog(_id, length, &length, msg);
        std::cout << "Failed to link program: " << msg << std::endl;
        delete[] msg;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
}

Shader::~Shader()
{
    glDeleteProgram(_id);
}

void Shader::Bind() const
{
    glUseProgram(_id);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform1f(const std::string& name, float value)
{
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform1iv(const std::string& name, int count, int* value)
{
    glUniform1iv(GetUniformLocation(name), count, value);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

std::string Shader::ReadShaderCode(const std::string shaderFile)
{
    std::string shaderCode;
    std::ifstream shaderStream;
    shaderStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        shaderStream.open(shaderFile);
        std::stringstream sstream;
        sstream << shaderStream.rdbuf();
        shaderStream.close();
        shaderCode = sstream.str();
    } catch(std::ifstream::failure& e) {
        std::cout << "Shader::ReadShaderCode read " << shaderFile << " failed." << std::endl;
        return "";
    }
    return shaderCode;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& shaderCode)
{
    unsigned int shader;
    shader = glCreateShader(type);
    const char* code = shaderCode.c_str();
    glShaderSource(shader, 1, &code, NULL);
    glCompileShader(shader);
    // check for shader compile errors
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char* msg = new char[length];
        glGetShaderInfoLog(shader, length, &length, msg);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << msg << std::endl;
        glDeleteShader(shader);
        delete[] msg;
        return 0;
    }
    return shader;
}

int Shader::GetUniformLocation(const std::string& name) const
{
    if (_uniformlocationCache.find(name) != _uniformlocationCache.end()) {
        return _uniformlocationCache[name];
    }
    int location;
    location = glGetUniformLocation(_id, name.c_str());
    if (location == -1) {
        std::cout << "Warning: uniform '" << name << "' doesn't exist" << std::endl;
    }

    _uniformlocationCache[name] = location;
    return location;
}

