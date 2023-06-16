#ifndef Environment_hpp
#define Environment_hpp
#include <string>
#include <iostream>
#include <vector>


using namespace std;

class Environment {
public:
	Environment();//empty default constructor to prevent unintended initialization
	Environment(int a);
	static int id_iterator;
	struct Tile {
		int x;
		int y;
		vector<int> organism_id;
		vector<int> item_id;
		string terrain;
		string terrain_png;
	};
	void setMap();
	static const int rows = 26;		//y
	static const int columns = 47;	//x
	static Tile map[rows][columns];
};

#endif