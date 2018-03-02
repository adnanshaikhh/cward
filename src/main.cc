#include "game.h"
#include "log.h"

int main(int argc, char* argv[])
{
	debug("cward started!");
	Game::run(&argc, &argv);
}