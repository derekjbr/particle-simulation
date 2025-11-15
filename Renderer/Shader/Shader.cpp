#include "Shader.h"
#include <iostream>
#include <FileParserUtils.h>
#include <memory>

using namespace Renderer;

/////////////////////////////////////////////////////////////////////
Shader::Shader(const std::string& vertexCode, const std::string& fragmentCode) {
    Compile(vertexCode, fragmentCode);
}

/////////////////////////////////////////////////////////////////////
std::shared_ptr<Shader> Shader::CreateFromFiles(const std::string& vertexFilePath, const std::string& fragmentFilePath) {
    std::string vertexCode;
    std::string fragmentCode;

    try {
        vertexCode = Utils::ReadFileToString(vertexFilePath);
        fragmentCode = Utils::ReadFileToString(fragmentFilePath);
    } catch (const std::runtime_error& e) {
        std::cerr << "Error reading shader files: " << e.what() << std::endl;
    }

    return std::make_shared<Shader>(vertexCode, fragmentCode);
}

/////////////////////////////////////////////////////////////////////
Shader::~Shader() {
    glDeleteProgram(ID);
}

/////////////////////////////////////////////////////////////////////
void Shader::Use() {
    glUseProgram(ID);
}

/////////////////////////////////////////////////////////////////////
GLuint Shader::GetID() const {
    return ID;
}

void Shader::SetFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

/////////////////////////////////////////////////////////////////////
void Shader::SetInteger(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

/////////////////////////////////////////////////////////////////////
void Shader::SetBoolean(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

/////////////////////////////////////////////////////////////////////
void Shader::Compile(const std::string& vertexCode, const std::string& fragmentCode) {
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}