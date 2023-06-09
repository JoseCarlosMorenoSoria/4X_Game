#include "Game.hpp"

Game game; //rather than use pointers like the tutorial, I am using only instances to avoid memory leaks

int main(int argc, const char* argv[]) {

	//frame rate variables
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;

	game = Game();
	game.init("Game Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (32*48), (32*27), false);
	game.initGameState();
	
	while (game.running()) {
		frameStart = SDL_GetTicks();//for capping frame rate below
		game.handleEvents(); 
		game.update();
		game.render();
		//caps the frame rate		might need to implement this differently (or remove it?) as it might also slow down background calculations, idk
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}
	game.clean();

	return 0;
}