#include <iostream>
#include "openglWp.h"

int main(int argc, char *argv[])
{

  initWp();

  const float vertices[] = {
    0.0f, 0.5f, 0.0f, 1.0f,
    0.5f, -0.366f, 0.0f, 1.0f,
    -0.5f, -0.366f, 0.0f, 1.0f
  };
  const float colors[] = {
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f 	
  };

  glGenVertexArrays(1, &vao);

  // vertex_vbo
  glGenBuffers(1, &vertex_vbo); //create the buffer
  glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo); //we're "using" this one now
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // color_vbo
  glGenBuffers(1, &color_vbo); //create the buffer
  glBindBuffer(GL_ARRAY_BUFFER, color_vbo); //we're "using" this one now
  glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

  char bGameLoopRunning = 1;
  while (bGameLoopRunning)
  {
    SDL_Event e;
    if ( SDL_PollEvent(&e) ) 
    {
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
