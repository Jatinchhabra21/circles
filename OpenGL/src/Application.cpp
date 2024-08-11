#define GLEW_STATIC
#include<GL/glew.h>
#include <GLFW/glfw3.h>

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<math.h>
#include<windows.h> 
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Renderer.h"
#include "Circle.h"

std::vector<VertexBuffer> vb;
std::vector<VertexArray> va;
std::vector<IndexBuffer> ib;
 

void GLAPIENTRY
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
  fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
}


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err =  glewInit();

    if (err != GLEW_OK) {
        std::cout << "Error encountered" << std::endl;
    }

    std::cout << "[Debug] OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    
    glDebugMessageCallback(MessageCallback, 0);


    {
        Circle circle = Circle(0, 0, 0.2);
        //Gelis: Changed it so you're not making new vaos, vbos and ibos because you're already making them in the circle struct.
        //Gelis: If you want to have a vector of "objects" make a vector of circles and bind the vaos and ibos like im doing for the single circle.

        // vb.push_back(VertexBuffer(&circle.m_vertexPosition[0], circle.m_vertexPosition.size() * sizeof(float)));

        // ib.push_back(IndexBuffer(&circle.m_vertexIndices[0], circle.m_vertexIndices.size()));

        // va.push_back(VertexArray());
        // va[0].AddBuffer(vb[0], circle.m_layout);

        Shader shader = Shader("OpenGL/res/Shaders/Basic.shader");

        Renderer renderer;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);
            
            // for (int i = 0; i < va.size(); i++)
            renderer.Draw(circle.m_vertexArray, circle.m_indexBuffer, shader);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}