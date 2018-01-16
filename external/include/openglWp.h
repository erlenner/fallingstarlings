//gcc sdl2-opengl-sample.c -o sdl2-opengl-sample -Wall -std=c99 -I/usr/local/include/SDL2 -lSDL2 -I/usr/include/GL -lGL -lGLEW -Wall
#include <SDL2/SDL.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>
#include "conf.h"

#define  WGL_SWAP_METHOD_ARB WGL_SWAP_EXCHANGE_ARB

SDL_Window* window;
SDL_GLContext glContext;

GLuint BuildShaderProgram(const char *vsPath, const char *fsPath);
GLuint CreateShader(GLenum eShaderType, const char *strShaderFile);
GLuint shaderProgram;
GLuint vao;
GLuint vertex_vbo;
GLuint color_vbo;
GLuint elements;

uint32_t width, height;

int initWp(const std::vector<float>& vertices, const std::vector<float>& colors, const std::vector<uint32_t>& indices)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) return 1;

    //SDL_DisplayMode displayMode;
    //SDL_GetCurrentDisplayMode(0, &displayMode);
    width = 512;
    height = 512;
    //width = displayMode.w;
    //height = displayMode.h;

    window = SDL_CreateWindow("Falling Starlings", 0, 0,
        //SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        //SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        //displayMode.w, displayMode.h,
        width, height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_FULLSCREEN_DESKTOP);
        //SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);

    int idx = SDL_GetWindowDisplayIndex( window );
    SDL_Rect bounds;
    SDL_GetDisplayBounds( idx, &bounds );
    SDL_SetWindowBordered( window, SDL_FALSE );
    SDL_SetWindowPosition( window, bounds.x, bounds.y );
    SDL_SetWindowSize( window, bounds.w, bounds.h );

    width = bounds.w; height = bounds.h;


    glContext = SDL_GL_CreateContext(window);
    if (glContext == NULL)
    {
        printf("There was an error creating the OpenGL context!\n");
        return 0;
    }

    SDL_SetWindowFullscreen(window, SDL_FALSE);

    const unsigned char *version = glGetString(GL_VERSION);
    if (version == NULL) 
    {
        printf("There was an error creating the OpenGL context!\n");
        return 1;
    }

    //SDL_GL_MakeCurrent(window, glContext);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    //MUST make a context AND make it current BEFORE glewInit()!
    glewExperimental = GL_TRUE;
    GLenum glew_status = glewInit();
    if (glew_status != 0) 
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
        return 1;
    }

    shaderProgram = BuildShaderProgram("shaders/vs1.glsl", "shaders/fs1.glsl");
    if (shaderProgram == 1)
    {
        SDL_Quit();
        return 0;
    }

    glGenVertexArrays(1, &vao);

    // vertex_vbo
    glGenBuffers(1, &vertex_vbo); //create the buffer

    // color_vbo
    glGenBuffers(1, &color_vbo); //create the buffer

    // index_vbo
    glGenBuffers(1, &elements);

    std::cout << width << " " << height << "\n";
    ////glViewport(-width/2, -height/2, width, height);
    //glViewport(0, 0, width, height);
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //glOrtho(0, width, height, 0, -1, 1);
    //glMatrixMode(GL_MODELVIEW);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glEnable(GL_DEPTH_TEST);

    glUseProgram(shaderProgram);
    glViewport(0, 0, width, height);
    glClearColor(0.0,0.0,0.0,1.0);

    SDL_GL_SetSwapInterval(conf::use_vsync);

    return 0;
}

int updateWp(const std::vector<float>& vertices, const std::vector<float>& colors, const std::vector<uint32_t>& indices)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //glBindVertexArray(vao);

    // vertex_vbo
    glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);
    glEnableVertexAttribArray(0);
    // color_vbo
    glBindBuffer(GL_ARRAY_BUFFER, color_vbo); //we're "using" this one now
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*colors.size(), colors.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);
    glEnableVertexAttribArray(1);
    // indices_vbo
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t)*indices.size(), indices.data(), GL_DYNAMIC_DRAW);
    glDrawElements(GL_TRIANGLES, sizeof(uint32_t)*indices.size(), GL_UNSIGNED_INT, 0);

    SDL_GL_SwapWindow(window);
    return 0;
}

GLuint BuildShaderProgram(const char *vsPath, const char *fsPath)
{
    GLuint vertexShader;
    GLuint fragmentShader;

    vertexShader = CreateShader(GL_VERTEX_SHADER, vsPath);
    fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fsPath);

    GLuint tempProgram;
    tempProgram = glCreateProgram();

    glAttachShader(tempProgram, vertexShader);
    glAttachShader(tempProgram, fragmentShader);
    glBindAttribLocation(tempProgram, 0, "position");
    glBindAttribLocation(tempProgram, 1, "color");

    glLinkProgram(tempProgram);

    GLint status;
        glGetProgramiv(tempProgram, GL_LINK_STATUS, &status);
        if (status == GL_FALSE)
        {
            GLint infoLogLength;
            glGetProgramiv(tempProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

            GLchar strInfoLog[4096];
            glGetProgramInfoLog(tempProgram, infoLogLength, NULL, strInfoLog);
            printf("Shader linker failure: %s\n", strInfoLog);
            return -1;
        }

glDetachShader(tempProgram, vertexShader);
glDetachShader(tempProgram, fragmentShader);

return tempProgram;
}

GLuint CreateShader(GLenum eShaderType, const char *strShaderFile)
{
    char shaderSource[4096];
    char inChar;
    FILE *shaderFile;
    int i = 0;

    shaderFile = fopen(strShaderFile, "r");
    while(fscanf(shaderFile,"%c",&inChar) > 0)
    {
    shaderSource[i++] = inChar; //loading the file's chars into array
    }
    shaderSource[i - 1] = '\0';
    fclose(shaderFile);

    GLuint shader = glCreateShader(eShaderType);
    const char *ss = shaderSource;
    glShaderSource(shader, 1, &ss, NULL);

    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar strInfoLog[4096];
        glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

        char strShaderType[16];
        switch(eShaderType)
        {
            case GL_VERTEX_SHADER: sprintf(strShaderType, "vertex"); break;
            case GL_GEOMETRY_SHADER: sprintf(strShaderType, "geometry"); break;
            case GL_FRAGMENT_SHADER: sprintf(strShaderType, "fragment"); break;
        }

        printf("Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
        return -1;
    }

return shader;
}
