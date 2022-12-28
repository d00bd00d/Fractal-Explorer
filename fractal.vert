#version 330 core

#define ASPECT_RATIO 1366.0 / 768.0
#define SCALE 1

layout(location = 0) in vec2 vertexPosition; 
out vec2 fragmentPosition; 

void main() {
    gl_Position.xy = vertexPosition; 

    // 3d shenanigans, set to 0 
    gl_Position.z = 0; 

    // quaternion rotation shenanigans, set to 1
    gl_Position.w = 1; 

    fragmentPosition.x = vertexPosition.x * ASPECT_RATIO; 
    fragmentPosition.y = vertexPosition.y; 
    fragmentPosition *= SCALE;
}
