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
		int light_level=50;//minimum is 0
		int water_level=0;//minimum is 0, max is 100 only if terrain is water, else is max 50. Only dirt can hold water. (?)
		int nutrient_level = 0;//for plants, created from decomposed organisms and shit. Need to figure out a way to control amount of usable nutrients/calories in an ecosystem. Use a calorie in/calorie out system that incorporates all actions, decomposition, and defecation (just as the water system should incorporate the urination system). Either create a stable system where total world organic life has a calorie cap, or an unstable one where calories leave the system and are created by plants so that the global calorie content varies over time.
	};
	void setMap();
	static const int rows = 26;		//y
	static const int columns = 47;	//x
	static Tile map[rows][columns];
	void dirt_water_spread();//periodically spreads water into and between dirt tiles from water sources including other dirt tile. Currently, the max distance a water source tile (full water tile) can spread through surrounding dirt tiles is 6 tiles, spreads by halfing each tile, so 100 (water tile) -> 50 -> 25 -> 12 -> 6 -> 3 -> 1
	void temperature_spread();//same as water spread but for temperature and all tiles, no heat sources yet implemented, nor shade, so this function doesn't do much yet.
	void update();
};

#endif