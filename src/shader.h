#pragma once

#include <unordered_map>
#include <string>

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string fragmentPath);
	~Shader();

	void Bind() const;
	void Unbind() const;
    void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform1iv(const std::string& name, int count, int* value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

private:
    std::string ReadShaderCode(const std::string shaderFile);
    unsigned int CompileShader(unsigned int type, const std::string& shaderCode);
    int GetUniformLocation(const std::string& name) const;

    unsigned int _id;
    mutable std::unordered_map<std::string, int> _uniformlocationCache;
};