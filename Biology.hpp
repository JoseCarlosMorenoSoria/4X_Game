#ifndef Biology_hpp
#define Biology_hpp
#include "Environment.hpp"
#include <string>
#include <iostream>
#include <vector>

//it's possible that pointers now work correctly and should be used instead of id and pass by value. Will use id and pass by value for now but change later.

//it's better to have fixed structures rather than looping to fnd x, for example when getting species by id, it'd be better if the id was an index of the array
//better than that is simply encoding info in smaller data packets such as an int/bit sequence

using namespace std;

class Biology {
public:
	Biology();//empty default constructor to prevent unintended initialization
	Biology(int a);

	struct Species {
		int species_id;
		string species_name;
	};
	static const int number_of_species = 1;
	Species species[number_of_species] = { {1,"human"}};
	struct Need {
		string need_name;
		int priority=1;
		int current_level=100;
		int change_rate=1;
		//[0] 
		//[1] 
		//[2] 
		//[3] 
		//[4] 
	};
	static int id_iterator;
	struct Organism {
		int organism_id;
		int species_id;
		int x;
		int y;
		string png_file_state="";
		Need needs[25];
		int o_it[2][5] = {//external iterator for functions
			{0,0,0,0,0},
			{0,0,0,0,0}
		};
	};
	static vector<Organism> organisms;//never erase or rearrange objects here or else it will invalidate the pointers in the radix tree. Only erase when saving/quiting game and then immediately reinsert entire vector into the radix tree from the o_root.

	struct radix {
		Organism* o=nullptr; 
		radix* _0 = nullptr;//these 10 pointers could just be an array of pointers instead
		radix* _1 = nullptr;
		radix* _2 = nullptr;
		radix* _3 = nullptr;
		radix* _4 = nullptr;
		radix* _5 = nullptr;
		radix* _6 = nullptr;
		radix* _7 = nullptr;
		radix* _8 = nullptr;
		radix* _9 = nullptr;
	};

	static radix o_root;//radix sorted tree, sorts by id, points to objects in the organisms vector above.



	struct return_vars {//for when a function needs more than 1 return variable of different types.
		vector<string> r_string;
		vector<int> r_int;
		vector<bool> r_bool;
		vector <Environment::Tile> r_tile;
		vector <Organism> r_organism;
	};

	int new_id(int species_id);
	//move_to()						simple move function
	bool move_to(int id, int x, int y);
	//death()						handles if and when ann organism dies and deterioration of the corpse
	bool death(int id);
	//birth()						create new organism, allows options for specific contexts
	void birth(int mother_id, int father_id);
	//find()						general search function
	return_vars find(int id, string target_type, string target, int search_radius);
	//satisfy_needs()				sorts needs by priority, iterates over all needs attempting to fill them
	void satisfy_needs(int id);
	//carry()						pick up or drop item
	//fight()						cause damage to another organism
	//periodic()					all periodic changes such as need deterioration should be here
	void periodic(int id);
	//context()						a listener that checks the organism"s state and immediate surroundings to respond to things like taking damage or the appearance of a threat
	void context(int id);
	//get_by_id()					returns organism
	Organism get_by_id(int id);
	//get_species()					gets corresponding species, used to avoid holding a copy per organism without using pointers
	Species get_species(int species_id);
	//check if out of bounds, true if yes, false if no
	bool out_of_bounds(int x, int y);
	void update(int id);
	void update_all();
	void insert_o(Organism o);	//insert organism into radix tree	- updates an organism, used to avoid using pointers/references and only use values because they were causing undiagnosable problems.
	//the goal is to have very few and very simple functions which can be combined to create more complex behavior without introducing new bugs
	//work directly with objects, no references or pointers at all





};


#endif