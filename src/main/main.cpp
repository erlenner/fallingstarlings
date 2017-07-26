#include <iostream>
#include "openglWp.h"
#include "Boid.h"
#include "Lead.h"
#include "utils.h"
#include "conf.h"

#define N_BOIDS 200
#define N_LEADS 1

int main(int argc, char *argv[])
{
    std::vector<float> vertices;
    std::vector<float> colors;
    std::vector<uint32_t> indices;

    vertices.reserve(   N_BOIDS*conf::boid_points*2 + N_LEADS*conf::lead_points*2);
    colors.reserve(     N_BOIDS*conf::boid_points*4 + N_LEADS*conf::lead_points*4);
    indices.reserve(    N_BOIDS*conf::boid_points   + N_LEADS*conf::lead_points);

    float now, before, dt;
    before = now = secs();

    std::cout << "boids:\n";
    std::vector<Boid> boids(N_BOIDS);
    for (uint32_t i=0; i<N_BOIDS; ++i){
        static vec initPos, velInit(.1,.1);

        float angle = (std::rand() % 360) * 3.14f / 180.f;
        float vectorSize = .05 + (std::rand() % 400) / 2e3;
        initPos = vec(std::cos(angle) * vectorSize, std::sin(angle) * vectorSize);

        boids[i].init(vertices, indices, colors, initPos, velInit);
        //std::cout << &(boids[i]) << "\n";
    }

    std::cout << "leads:\n";
    std::vector<Lead> leads(N_LEADS);
    for (uint32_t i=0; i<N_LEADS; ++i){
        leads[i].init(vertices, indices, colors, vec(0,0), vec(0,0));
        //std::cout << &(leads[i]) << "\n";
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
                case SDL_MOUSEBUTTONUP:
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if (!leads.empty())
                        leads[0].steer(vec(2*(float)x/width - 1, 1 - 2*(float)y/height));
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
        for (auto& lead : leads){
            lead.update(dt);
        }

        updateWp(vertices, colors, indices);

        //SDL_Delay(10);
    }

    SDL_GL_DeleteContext(glContext);
    SDL_Quit();
    return 0;
}
