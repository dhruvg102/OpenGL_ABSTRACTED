#pragma once

#include <string>
#include <unordered_map>

//STRUCT TO STORE VERT AND FRAG CODE
struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource; 
};

class Shader{

private:
    std::string m_FilePath;
    unsigned int m_RendererID;
    std::unordered_map<std::string, int> m_UniformLocationCache;


public:
    Shader(const std::string& filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    //Set Uniform
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

private:
    unsigned int GetUniformLocation(const std::string& name);
    ShaderProgramSource ParseShader(const std::string& filePath);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragShader);
};