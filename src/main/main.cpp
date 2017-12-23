#include <iostream>
#include "openglWp.h"
#include "Boid.h"
#include "Lead.h"
#include "utils.h"
#include "conf.h"

int main(int argc, char *argv[])
{

    float now, before, dt, freq;
    before = now = SDL_GetPerformanceCounter();
    freq = SDL_GetPerformanceFrequency();


    std::vector<float> vertices;
    std::vector<float> colors;
    std::vector<uint32_t> indices;

    const uint32_t n_boids_a = 200, n_leads_a = 1;
    const uint32_t n_boids_b = 300, n_leads_b = 1;

    add_capacity(n_boids_a, conf::boid_points, vertices, colors, indices);
    add_capacity(n_leads_a, conf::lead_points, vertices, colors, indices);
    add_capacity(n_boids_b, conf::boid_points, vertices, colors, indices);
    add_capacity(n_leads_b, conf::lead_points, vertices, colors, indices);

    std::vector<Boid> boids_a(n_boids_a);
    initialize_boids(boids_a.data(), n_boids_a, vec(.5,.5), STARLING, vertices, colors, indices);
    std::cout << "boids:\n";
    for (auto& boid : boids_a)
        std::cout << &boid << "\t";
    std::cout << "\n";
    std::vector<Boid> boids_b(n_boids_b);
    initialize_boids(boids_b.data(), n_boids_b, vec(-.5,-.5), AUK, vertices, colors, indices);


    array<Lead, n_leads_a> leads_a = { Lead() };
    leads_a[0].init(vertices, indices, colors, vec(.5,.5), STARLING);
    std::cout << "leads:\n";
    for (auto& lead : leads_a)
        std::cout << &lead << "\t";
    std::cout << "\n";
    array<Lead, n_leads_b> leads_b = { Lead() };
    leads_b[0].init(vertices, indices, colors, vec(-.5,-.5), AUK);

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
                    if (!leads_a.empty())
                        leads_a[0].steer(vec(2*(float)x/width - 1, 1 - 2*(float)y/height));
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

        freq = SDL_GetPerformanceFrequency();
        now = SDL_GetPerformanceCounter();
        dt = (now - before) / (float)freq;
        if (dt < .017){
            SDL_Delay(17 - 1000*dt);
            now = SDL_GetPerformanceCounter();
            dt = (now - before) / (float)freq;
        }
        before = now;

        float rate = 1/dt;
        //if (rate < 55)
        std::cout << "rate:\t" << rate << "\n";

        updateWp(vertices, colors, indices);

        for (auto& boid : boids_a)
            boid.update(dt, leads_a.data, n_leads_a);
        for (auto& lead : leads_a)
            lead.update(dt);
        for (auto& boid : boids_b)
            boid.update(dt, leads_b.data, n_leads_b);
        for (auto& lead : leads_b)
            lead.update(dt);


        //SDL_Delay(10);
    }

    SDL_GL_DeleteContext(glContext);
    SDL_Quit();
    return 0;
}
