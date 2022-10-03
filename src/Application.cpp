#include <iostream>
#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include <string>
#include <fstream>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

int main(){
    GLFWwindow *window;

    if(!glfwInit()){
        std::cout<< "GLFW not intialized" <<std::endl;
        return -1;
    }

    window = glfwCreateWindow(800,800, "opengl_tut", 0,0);
    if(!window){
        std::cout<< "Window wasnt created" <<std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(2);
    
    gladLoadGL();

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    const char* glsl_version = "#version 130";

    ImGui_ImplOpenGL3_Init(glsl_version);



    // glViewport(0,0,1280,720);
    {
    float position[]= {
        200.0f, 200.0f, 0.0f, 0.0f,
        600.0f, 200.0f, 1.0f, 0.0f,
        600.0f, 600.0f, 1.0f, 1.0f,
        200.0f, 600.0f, 0.0f, 1.0f,
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };    

    GLCALL(glEnable(GL_BLEND));
    GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    
    VertexArray va;
    VertexBuffer vb (position, 4 * 4 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    
    va.AddBuffer(vb, layout);

    

    IndexBuffer ib(indices, 6);

    glm::mat4 proj = glm::ortho(0.0f, 800.0f, 0.0f, 800.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100,0,0));

    Shader shader("..\\res\\shaders\\Basic.shader");
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
    

    Texture texture("..\\res\\textures\\cool.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);

    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();

    Renderer renderer;

    glm::vec3 translation(0, 0, 0);
    float r = 0.0f;
    float increment = 0.05f;

    while(!glfwWindowShouldClose(window)){
        renderer.Clear();
        
         // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glm::mat4 model = glm::translate(glm::mat4(1.0f), translation );

        glm::mat4 mvp = proj * view * model;


        shader.Bind();
        shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
        shader.SetUniformMat4f("u_MVP", mvp);

        renderer.Draw(va, ib, shader);

        if(r > 1.0f){
            increment = -0.05f;
        }else if(r < 0.0f){
            increment = 0.05f;
        }
        r += increment;


        {

            ImGui::Begin("Hello, world!");                          
            ImGui::SliderFloat3("Translation", &translation.x, 0.0f, 800.0f);   
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        glfwSwapBuffers(window);

        glfwPollEvents();


    }
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}