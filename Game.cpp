#include "Game.hpp"

using namespace std; 

Game::Game() {
	isRunning = false;
}

Game::~Game() {

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		cout << "Subsystems initialized." << endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			cout << "Window created." << endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);//set background color
			cout << "Renderer created." << endl;
		}
		isRunning = true;
	}
	else {
		isRunning = false;
	}
}

SDL_Rect srcR, destR;
void Game::initGameState() {
	int a = 0;
	environment = Environment(a);
	biology = Biology(a);
	destR.h = 32;
	destR.w = 32;
	destR.x = 0;
	destR.y = 0;
}

void Game::handleEvents() { //I think this handles user inputs such as keyboard and mouse
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}


//Every 4 updates is an hour, 24 hours per day, so 96 updates per day
int daytime = 0;
int days_passed = 0;
void Game::update() {
	if (daytime < 96) { daytime++; }
	else { daytime = 0; days_passed++; cout << days_passed << " days passed" << endl; }

	biology.update_all();

}


//this function seems inefficient, don't know if there's a better way than creating and destroying per texture every tick
void Game::textureManager(string texture, SDL_Rect destRect) {//textureManager feels like an unclear name, rename this function, this function takes in the image file and the location and size (destRect) to draw it on and adds it to the game's canvass (renderer)
	SDL_Surface* tmpSurface = IMG_Load(texture.c_str());
	SDL_Texture* tmpTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);//would it be better to store these in an array and access them from there?
	SDL_FreeSurface(tmpSurface); //this might not be necessary, maybe move to the game.clean() function
	SDL_RenderCopy(renderer, tmpTex, NULL, &destRect);
	SDL_DestroyTexture(tmpTex); //this might not be necessary, maybe move to the game.clean() function
}

void Game::render() {
	SDL_RenderClear(renderer);
	//resets destR for printing environment
	destR.x = 0;
	destR.y = 0;
	//render all tiles within screen view and all organisms and items on those tiles, adjusted for position on screen (x*32)
	//my laptop screen fits a 47(x)*26(y) tilemap
	int corner1_x = 0;
	int corner1_y = 0;
	int corner2_x = 47;
	int corner2_y = 26;
	for (int y = corner1_y; y < corner2_y; y++) {
		destR.y = y * 32;
		for (int x = corner1_x; x < corner2_x; x++) {
			destR.x = x * 32;
			textureManager(environment.map[y][x].terrain_png, destR);
			Environment::Tile t = environment.map[y][x];
			for (int i = 0; i < t.organism_id.size(); i++) {//need to figure out how to efficiently render in correct order so things like grass are rendered first and humans last
				Biology::Organism o = biology.get_by_id(t.organism_id[i]);
				textureManager("pics/" + biology.get_species(o.species_id).species_name + o.png_file_state + ".png", destR);
			}
		}
	}
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout << "Game cleaned." << endl;
}

bool Game::running() {
	return isRunning;
}

