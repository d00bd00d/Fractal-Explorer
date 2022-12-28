#include "Coefficients.h"
#include "WindowManager.h" 
#include "GLFWutils.h"

#include <stdio.h> 
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h> 

const GLfloat WindowManager::_vertices[] = {
    1.0f, -1.0f, 
    -1.0f, -1.0f,
    1.0f, 1.0f,
    -1.0f, 1.0f
};  

WindowManager::WindowManager() { 
    // initialise GLFW systems 
    initGLFW(); 

    // create the window
    _window = glfwCreateWindow(1366, 768, // default dimensions
        "Animated Newton Fractal", 
        glfwGetPrimaryMonitor(), NULL); 

    // verify that the window was set up properly 
    if(!_window) {
        fprintf(stderr, "Failed to open a new window.\n"); 
        exit(-1); 
    }

    // sets up the GLEW context
    glfwMakeContextCurrent(_window); 

    if(glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialise GLEW.\n"); 
        exit(-1); 
    } 

    // create a VAO and the vertex buffer, then feed it in. 
    glGenVertexArrays(1, &_vertexArrayID); 
    glBindVertexArray(_vertexArrayID); 

    glGenBuffers(1, &_vertexBuffer); 
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer); 
    glBufferData(GL_ARRAY_BUFFER,    
                 sizeof(WindowManager::_vertices), 
                 WindowManager::_vertices, 
                 GL_STATIC_DRAW);     
    
    // compile the shaders!
    _programID = loadShaders("fractal.vert", "fractal.frag"); 
    glBindAttribLocation(_programID, 0, "vertexPosition"); 
} // end of WindowManager::WindowManager() 

WindowManager::~WindowManager() {} // do nothing in dtor

void WindowManager::mainLoop() {
    do {
        // clears the screen 
        glClear(GL_COLOR_BUFFER_BIT); 

        // use the program
        glUseProgram(_programID); 
        glEnableVertexAttribArray(0); 
        _coeff.sendCoeffs(_programID, "coefficients"); 

        // draw stuff [currently empty] 
        glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer); 
        glVertexAttribPointer(0,    // attribute; unimportant
            2,                      // size of data 
            GL_FLOAT,               // type of data 
            GL_FALSE,               // normalised? 
            0,                      // "stride" (?) 
            (void*)0);              // buffer offset
        glDrawArrays(GL_TRIANGLES, 0, 3); 
        glDrawArrays(GL_TRIANGLES, 1, 3); 

        // unuse the program 
        glDisableVertexAttribArray(0); 
        glUseProgram(0); 

        // swap buffers 
        glfwSwapBuffers(_window); 
        glfwPollEvents(); 
    } while(glfwGetKey(_window, GLFW_KEY_ESCAPE) != GLFW_PRESS && 
            glfwWindowShouldClose(_window) == 0); 
} // end of WindowManager::mainLoop()
