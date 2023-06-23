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
		bool has_smoke = false;
		bool has_toxic_gas = false;
		float temperature = 50;//measured in Celsius because it makes it easier given water freezes at 0 and boils at 100
		int light_level;//minimum is 0
	};
	void setMap();
	static const int rows = 26;		//y
	static const int columns = 47;	//x
	static Tile map[rows][columns];
};

#endif