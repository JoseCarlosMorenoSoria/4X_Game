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
			}
			else {
				map[r][c].terrain = "dirt";
				map[r][c].terrain_png = "pics/dirt.png";
			}
		}
	}
}
