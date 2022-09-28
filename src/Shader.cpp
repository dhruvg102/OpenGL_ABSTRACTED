
#include "Shader.h"

#include "Renderer.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


Shader::Shader(const std::string &filepath)
    :m_FilePath(filepath), m_RendererID(0)
{
    ShaderProgramSource source = ParseShader(filepath);
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
    
}

Shader::~Shader(){
    GLCALL(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const {
    GLCALL(glUseProgram(m_RendererID));
}

void Shader::Unbind() const {
    GLCALL(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3)
{
    GLCALL(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

unsigned int Shader::GetUniformLocation(const std::string &name){

    if(m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
    {
        return m_UniformLocationCache[name];
    }

    GLCALL(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if(location ==-1){
        std::cout<<"WARNING: UNIFROM: " << name << "doesnt exist" <<std::endl;
    }
    m_UniformLocationCache[name] = location;
    return location;
}
ShaderProgramSource Shader::ParseShader(const std::string& filePath){

    std::ifstream stream(filePath);
    
    enum class ShaderType{
        NONE = -1,
        VERTEX = 0,
        Fragment = 1
    };

    std::string line;
    std::stringstream ss[2];

    ShaderType type = ShaderType::NONE;

    while(getline(stream, line)){
        if(line.find("#shader")!= std::string::npos)
        {
            if(line.find("vertex")!= std::string::npos)
            {
                //set mode to vertex
                type = ShaderType::VERTEX;
            }
            if(line.find("fragment")!= std::string::npos)
            {
                //set mode to vertex
                type= ShaderType::Fragment;
            }
        }
        else{
            ss[(int)type] << line << '\n';
        }
    }
    return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {

    unsigned int id = glCreateShader(type);
    const char* src = &source[0];
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE){
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout<<"FAILED TO COMPILE "<< (type == GL_VERTEX_SHADER? "vertex" : "fragment") << " SHADER!"<<std::endl;
        std::cout<<message<<std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragShader){

    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}