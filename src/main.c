#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <gl/glew.h>

int Init()
{
  if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    printf("SDL_Init error: %s\n", SDL_GetError());
    return 1;
  }
  else
  {
    //Use OpenGL 3.1 core
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

    // Turn on double buffering with a 24bit Z buffer.
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_Window* disp_window;
    disp_window = SDL_CreateWindow("cward",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        512,
        512,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if(!disp_window)
    {
      printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
      return 1;
    }
    else
    {

      SDL_GLContext main_context;

      main_context = SDL_GL_CreateContext(disp_window);

      if(main_context == NULL)
      {
        printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
        return 1;
      }
      else
      {
        glewExperimental = GL_TRUE;
        GLenum glew_error = glewInit();

        if(glew_error != GLEW_OK)
        {
          printf("Error initializing GLEW %s\n", glewGetErrorString(glew_error));
        }

        printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
        printf("GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
        printf("Vendor: %s\n", glGetString(GL_VENDOR));
        printf("Renderer: %s\n", glGetString(GL_RENDERER));

        //OpenGL Settings
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        //Use Vsync
        if(SDL_GL_SetSwapInterval(1) < 0)
        {
          printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
        }

      }

    }
  }
  return 0;
}

int main(int argc, char** argv[])
{
  if(Init())
  {
    printf("Failed to initialize\n");
    return 1;
  }
  else
  {   
    while(1)
    {
    }
    SDL_Quit();
  }

  return 0;
} 
