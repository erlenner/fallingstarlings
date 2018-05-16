#include <iostream>
#include <thread>
#include <signal.h>
#include <unistd.h>
#include "openglWp.h"
#include "Boid.h"
#include "Lead.h"
#include "utils.h"
#include "conf.h"
#include "Context.h"
//#include <fenv.h>

bool shouldStop = false;

std::vector<std::thread> threads;

void cleanup(int signum){

    shouldStop = true;
}

void pollControls(Lead& lead, Map& map){
    //double dt;
    //uint64_t now, before;
    //before = now = SDL_GetPerformanceCounter();
    while (!shouldStop){
        //iterate_time(now, before, dt, 30);

        SDL_Event e;
        while ( SDL_PollEvent(&e) ) {
            switch (e.type) {
                case SDL_QUIT:
                    shouldStop = true;
                break;
                case SDL_MOUSEBUTTONUP:
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    lead.steer(frame2glob(vec(2*(float)x/width - 1, 1 - 2*(float)y/height)));
                break;
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            shouldStop = true;
                        break;
                        case SDLK_w:
                            map.activateScroll(1,-1);
                        break;
                        case SDLK_a:
                            map.activateScroll(0,-1);
                        break;
                        case SDLK_s:
                            map.activateScroll(1,1);
                        break;
                        case SDLK_d:
                            map.activateScroll(0,1);
                        break;
                        case SDLK_r:
                            map.scrollToLead(lead);
                        break;
                        case SDLK_t:
                            map.keepLeadCentered ^= 1;
                        break;
                    }
                break;
                case SDL_KEYUP:
                    switch (e.key.keysym.sym) {
                        case SDLK_w:
                            map.resetScroll(1);
                        break;
                        case SDLK_a:
                            map.resetScroll(0);
                        break;
                        case SDLK_s:
                            map.resetScroll(1);
                        break;
                        case SDLK_d:
                            map.resetScroll(0);
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

    Map* map = &barrens;
    Context::init(PLAY, map);

    std::vector<float> vertices;
    std::vector<float> colors;
    std::vector<uint32_t> indices;

    const uint32_t n_boids_a = 200, n_leads_a = 1;
    const uint32_t n_boids_b = 200, n_leads_b = 1;

    std::vector<Boid> boids_a(n_boids_a);
    array<Lead, n_leads_a> leads_a = { Lead() };

    std::vector<Boid> boids_b(n_boids_b);
    array<Lead, n_leads_b> leads_b = { Lead() };

    add_capacity(n_leads_a, starling.n_vertices, starling.n_indices, vertices, colors, indices);
    add_capacity(n_boids_a, starling.n_vertices, starling.n_indices, vertices, colors, indices);

    add_capacity(n_leads_b, auk.n_vertices, auk.n_indices, vertices, colors, indices);
    add_capacity(n_boids_b, auk.n_vertices, auk.n_indices, vertices, colors, indices);


    vec center_a = {.3,.3};
    vec center_b = {.7,.7};
    initialize_boids(boids_a.data(), n_boids_a, center_a, &starling, vertices, colors, indices);
    leads_a[0].init(vertices, indices, colors, center_a, &starling_lead);

    initialize_boids(boids_b.data(), n_boids_b, center_b, &auk, vertices, colors, indices);
    leads_b[0].init(vertices, indices, colors, center_b, &auk_lead);

    initWp(vertices, colors, indices, *map);

    loadMap(*map);

    threads.push_back(std::thread(pollControls, std::ref(leads_a[0]), std::ref(*map)));

    signal(SIGINT, cleanup);

    while (!shouldStop){

            iterate_time(now, before, dt, 60);

            std::cout << "rate:\t" << 1/dt << "\t" << dt << "\n";

            updateWp(vertices, colors, indices);

            for (auto& boid : boids_b)
                boid.update(dt, leads_b.data, n_leads_b);
            for (auto& lead : leads_b)
                lead.update(dt);
            for (auto& boid : boids_a)
                boid.update(dt, leads_a.data, n_leads_a);
            for (auto& lead : leads_a)
                lead.update(dt);

        map->applyScroll(dt, leads_a[0]);
    }
    for (auto& thread : threads)
        thread.join();

    cleanupWp();

    return 0;
}
