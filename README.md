# An Explorer for Newton Fractals

This is a project I made for rendering, animating, and exploring Newton Fractals. I wrote most of the starting code when I was on vacation with family, and it ended up being both an interesting and fun project to work on. It uses OpenGL and C++. 

## Procedural Generation

Looking at a single fractal (e.g. the Mandelbrot set) can be very interesting, but most of the videos about these fractals zoom way into the fractal instead of just showing a static image. I thought to myself, I wonder if there's a way to animate them? (In fact, this was a question I had years ago, when I was interested in making a fractal music visualiser (I failed).) 

This project uses [polynomials](https://en.wikipedia.org/wiki/Polynomial) with real coefficients to generate [Newton Fractals](https://en.wikipedia.org/wiki/Newton_fractal). Heuristically, slightly changing the coefficients of the polynomials will result in a similarly "small" change in the resulting fractal, though this is far from obvious and probably requires techniques from [complex dynamics](https://en.wikipedia.org/wiki/Complex_dynamics) to answer adequately. Fortunately for me, continuously or smoothly varying the coefficients produces an animation of the fractal; this is the principle that underlies the project. 

Producing the smooth variation of the coefficients is a whole thing, and I will write a blog post on [my website](https://hunterliu.xyz) in the near future detailing this aspect. 

## Next Steps 

If I do continue working on this project, I'm hoping to implement: 
 * Animation controls to pause, speed up, or slow down the animation or control other animation parameters. 
 * An "information panel" that allows a user to view details about the pixel beneath their mouse and about the fractal itself. 
 * Camera controls: zoom, pan, and possible rotate. 
 * A way to set the colour palate used by the shaders. 
 * A way to set a seed so animations or fractals are reproducible.
