//gcc sdl2-opengl-sample.c -o sdl2-opengl-sample -Wall -std=c99 -I/usr/local/include/SDL2 -lSDL2 -I/usr/include/GL -lGL -lGLEW -Wall
#include <GL/glew.h>
#include <SDL2/SDL.h>

SDL_Window* window;
SDL_GLContext glContext;

int initWp();
int updateWp();
GLuint BuildShaderProgram(const char *vsPath, const char *fsPath);
GLuint CreateShader(GLenum eShaderType, const char *strShaderFile);
GLuint shaderProgram;
GLuint vao;
GLuint vertex_vbo;
GLuint color_vbo;
GLuint elements;

int initWp()
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;

  window = SDL_CreateWindow("My Game Window",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    640, 480,
    SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

  glContext = SDL_GL_CreateContext(window);
  if (glContext == NULL)
  {
  	printf("There was an error creating the OpenGL context!\n");
  	return 0;
  }

  const unsigned char *version = glGetString(GL_VERSION);
  if (version == NULL) 
  {
  	printf("There was an error creating the OpenGL context!\n");
  	return 1;
  }

  SDL_GL_MakeCurrent(window, glContext);

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

  return 0;
}

int updateWp()
{
  glClearColor(0.0,0.0,0.0,0.0);
  glClear(GL_COLOR_BUFFER_BIT);

  glBindVertexArray(vao);

  glUseProgram(shaderProgram);
  // vertex_vbo
  glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glEnableVertexAttribArray(0);
  // color_vbo
  glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glEnableVertexAttribArray(1);
  //glDrawArrays(GL_TRIANGLES, 0, 3);
  // indices:vbo
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements);
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, 0);

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
