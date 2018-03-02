#include "game.h"

#include "mathops.h"

// Maximum time step is 100ms.
static const double MAX_TIME_STEP = 0.1;

Game *Game::_current_game = { 0 };

/* static */
int Game::run(int* argc, char** argv[])
{
	if (!glfwInit())
		return -1;
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	GLFWwindow* window = glfwCreateWindow(640, 480, "cward", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	Game game(window);
	_current_game = &game;
	game.loop();

	_current_game = nullptr;
	glfwTerminate();
	return 0;
}

void Game::loop() {
	glfwMakeContextCurrent(_window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	//TODO: add debug macro switch
	glEnable(GL_DEBUG_OUTPUT);

	int32_t width, height;
	glfwGetFramebufferSize(_window, &width, &height);
}