#include <iostream>
#include "openglWp.h"
#include "Boid.h"

#define N_BOIDS 3

int main(int argc, char *argv[])
{
  
    const float oldvertices[] = {
        0.0f, 0.5f, 0.0f, 1.0f,
        0.5f, -0.366f, 0.0f, 1.0f,
        -0.5f, -0.366f, 0.0f, 1.0f
    };
    const float oldcolors[] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f 	
    };
  
    std::vector<float> vertices;
    std::vector<float> colors;
    std::vector<GLubyte> indices;
  
    std::vector<Boid> boids;
    vec posInit;
    vec velInit(0,1);
    for (unsigned i=0; i<N_BOIDS; ++i){
        boids.push_back(Boid());
        posInit = vec(0,0);
        boids[0].init(vertices, indices, colors, posInit, velInit);
    }
  
    initWp();
  
    glGenVertexArrays(1, &vao);
  
    // vertex_vbo
    glGenBuffers(1, &vertex_vbo); //create the buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo); //we're "using" this one now
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size(), vertices.data(), GL_STATIC_DRAW);
  
    // color_vbo
    glGenBuffers(1, &color_vbo); //create the buffer
    glBindBuffer(GL_ARRAY_BUFFER, color_vbo); //we're "using" this one now
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*colors.size(), colors.data(), GL_STATIC_DRAW);
  
    // index_vbo
    glGenBuffers(1, &elements);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*indices.size(), indices.data(), GL_STATIC_DRAW);
  
    char bGameLoopRunning = 1;
    while (bGameLoopRunning){
        SDL_Event e;
        if ( SDL_PollEvent(&e) ) {
            if (e.type == SDL_QUIT)
                bGameLoopRunning = 0;
            else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
                bGameLoopRunning = 0;
        }
  
        updateWp();
  
        SDL_Delay(20);
    } 
  
    SDL_GL_DeleteContext(glContext);
    SDL_Quit();
    return 0;
}
