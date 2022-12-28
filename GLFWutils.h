#ifndef GLFW_UTILS_H
#define GLFW_UTILS_H 

#include <GL/glew.h>
#include <GLFW/glfw3.h> 

// sets up GLFW with all of the best settings 
void initGLFW(); 

// compiles a pair of vertex/fragment shaders at the provided 
// file locations and returns the associated program ID. 
GLuint loadShaders(const char* vertex, const char* fragment);

#endif 
