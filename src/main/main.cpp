#include <iostream>
#include "openglWp.h"
#include "Boid.h"
#include "utils.h"
#include "conf.h"

#define N_BOIDS 7

int main(int argc, char *argv[])
{
    std::vector<float> vertices;
    std::vector<float> colors;
    std::vector<unsigned char> indices;

    vertices.reserve(N_BOIDS*conf::boid_points*2);
    colors.reserve(N_BOIDS*conf::boid_points*4);
    indices.reserve(N_BOIDS*conf::boid_points);

    float now, before, dt;
    before = now = secs();

    std::vector<Boid> boids;
    boids.reserve(N_BOIDS);
    vec velInit(0.1,0.1);
    for (uint32_t i=0; i<N_BOIDS; ++i){
        static vec initPos(0,0);
        boids.push_back(Boid());
        boids.back().init(vertices, indices, colors, initPos, velInit);
        std::cout << &boids.back() << "\n";
        initPos += vec(0.05,0.15);
    }
    //std::cout << "vertices:\n";
    //for (int i=0; i<vertices.size(); ++i){
    //    std::cout << vertices[i] << "\t";
    //    if(i%12==11) std::cout << "\n";
    //std::cout << "indices:\n";
    //for (int i=0; i<indices.size(); ++i)
    //    std::cout << (int)indices[i] << "\t";
    //std::cout << "colors:\n";
    //for (int i=0; i<colors.size(); ++i)
    //    std::cout << colors[i] << "\t";

    initWp(vertices, colors, indices);

    char done = 0;
    while (!done){
        SDL_Event e;
        while ( SDL_PollEvent(&e) ) {
            switch (e.type) {
                case SDL_QUIT:
                    done = 1;
                break;
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            done = 1;
                        break;
                        case SDLK_CAPSLOCK:
                            done = 1;
                        break;
                    }
                break;
            }
        }

        now = secs();
        dt = now - before;
        before = now;

        std::cout << "rate:\t" << 1/dt << "\n";

        for (auto& boid : boids){
            boid.update(dt);
        }

        updateWp(vertices, colors, indices);

        //SDL_Delay(10);
    }

    SDL_GL_DeleteContext(glContext);
    SDL_Quit();
    return 0;
}
