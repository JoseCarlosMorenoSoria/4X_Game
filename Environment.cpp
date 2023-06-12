#include "Environment.hpp"
using namespace std;


int map1[Environment::rows][Environment::columns] = {
	{2,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,2},
	{0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
	{0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
	{0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
	{0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},

	{0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
	{0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
	{0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
	{0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
	{0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},


	{0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
	{0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
	{0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
	{0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
	{0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},

	{0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 1,1,1,1,1},
	{0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 1,1,1,1,1},
	{0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 1,1,1,1,1},
	{0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 1,1,1,1,1},
	{2,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 1,1,1,1,2}
};




Environment::Environment() {
	//LoadMap(map1);
	setMap();
}
Environment::~Environment() {

}

void Environment::LoadMap(int arr[rows][columns]) {
	for (int r = 0; r < rows; r++) {
		for (int c = 0;c < columns;c++) {
			//map[r][c] = map1[r][c];
		}
	}
}

void Environment::setMap() {
	for (int r = 0; r < rows; r++) {
		for (int c = 0;c < columns;c++) {
			if(r>20 && c>40){
				map[r][c].terrain = "water";
				map[r][c].terrain_png = "pics/water.png";
			}
			else {
				map[r][c].terrain = "dirt";
				map[r][c].terrain_png = "pics/dirt.png";
			}
		}
	}
}

Environment::Tile* Environment::get_tile(int x, int y) {
	for (int r = 0; r < rows; r++) {
		for (int c = 0;c < columns;c++) {
			if (r == y && c == x) {
				return &map[r][c];
			}
		}
	}
	return nullptr;
}

void Environment::tie_to_tile(int id, int x, int y) {
	Tile* tile = get_tile(x,y);
	tile->tile_organisms_id.push_back(id);
}

void Environment::untie_from_tile(int id, int x, int y) {
	Tile* tile = get_tile(x,y);
	if (tile == nullptr) { return; }//this shouldn't happen (the tile not existing), don't know why it does
	if (tile->tile_organisms_id.size() == 0) { return; }
	int index = -1;
	for (int i = 0; i < tile->tile_organisms_id.size(); i++) {
		if (tile->tile_organisms_id[i] == id) {
			index = i;
			break;
		}
	}
	if (index < 0) { return; }
	tile->tile_organisms_id.erase(tile->tile_organisms_id.begin()+index);
}