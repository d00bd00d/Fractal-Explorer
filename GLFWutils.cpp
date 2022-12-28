#include "GLFWutils.h"

#include <stdio.h> 
#include <stdlib.h>
#include <fstream> 
#include <string> 
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h> 

void initGLFW() {
    // try initialising GLFW 
    if(!glfwInit()) {
        fprintf(stderr, "Failed to initialise GLFW.\n"); 
		exit(-1);
    }

    // setting up window settings 
    // 4x antialiasing 
    glfwWindowHint(GLFW_SAMPLES, 4); 

    // use OpenGL 3.3 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
}

// some helper functions for compiling shaders

// reads a file into a string buffer; does nothing if file is 
// inaccessible for any reason whatsoever
void readFile(const char* file, std::string& buffer); 

// matches the source code to the provided shader id, then 
// compiles said source code 
void compileShader(const char* source, GLuint id); 

// checks the compilation status of the requested shader or 
// program ID, printing out any error logs if the compilation 
// was unsuccessful. 
void checkStatus(GLuint id); 

GLuint loadShaders(const char* vertex, const char* fragment) {
	// read in the files! 
	std::string vertexSource, fragmentSource; 
	readFile(vertex, vertexSource); 
	readFile(fragment, fragmentSource); 

	// the procedure for compiling these guys is as follows: 
	// 1. procure an ID
	// 2. compile the program 
	// 3. make sure there were no compilation errors 
	GLuint vertexID = glCreateShader(GL_VERTEX_SHADER); 
	compileShader(vertexSource.c_str(), vertexID); 
	checkStatus(vertexID); 

	GLuint fragmentID = glCreateShader(GL_FRAGMENT_SHADER); 
	compileShader(fragmentSource.c_str(), fragmentID); 
	checkStatus(fragmentID); 

	// create a program, link the shaders, and compile it! 
	GLuint programID = glCreateProgram(); 
	glAttachShader(programID, vertexID); 
	glAttachShader(programID, fragmentID); 
	glLinkProgram(programID); 

	// check the program's status 
	GLint status = 0; 
	glGetProgramiv(programID, GL_COMPILE_STATUS, &status); 
	if(status == GL_FALSE) { 
		GLint logLength;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLength); 

		std::vector<char> log(logLength + 1); 
		glGetProgramInfoLog(programID, logLength, NULL, &log[0]);
		fprintf(stderr, "%s\n", &log[0]); 
	}

	// detach and delete the shaders now that they've been compiled
	glDetachShader(programID, vertexID); 
	glDetachShader(programID, fragmentID); 
	glDeleteShader(vertexID); 
	glDeleteShader(fragmentID); 

	return programID; 
} 

void readFile(const char* file, std::string& buffer) {
	std::ifstream fileStream(file); 
	if(fileStream.fail()) {
		fprintf(stderr, "Could not open %s.\n", file); 
		return; 
	} 

	buffer = ""; 
	std::string line; 

	while(std::getline(fileStream, line)) {
		buffer += line; 
		buffer += '\n'; 
	} 
} 

void compileShader(const char* source, GLuint id) {
	glShaderSource(id, 1, &source, NULL); 
	glCompileShader(id); 
} 

void checkStatus(GLuint id) { 
	GLint status = 0; 
	glGetShaderiv(id, GL_COMPILE_STATUS, &status); 

	if(status == GL_FALSE) {
		GLint logLength;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength); 

		std::vector<char> log(logLength + 1); 
		glGetShaderInfoLog(id, logLength, NULL, &log[0]);
		fprintf(stderr, "%s\n", &log[0]); 
	}
} 
