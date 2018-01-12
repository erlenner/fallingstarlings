#include <iostream>
#include <thread>
#include <signal.h>
#include <unistd.h>
#include "openglWp.h"
#include "Boid.h"
#include "Lead.h"
#include "utils.h"
#include "conf.h"
#include "mutexctrl.h"
//#include <fenv.h>

bool shouldStop = false;

std::vector<std::thread> threads;

void cleanup(int signum){

    shouldStop = true;
}

void pollControls(Lead& lead){
    while (!shouldStop){

        SDL_Event e;
        while ( SDL_PollEvent(&e) ) {
            switch (e.type) {
                case SDL_QUIT:
                    shouldStop = true;
                break;
                case SDL_MOUSEBUTTONUP:
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    {
                        locker l(LEAD_DEST, 0);
                        lead.steer(vec(2*(float)x/width - 1, 1 - 2*(float)y/height));
                    }
                break;
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            shouldStop = true;
                        break;
                        case SDLK_CAPSLOCK:
                            shouldStop = true;
                        break;
                    }
                break;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    //feenableexcept(FE_ALL_EXCEPT & ~FE_INEXACT);

    double dt;
    uint64_t now, before;
    before = now = SDL_GetPerformanceCounter();

    std::vector<float> vertices;
    std::vector<float> colors;
    std::vector<uint32_t> indices;

    const uint32_t n_boids_a = 1000, n_leads_a = 1;
    //const uint32_t n_boids_b = 600, n_leads_b = 1;

    std::vector<Boid> boids_a(n_boids_a);
    array<Lead, n_leads_a> leads_a = { Lead() };

    //std::vector<Boid> boids_b(n_boids_b);
    //array<Lead, n_leads_b> leads_b = { Lead() };

    add_capacity(n_leads_a, starling.n_vertices, starling.n_indices, vertices, colors, indices);
    add_capacity(n_boids_a, starling.n_vertices, starling.n_indices, vertices, colors, indices);

    //add_capacity(n_leads_b, starling.n_vertices, starling.n_indices, vertices, colors, indices);
    //add_capacity(n_boids_b, starling.n_vertices, starling.n_indices, vertices, colors, indices);


    initialize_boids(boids_a.data(), n_boids_a, {.5,.5}, &starling, vertices, colors, indices);
    leads_a[0].init(vertices, indices, colors, {.5,.5}, &starling);

    //initialize_boids(boids_b.data(), n_boids_b, {-.5,-.5}, &starling, vertices, colors, indices);
    //leads_b[0].init(vertices, indices, colors, {-.5,-.5}, &starling);

    //std::cout << "boids:\n";
    //for (auto& boid : boids_a)
    //    std::cout << &boid << "\t";
    //std::cout << "\n";


    //std::cout << "leads:\n";
    //for (auto& lead : leads_a)
    //    std::cout << &lead << "\t";
    //std::cout << "\n";

    //std::cout << "\nvertices:\n";
    //for (uint32_t i=0; i<vertices.size(); ++i){
    //    std::cout << vertices[i] << "\t";
    //    if(i%12==11) std::cout << "\n";
    //}
    //std::cout << "\nindices:\n";
    //for (uint32_t i=0; i<indices.size(); ++i)
    //    std::cout << (int)indices[i] << "\t";
    //std::cout << "\ncolors:\n";
    //for (uint32_t i=0; i<colors.size(); ++i)
    //    std::cout << colors[i] << "\t";
    //std::cout << "\nN:\n";
    //std::cout << n_boids_a << "\t" << vertices.size() << "\t" << colors.size() << "\t" << indices.size() << "\n";

    initWp(vertices, colors, indices);

    threads.push_back(std::thread(pollControls, std::ref(leads_a[0])));

    signal(SIGINT, cleanup);

    while (!shouldStop){

        now = SDL_GetPerformanceCounter();
        dt = (double)(now - before) / SDL_GetPerformanceFrequency();
        if (dt < .017){
            SDL_Delay(17 - 1000*dt);
            now = SDL_GetPerformanceCounter();
            dt = (double)(now - before) / SDL_GetPerformanceFrequency();
        }
        before = now;

        std::cout << "rate:\t" << 1/dt << "\t" << dt << "\n";

        updateWp(vertices, colors, indices);

        //for (auto& boid : boids_b)
        //    boid.update(dt, leads_b.data, n_leads_b);
        //for (auto& lead : leads_b)
        //    lead.update(dt);
        for (auto& boid : boids_a)
            boid.update(dt, leads_a.data, n_leads_a);
        {
            locker l(0, LEAD_DEST);
            for (auto& lead : leads_a)
                lead.update(dt);
        }
    }
    for (auto& thread : threads)
        thread.join();

    SDL_GL_DeleteContext(glContext);
    SDL_Quit();
    return 0;
}
