#ifndef Environment_hpp
#define Environment_hpp
#include <string>
#include <iostream>
#include <vector>

using namespace std;


class Environment {
public:
	Environment();
	~Environment();


	static const int columns = 47; //x value
	static const int rows = 26; //y value
	void LoadMap(int arr[rows][columns]);
	void setMap();//for loading a map defined by the function rather than copying an existing map preset

	//int map[rows][columns]; //map[y][x] where 0,0 is the top left corner

	

	struct Tile {//used to hold tile specific info
		string terrain="";
		string terrain_png="";
		vector<int> tile_organisms_id; //never store pointers, because the vector that stores objects changes their addresses every time an element is erased
	};

	Tile map[rows][columns];

	Tile* get_tile(int x, int y);
	void tie_to_tile(int id, int x, int y);//ties an organism to a tile
	void untie_from_tile(int id, int x, int y);


};

#endif