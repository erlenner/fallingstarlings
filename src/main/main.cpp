#include <iostream>
#include "openglWp.h"
#include "Boid.h"
#include "Lead.h"
#include "utils.h"
#include "conf.h"

int main(int argc, char *argv[])
{

    float now, before, dt;
    before = now = secs();


    std::vector<float> vertices;
    std::vector<float> colors;
    std::vector<uint32_t> indices;

    const uint32_t n_boids_a = 512, n_leads_a = 1;

    add_capacity(n_boids_a, conf::boid_points, vertices, colors, indices);
    add_capacity(n_leads_a, conf::lead_points, vertices, colors, indices);

    std::cout << "boids:\n";
    std::vector<Boid> boids(n_boids_a);
    initialize_boids(boids.data(), n_boids_a, STARLING, vertices, colors, indices);
    for (auto& boid : boids)
        std::cout << &boid << "\t";
    std::cout << "\n";


    std::cout << "leads:\n";
    array<Lead, n_leads_a> leads;
    leads.push_back(Lead());
    leads[0].init(vertices, indices, colors, vec(0,0), vec(0,0), STARLING);
    array<Lead*, n_leads_a> lead_refs;
    for (auto& lead : leads)
        lead_refs.push_back(&lead);
    for (auto& lead : leads)
        std::cout << &lead << "\t";
    std::cout << "\n";

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
        now = secs();
        dt = now - before;
        before = now;

        float rate = 1/dt;
        //if (rate < 55)
        std::cout << "rate:\t" << rate << "\n";

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
        std::cout << "-1:\t" << secs() - now << "\n";
        now = secs();

        for (auto& boid : boids)
            boid.update(dt, lead_refs);
        std::cout << "0:\t" << secs() - now << "\n";
        now = secs();
        for (auto& lead : leads)
            lead.update(dt);
        std::cout << "1:\t" << secs() - now << "\n";
        now = secs();
        updateWp(vertices, colors, indices);
        std::cout << "2:\t" << secs() - now << "\n";
        now = secs();


        //SDL_Delay(10);
    }

    SDL_GL_DeleteContext(glContext);
    SDL_Quit();
    return 0;
}
