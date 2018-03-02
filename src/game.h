#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>

class Game
{
	public:
		static int run(int* argc, char** argv[]);
	private:
		Game(GLFWwindow *window) : _window(window) {}
		void loop();
		static Game *_current_game;
		GLFWwindow *_window;
		double _last_delta;
};