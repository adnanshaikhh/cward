#include "graphics.h"

#include "log.h"

#include <GL/glew.h>
#include <SDL.h>

static SDL_Window* screen = NULL;
static SDL_GLContext* context = NULL;

static int window_flags = 0;
static int window_multisamples = 0;
static int window_multisamplesbuffs = 0;
static int window_antialiasing = 0;

void graphics_init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		error("SDL_Init error: %s\n", SDL_GetError());
	}

	window_flags = SDL_WINDOW_OPENGL;
	window_multisamples = 4;
	window_multisamplesbuffs = 1;
	window_antialiasing = 1;

	graphics_viewport_start();
}

void graphics_viewport_start()
{
	//Use OpenGL 3.1 core
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// Turn on double buffering with a 24bit Z buffer.
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	screen = SDL_CreateWindow("Corange",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		800, 600,
		window_flags);

	if (!screen)
	{
		error("Could not create SDL window: %s", SDL_GetError());
	}

	SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1);
	context = SDL_GL_CreateContext(screen);

	if (!context)
	{
		error("Could not create SDL context: %s", SDL_GetError());
	}

	glewExperimental = GL_TRUE;
	GLenum glew_error = glewInit();

	if (glew_error != GLEW_OK)
	{
		error("Error initializing GLEW %s\n", glewGetErrorString(glew_error));
	}

	debug("OpenGL Version: %s\n", glGetString(GL_VERSION));
	debug("GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	debug("Vendor: %s\n", glGetString(GL_VENDOR));
	debug("Renderer: %s\n", glGetString(GL_RENDERER));

	//OpenGL Settings
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);

	if (SDL_GL_SetSwapInterval(1) < 0)
	{
		error("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
	}

	//SDL_GL_LoadExtensions();

	glViewport(0, 0, 800, 600);
}

void graphics_swap()
{
	SDL_GL_SwapWindow(screen);
}

void graphics_viewport_set_title(const char* title)
{
	SDL_SetWindowTitle(screen, title);
}

const char* graphics_viewport_title()
{
	return SDL_GetWindowTitle(screen);
}

void graphics_finish()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(screen);
}

