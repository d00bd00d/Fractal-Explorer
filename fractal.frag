#version 330 core

#define MAX_ITERS 128
#define TOLERANCE 0.000001

#define N 8

in vec2 fragmentPosition; 
out vec3 color;

uniform float coefficients[N + 1]; 

vec2 f(float x, float y) {
    float fx = coefficients[N]; 
    float fy = 0; 
    float t; 

    for(int n = N - 1; n >= 0; n--) {
        // multiply by x + iy
        t = fx; 
        fx = fx * x - fy * y; 
        fy = t * y + fy * x; 

        // add the next (real) coefficient 
        fx += coefficients[n]; 
    } 

    return vec2(fx, fy); 
} 

vec2 fp(float x, float y) {
    float fx = coefficients[N] * N; 
    float fy = 0; 
    float t; 

    for(int n = N - 1; n >= 1; n--) {
        // multiply by x + iy
        t = fx; 
        fx = fx * x - fy * y; 
        fy = t * y + fy * x; 

        // add n * next coefficient. 
        fx += n * coefficients[n]; 
    }

    return vec2(fx, fy); 
} 

void main() {
    float x = fragmentPosition.x; 
    float y = fragmentPosition.y; 

    vec2 fv, fpv; 
    float r; 

    float n = 0; 
    while(n <= MAX_ITERS) {
        // check if we've found a root or not
        fv = f(x, y); 
        if(fv.x * fv.x + fv.y * fv.y < TOLERANCE) 
            break; 

        fpv = fp(x, y); 
        r = fpv.x * fpv.x + fpv.y * fpv.y; 

        // make sure the derivative isn't too small 
        if(r < TOLERANCE) {
            n = MAX_ITERS; 
            break; 
        }

        x -= (fv.x * fpv.x + fv.y * fpv.y) / r; 
        y -= (fv.y * fpv.x - fv.x * fpv.y) / r; 
        n += 1.0; 
    } 

    n = n / (n + 10); 
    r = 1 / (x * x + y * y); 
    color = vec3(1 - n - x * x * r * (1 - n), 
                 1 - n - y * y * r * (1 - n), 
                 1 - n); 
}
