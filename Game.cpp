#include "Game.hpp"

using namespace std; //Note: Loops are expensive??, therefore try to eliminate loops or reduce their size (for or while, etc)

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
			SDL_SetRenderDrawColor(renderer, 255,255,255,255);//set background color
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
	environment = Environment();
	biology = Biology(&environment);
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
void Game::update() {
	if (daytime < 96) { daytime++; }
	else { daytime = 0; }
	//cout << daytime << endl;

	for (int i = 0; i < biology.organisms.size(); i++) {//all humans move to position 15,15
		if (biology.organisms[i].species.species_name == "human") {
			biology.update(&biology.organisms[i]);
		}
	}
	
}


//this function seems inefficient, don't know if there's a better way than creating and destroying per texture every tick
void Game::textureManager(string texture, SDL_Rect destRect) {//textureManager feels like an unclear name, rename this function, this function takes in the image file and the location and size (destRect) to draw it on and adds it to the game's canvass (renderer)
	SDL_Surface* tmpSurface = IMG_Load(texture.c_str());
	SDL_Texture* tmpTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);//would it be better to store these in an array and access them from there?
	SDL_FreeSurface(tmpSurface); //this might not be necessary, maybe move to the game.clean() function
	SDL_RenderCopy(renderer, tmpTex, NULL, &destRect);
	SDL_DestroyTexture(tmpTex); //this might not be necessary, maybe move to the game.clean() function
}

void Game::render() {//to do: recieves absolute position data from world and translates to viewscreen relative position then draws to screen
	SDL_RenderClear(renderer);
	//add stuff to render here - 1st rendered = background, last rendered = foreground
	

	//resets destR for printing environment
	destR.x = 0;
	destR.y = 0;
	for (int r = 0; r < environment.rows; r++) { //prints out tilemap
		destR.y = r * 32;
		for (int c = 0;c < environment.columns;c++) {
			destR.x = c * 32;
			string tile_png = "";
			switch (environment.map[r][c])
			{
			case 0:
				tile_png = "pics/dirt.png";//these can be moved out of this file by have tile structs with the position and png instead of an array of ints in map
				break;
			case 1:
				tile_png = "pics/water.png";
				break;
			case 2:
				tile_png = "pics/stone.png";
				break;
			default:
				break;
			}
			textureManager(tile_png, destR);
		}
	}

	//render all organisms in the list, their x and y position are tile positions and so must be adjusted to screen location(x*32)
	for (int i = 0; i < biology.organisms.size(); i++) {
		destR.x = biology.organisms[i].position.x*32;
		destR.y = biology.organisms[i].position.y*32;
		textureManager(biology.organisms[i].species.png_file, destR);
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

