#include <SDL2/SDL.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <SOIL/SOIL.h>
#include <vector>
#include "conf.h"
#include "Map.h"

//#define  WGL_SWAP_METHOD_ARB WGL_SWAP_EXCHANGE_ARB

SDL_Window* window;
SDL_GLContext glContext;

GLuint BuildShaderProgram(const char *vsPath, const char *fsPath);
GLuint CreateShader(GLenum eShaderType, const char *strShaderFile);
GLuint unit_shader;
GLuint unit_vao;
GLuint vertex_vbo;
GLuint color_vbo;
GLuint elements;

GLuint map_shader;
GLuint map_vao;
GLuint map_vertex_vbo;
GLuint map_tex_coord_vbo;
GLuint map_elements_vbo;
GLuint map_tex_vbo;
GLint map_coords_loc;

uint32_t width, height;

int initWp(const std::vector<float>& vertices, const std::vector<float>& colors, const std::vector<uint32_t>& indices, const Map& map)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) return 1;

    //SDL_DisplayMode displayMode;
    //SDL_GetCurrentDisplayMode(0, &displayMode);
    //width = displayMode.w;
    //height = displayMode.h;
    width = 512;
    height = 512;

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
    //printf((const char*)version);
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

    unit_shader = BuildShaderProgram("shaders/unit_vs.glsl", "shaders/unit_fs.glsl");
    map_shader = BuildShaderProgram("shaders/map_vs.glsl", "shaders/map_fs.glsl");

    // vbos and vbas
    glGenVertexArrays(1, &unit_vao);

    // vertex_vbo
    glGenBuffers(1, &vertex_vbo);
    // color_vbo
    glGenBuffers(1, &color_vbo);
    // index_vbo
    glGenBuffers(1, &elements);

    glBindVertexArray(unit_vao);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
    GLint posAttrib = glGetAttribLocation(unit_shader, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
    GLint colAttrib = glGetAttribLocation(unit_shader, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t)*indices.size(), indices.data(), GL_STATIC_DRAW);

    map_coords_loc = glGetUniformLocation(unit_shader, "map_info");

    //std::cout << width << " " << height << "\n";
    ////glViewport(-width/2, -height/2, width, height);
    //glViewport(0, 0, width, height);
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //glOrtho(0, width, height, 0, -1, 1);
    //glMatrixMode(GL_MODELVIEW);

    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_BLEND);

    //glEnable(GL_DEPTH_TEST);

    //glViewport(0, 0, width, height);
    //glClearColor(0.0,0.0,0.0,1.0);

    GLfloat map_vertices[] = {
    //  Position      Color             
        -1.0f,  1.0f, 1.0f, 0.0f, 0.0f,  // NW
         1.0f,  1.0f, 0.0f, 1.0f, 0.0f,  // NE
         1.0f, -1.0f, 0.0f, 0.0f, 1.0f,  // SE
        -1.0f, -1.0f, 1.0f, 1.0f, 1.0f,  // SW
    };

    GLuint map_indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    glGenVertexArrays(1, &map_vao);
    glGenBuffers(1, &map_vertex_vbo);
    glGenBuffers(1, &map_tex_coord_vbo);
    glGenBuffers(1, &map_elements_vbo);

    glBindVertexArray(map_vao);

    glBindBuffer(GL_ARRAY_BUFFER, map_vertex_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(map_vertices), map_vertices, GL_STATIC_DRAW);

    posAttrib = glGetAttribLocation(map_shader, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
    colAttrib = glGetAttribLocation(map_shader, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(2 * sizeof(GLfloat)));
    glBindBuffer(GL_ARRAY_BUFFER, map_tex_coord_vbo);
    GLint texAttrib = glGetAttribLocation(map_shader, "texcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, map_elements_vbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(map_indices), map_indices, GL_STATIC_DRAW);


    SDL_GL_SetSwapInterval(conf::use_vsync);

    return 0;
}

int loadMap(const Map& map)
{
    // Load textures
    glGenTextures(1, &map_tex_vbo);

    int width, height;
    unsigned char* image;

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, map_tex_vbo);
    image = SOIL_load_image(map.img_path, &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);
    glUniform1i(glGetUniformLocation(map_shader, "tex"), 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return 0;
}


int updateWp(const std::vector<float>& vertices, const std::vector<float>& colors, const std::vector<uint32_t>& indices, const Map& map)
{
    std::cout << "map.position(): " << map.glob_pos() << "\n";

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(map_shader);
    glBindVertexArray(map_vao);
    glBindBuffer(GL_ARRAY_BUFFER, map_tex_coord_vbo);
    glBufferData(GL_ARRAY_BUFFER, 8*sizeof(float), map.coords, GL_DYNAMIC_DRAW);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


    glUseProgram(unit_shader);
    glBindVertexArray(unit_vao);
    // vertex_vbo
    glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size(), vertices.data(), GL_STREAM_DRAW);
    // color_vbo
    glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*colors.size(), colors.data(), GL_DYNAMIC_DRAW);
    glUniform4f(map_coords_loc, map.glob_pos().x, map.glob_pos().y, map.span().x, map.span().y);
    glDrawElements(GL_TRIANGLES, sizeof(uint32_t)*indices.size(), GL_UNSIGNED_INT, 0);


    SDL_GL_SwapWindow(window);
    return 0;
}

int cleanupWp()
{

    //glDeleteTextures(1, map_tex_vbo);
    //glDeleteProgram(map_shader);
    //glDeleteProgram(unit_shader);
    //glDeleteBuffers(1, &vertex_vbo);


    SDL_GL_DeleteContext(glContext);
    SDL_Quit();

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
    glBindFragDataLocation(tempProgram, 0, "outColor");

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
