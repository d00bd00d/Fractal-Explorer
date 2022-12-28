#ifndef WINDOW_MANAGER_H 
#define WINDOW_MANAGER_H

#include "Coefficients.h" 

#include <GL/glew.h>
#include <GLFW/glfw3.h> 

class WindowManager {
public: 
    WindowManager(); 
    ~WindowManager(); 

    // the main loop for drawing things! This pretty much just 
    // applies a simple shader to everything. 
    void mainLoop(); 

private: 
    GLFWwindow* _window; 
    GLuint _vertexArrayID; 
    GLuint _vertexBuffer; 
    GLuint _programID; 
    Coefficients _coeff; 

    // (fixed) vertices to cover the screen in rectangles 
    static const GLfloat _vertices[]; 
}; 

#endif 
