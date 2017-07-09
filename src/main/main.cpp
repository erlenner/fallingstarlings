#include <iostream>
#include "openglWp.h"
#include "Boid.h"

#define N_BOIDS 2

int main(int argc, char *argv[])
{
    std::vector<float> vertices;
    std::vector<float> colors;
    std::vector<GLubyte> indices;

    std::vector<Boid> boids;
    vec velInit(0,1);
    for (unsigned i=0; i<N_BOIDS; ++i){
        static vec initPos(0,0);
        boids.push_back(Boid());
        boids[0].init(vertices, indices, colors, initPos, velInit);
        std::cout << initPos << "\n";
        initPos += vec(0,0.5);
    }
    std::cout << "vertices:\n";
    for (int i=0; i<vertices.size(); ++i){
        std::cout << vertices[i] << "\t";
        if(i%12==11) std::cout << "\n";
}
    std::cout << "indices:\n";
    for (int i=0; i<indices.size(); ++i)
        std::cout << (int)indices[i] << "\t";
    std::cout << "colors:\n";
    for (int i=0; i<colors.size(); ++i)
        std::cout << colors[i] << "\t";

    initWp();

    glGenVertexArrays(1, &vao);

    // vertex_vbo
    glGenBuffers(1, &vertex_vbo); //create the buffer

    // color_vbo
    glGenBuffers(1, &color_vbo); //create the buffer

    // index_vbo
    glGenBuffers(1, &elements);

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    std::cout << "displayMode: " << displayMode.w << "," << displayMode.h << "\n";

    char bGameLoopRunning = 1;
    while (bGameLoopRunning){
        SDL_Event e;
        if ( SDL_PollEvent(&e) ) {
            if (e.type == SDL_QUIT)
                bGameLoopRunning = 0;
            else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
                bGameLoopRunning = 0;
        }

        updateWp(vertices, colors, indices);

        SDL_Delay(10);
    } 

    SDL_GL_DeleteContext(glContext);
    SDL_Quit();
    return 0;
}
