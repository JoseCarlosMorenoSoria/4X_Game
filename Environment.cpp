#include "Environment.hpp"
using namespace std;

Environment::Tile Environment::map[rows][columns];

Environment::Environment(){}
Environment::Environment(int a) {
	setMap();
}

void Environment::setMap() {
	for (int r = 0; r < rows; r++) {
		for (int c = 0;c < columns;c++) {
			map[r][c].x = c;
			map[r][c].y = r;
			if (r > 20) {
				map[r][c].terrain = "shallow water";
				map[r][c].terrain_png = "pics/water.png";
				map[r][c].water_level = 100;
			}
			else {
				map[r][c].terrain = "dirt";
				map[r][c].terrain_png = "pics/dirt.png";
				map[r][c].nutrient_level = 50;
			}
		}
	}
}

void Environment::dirt_water_spread(){
	for (int r = 0; r < rows; r++) {
		for (int c = 0;c < columns;c++) {
			
			map[r][c].water_level = 0; //resets water level to be recalculated each update
				for (int y = r-6; y < r+6; y++) {
					for (int x = c-6; x < c-6; x++) {
						int distance = abs(r - y) + abs(c - x) - 1;
						if (distance != 0) {
							map[r][c].water_level += map[y][x].water_level * (1 / (2 * distance));//gets the water level of all tiles within a 6 tile radius and adds them to current tile water level, halving amount added per number of tiles away.
						}
					}
				}
			
		}
	}
}

void Environment::temperature_spread() {//one problem with these functions is that there might be a problem where the calculation order of tiles matters, such that if tile A is calculated before B, the result will be different than if B is calculated before A
	for (int r = 0; r < rows; r++) {
		for (int c = 0;c < columns;c++) {

			map[r][c].temperature = 50; //resets to default temperature. Need to make the default change according to daytime/cloud cover and season
			for (int y = r - 6; y < r + 6; y++) {
				for (int x = c - 6; x < c - 6; x++) {
					int distance = abs(r - y) + abs(c - x) - 1;
					if (distance != 0) {
						map[r][c].temperature += map[y][x].temperature * (1 / (2 * distance));//same as water spread, this only gets temperature from other tiles
						//need to implement temperature from heat sources such as a fire
						//need to implement temperature change from shade, indoors insulation, wind/water currents
					}
				}
			}

		}
	}
}

void Environment::update() {
	dirt_water_spread();
	temperature_spread();
}