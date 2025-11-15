#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <memory>

namespace Renderer {
    class Shader {
    public:
        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        ~Shader();

        void Use();
        GLuint GetID() const;

        void SetFloat(const std::string &name, float value) const;
        void SetInteger(const std::string &name, int value) const;
        void SetBoolean(const std::string &name, bool value) const;

        static std::shared_ptr<Shader> CreateFromFiles(const std::string& vertexFilePath, const std::string& fragmentFilePath);
    private:
        GLuint ID;
        void Compile(const std::string& vertexCode, const std::string& fragmentCode);
    };
}

#endif // SHADER_H