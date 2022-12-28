#include "Coefficients.h" 

#include <GL/glew.h>
#include <stdio.h> 
#include <stdlib.h>
#include <random> 
#include <time.h>

const int   Coefficients::SHIFT_FRAMES  = 100; 
const float Coefficients::MAX_COEFF     = 0.25; 
const int   Coefficients::DEGREE        = 8; 
const int   Coefficients::TAYLOR_DEGREE = 3; 
const float Coefficients::TAYLOR_DECAY  = 1.25; 
const float Coefficients::COEFF_DECAY   = 0.995; 

// static helper function for generating random floats 
float randFloat(float min, float max) {
    static std::mt19937 rng(time(0)); 
    
    // this is between 0 and 1, inclusive. 
    float t = (float)rng() / (float)(rng.max()); 
    return min + t * (max - min); 
} 

Coefficients::Coefficients() {
    _coeffs = new float*[Coefficients::TAYLOR_DEGREE + 1]; 
    _bound = Coefficients::MAX_COEFF; 

    for(int i = 0; i <= Coefficients::TAYLOR_DEGREE; i++) {
        _coeffs[i] = new float[Coefficients::DEGREE + 1]; 
        for(int j = 0; j <= Coefficients::DEGREE; j++) 
            _coeffs[i][j] = randFloat(-1 * _bound, _bound);

        _bound *= Coefficients::TAYLOR_DECAY; 
    } 
}

Coefficients::~Coefficients() {
    for(int i = 0; i <= Coefficients::TAYLOR_DEGREE; i++) 
        delete[] _coeffs[i]; 

    delete[] _coeffs; 
} 

void Coefficients::sendCoeffs(GLuint programID, const char* name) {
    // get the uniform's location
    GLuint location = glGetUniformLocation(programID, name); 
    if(location == GL_INVALID_INDEX) {
        fprintf(stderr, "Cannot find uniform %s.\n", name); 
        exit(-1); 
    } 

    // write the coefficient array to the uniform
    glUniform1fv(location, Coefficients::DEGREE + 1, _coeffs[0]); 

    // update coefficients 
    _updateCoeffs(); 

    // check if we need to change the coeffs to something new 
    if(++_ticks >= Coefficients::SHIFT_FRAMES) {
        _ticks = 0; 

        for(int i = 0; i <= Coefficients::DEGREE; i++)
            // only change the highest degree of the taylor guys
            _coeffs[Coefficients::TAYLOR_DEGREE][i] = 
                randFloat(-1 * _bound, _bound);
    }
}

void Coefficients::_updateCoeffs() {
    // very simple differencing! 
    for(int i = Coefficients::TAYLOR_DEGREE; i > 0; i--) 
        for(int j = 0; j <= Coefficients::DEGREE; j++) 
            _coeffs[i - 1][j] += _coeffs[i][j] / 
                (float)(Coefficients::SHIFT_FRAMES); 

    // tune the coefficients and make them decay a little
    for(int i = 0; i <= Coefficients::TAYLOR_DEGREE; i++) 
        for(int j = 0; j <= Coefficients::DEGREE; j++) 
            _coeffs[i][j] *= Coefficients::COEFF_DECAY; 

    // for debugging -- dump coefficients to stdout 
    for(int i = 0; i <= Coefficients::DEGREE; i++)
        printf("%6.3f ", _coeffs[0][i]); 
    printf("\n"); 
}
