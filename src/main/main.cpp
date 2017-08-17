#include <iostream>
#include "openglWp.h"
#include "Boid.h"
#include "Lead.h"
#include "utils.h"
#include "conf.h"

int main(int argc, char *argv[])
{
    std::vector<float> vertices;
    std::vector<float> colors;
    std::vector<uint32_t> indices;

    vertices.reserve(   conf::n_boids*conf::boid_points*2 + conf::n_leads*conf::lead_points*2);
    colors.reserve(     conf::n_boids*conf::boid_points*4 + conf::n_leads*conf::lead_points*4);
    indices.reserve(    conf::n_boids*conf::boid_points   + conf::n_leads*conf::lead_points);

    float now, before, dt;
    before = now = secs();

    std::cout << "boids:\n";
    std::vector<Boid> boids(conf::n_boids);
    for (uint32_t i=0; i<conf::n_boids; ++i){
        static vec initPos, velInit(.1,.1);

        float angle = (std::rand() % 360) * 3.14f / 180.f;
        float vectorSize = .05 + (std::rand() % 500) / 2e3;
        initPos = vec(std::cos(angle) * vectorSize, std::sin(angle) * vectorSize);

        boids[i].init(vertices, indices, colors, initPos, velInit);
        std::cout << &(boids[i]) << "\n";
    }

    std::cout << "leads:\n";
    array<Lead, conf::n_leads> leads;
    leads.push_back(Lead());
    leads[0].init(vertices, indices, colors, vec(0,0), vec(0,0));
    std::cout << &(leads[0]) << "\n";

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

        float rate = 1/dt;
        if (rate < 55)
        std::cout << "rate:\t" << rate << "\n";

        std::cout << "l0:\t" << &(leads[0]) << "\n";
        for (auto& boid : boids){
            boid.update(dt, leads);
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
