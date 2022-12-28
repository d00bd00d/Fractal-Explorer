#ifndef COEFFICIENTS_H
#define COEFFICIENTS_H

#include <GL/glew.h> 

class Coefficients {
public: 
    Coefficients(); 
    ~Coefficients(); 

    // sends the coefficients to the specified GL uniform variable
    void sendCoeffs(GLuint programID, const char* name); 

private: 
    void _updateCoeffs(); 

    int _ticks; 

    // idea: suppose some coefficient is "animated" by a function 
    // f(x). In order to make such an f(x) appear random, we'll be 
    // generating one of its higher derivatives every now and again. 
    // Then, we'll use iterated differencing to "estimate" f(x). 

    // to make the process of sending the actual coefficients to 
    // OpenGL way faster, _coeffs[0] will store the coefficients; 
    // _coeffs[1] will store the first derivative data, etc. 
    float** _coeffs; 

    // this remembers the range of n-th degree taylor coefficients 
    // we're permitting 
    float _bound;

    // number of frames before generating a new set of animation 
    // parameters 
    static const int SHIFT_FRAMES; 

    // the degree of the polynomial whose coefficients we're making
    static const int DEGREE; 

    // the degree of the taylor polynomial we're using to animate
    // the coefficients. 
    static const int TAYLOR_DEGREE; 

    // how big we're allowing the coefficients to be
    static const float MAX_COEFF; 

    // the factor by which the taylor coefficients should decrease.
    // this can be manually tuned so that the animation "stays 
    // interesting" and doesn't stay stagnant for too long, but also 
    // so that it doesn't give anyone epilepsy 
    static const float TAYLOR_DECAY; 

    // the factor by which the coefficients decay every frame. The 
    // value of any fixed coefficient at each update is like a random
    // walk on the real line, and it's bound to blow up if nothing
    // is done about it. This should be manually tuned. 
    static const float COEFF_DECAY; 
}; 

#endif 
