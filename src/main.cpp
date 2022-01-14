#define GL_SILENCE_DEPRECATION

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <math.h>

#include "../shaders/shader.h"

int main(){
    /* INIT GLFW */
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    /* WINDOW INIT */
    const unsigned int width = 800, height = 600;
    GLFWwindow *win = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if(!win){
        std::cerr << "Error creating OpenGL window" << std::endl;
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(win);
    glViewport(0, 0, width, height);

    /* IMGUI INIT */
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io; //sets up input / output

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(win, true);
    ImGui_ImplOpenGL3_Init("#version 150");

    /* GLEW INIT */
    glewExperimental = true;
    if(glewInit() != GLEW_OK){
        std::cerr << "ERROR INITIALIZING GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }

    //renders 3D vertices properly
    glEnable(GL_DEPTH_TEST);

    Shader my_shader = Shader("../shaders/shader.shader");

    float vertex_positions[] = {
        //front face
        0.5f, 0.5f, 0.5f, 
        0.0f, 0.5f, 0.5f, 
        0.0f, 0.0f, 0.5f, 

        0.0f, 0.0f, 0.5f, 
        0.5f, 0.0f, 0.5f, 
        0.5f, 0.5f, 0.5f, 

        //right face
        0.5f, 0.5f, 0.0f, 
        0.5f, 0.5f, 0.5f, 
        0.5f, 0.0f, 0.5f, 

        0.5f, 0.0f, 0.5f, 
        0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 

        //left face
        0.0f, 0.5f, 0.5f, 
        0.0f, 0.0f, 0.0f, 
        0.0f, 0.0f, 0.5f, 
        
        0.0f, 0.5f, 0.5f, 
        0.0f, 0.5f, 0.0f,
        0.0f, 0.0f, 0.0f,

        //back face
        0.5f, 0.0f, 0.0f, 
        0.0f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 

        0.0f, 0.5f, 0.0f, 
        0.5f, 0.5f, 0.0f, 
        0.5f, 0.0f, 0.0f, 

        //top face
        0.5f, 0.5f, 0.5f, 
        0.5f, 0.5f, 0.0f, 
        0.0f, 0.5f, 0.0f, 

        0.0f, 0.5f, 0.0f, 
        0.0f, 0.5f, 0.5f, 
        0.5f, 0.5f, 0.5f,

        //bottom face
        0.0f, 0.0f, 0.5f, 
        0.0f, 0.0f, 0.0f, 
        0.5f, 0.0f, 0.0f, 

        0.0f, 0.0f, 0.5f, 
        0.5f, 0.0f, 0.0f, 
        0.5, 0.0f, 0.5f,
    };

    float vertex_colours[] = {
        //front face
        0.0f, 0.0f, 0.0f, 
        0.0f, 0.0f, 0.0f, 
        0.0f, 0.0f, 0.0f, 

        0.0f, 0.0f, 0.0f, 
        0.0f, 0.0f, 0.0f, 
        0.0f, 0.0f, 0.0f,

        //right face
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        //left face
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

        //back face
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,

        //top face
        0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,

        0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,

        //bottom face
        0.0f, 0.5f, 0.5f,
        0.0f, 0.5f, 0.5f,
        0.0f, 0.5f, 0.5f,

        0.0f, 0.5f, 0.5f,
        0.0f, 0.5f, 0.5f,
        0.0f, 0.5f, 0.5f,
    };

    //buffer creations
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO, colour_buffer;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions), vertex_positions, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &colour_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, colour_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_colours), vertex_colours, GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    bool main_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    glm::vec3 rotation_vec(0.0f, 1.0f, 0.5f);

    /* MAIN RENDER LOOP */
    while(!glfwWindowShouldClose(win)){

        //loop variables
        float rotation_angle = glm::radians(45.0f);
        static float speed_factor = 0.5f;
        float rotation_speed = (float)glfwGetTime() * rotation_angle * speed_factor;
        glm::mat4 model = glm::mat4(1.0f);

        //input / output
        glfwPollEvents();

        //setup imgui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //main demo window
        {   
            ImGui::Begin("Hello, world!");                         

            ImGui::Text("This is some useful text.");               
            ImGui::Checkbox("Demo Window", &main_window);      
            ImGui::Checkbox("Another Window", &main_window);

            ImGui::SliderFloat3("Rotation", &rotation_vec.x, 0.0f, (2.0f * M_PI));            
            ImGui::SliderFloat("Rotation Speed", &speed_factor, 0.0f, 1.0f);
            ImGui::ColorEdit3("Background Color", (float*)&clear_color); 

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        //shaders
        glUseProgram(my_shader.ID);
        glBindVertexArray(VAO);

        //rendering 
        model = glm::rotate(model, rotation_speed, rotation_vec);
        glUniformMatrix4fv(glGetUniformLocation(my_shader.ID, "model"), 1, GL_FALSE, &model[0][0]);

        ImGui::Render();
        glClearColor(clear_color.x, clear_color.y, clear_color.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glDrawArrays(GL_TRIANGLES, 0, sizeof(vertex_positions) / 3);    
        glfwSwapBuffers(win); //swap front and back buffer
      
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(win);
    glfwTerminate();

    return 0;
}