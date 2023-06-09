#ifndef Biology_hpp
#define Biology_hpp
#include <string>
#include <iostream>
#include <vector>

#include "Environment.hpp"//this might cause circular referencing and therefore some problems



using namespace std;

class Biology {

public:
	Biology();//default constructor
	Biology(Environment* env);
	~Biology();

	Environment* environment;//reference to game's environment

	struct Species {
		string species_name="";
		const char* png_file="";  //this is kept in the species struct for now, but will need to be in the organism struct later to allow variability within the species
		int calories; //move to organism struct later given organisms grow and therefore their calories should increase, species should contain a calorie range according to age/size/etc
	};

	Species wolf = { "wolf" };
	Species deer = { "deer", "pics/deer.png"};
	Species grass = { "grass", "pics/grass.png"};
	Species tree = { "tree", "pics/tree.png"};
	Species berrybush = { "berrybush", "pics/berrybush.png", 40 };
	Species human = { "human", "pics/man.png" }; //initially, a human is sort of like a more complex wolf


	struct Need {
		float current_level = 100;
		float change_rate = 1; //a change_rate of 1 means it takes 100 units to reach current_level=100 which is the max a need can be filled.
	};

	//might make more sense to place these in an array rather than as separate variables.
	struct Needs_Physiological {//all needs start at 100% satisfaction, each species (and sometimes individual) has a different rate of decreasing and increasing each
		Need air;
		Need heat; //maintain proper temperature hot/cold
		Need clothes; //only applies to humans, might make more sense to merge with temperature as clothes is about enduring the environment
		Need hygiene; //only applies to humans, maybe cats?
		Need light; //especially important for plants
		Need water;
		Need urination;
		Need food; //soil nutrients for plants
		Need excretion;
		Need shelter; //applies only to animals that live in caves, nests, etc
		Need sleep;
	};

	struct Position { //expand this later into a vector, as in include direction and acceleration/velocity
		int x;
		int y;
	};//this is absolute position not render position

	int id_iterator = 0;//for tracking next available id number, unsure if int is enough or if id's that have been freed should be resused.
	struct Organism {//needs an automatic increment for ID when creating a new one
		int id;
		Species species; //maybe make this a pointer so that each organism does not have a separate instance copy of species
		Position position;
		Needs_Physiological needs_physiological;
		//for functions that need an external iterator, convert this into a vector and pass references to each iterator instead of using an array
		int o_it[7][5] = {  {0,0,0,0,0}, //each row is for a separate function
							{0,0,0,0,0},
							{0,0,0,0,0},
							{0,0,0,0,0},
							{0,0,0,0,0},
							{0,0,0,0,0},
							{0,0,0,0,0}  };
	};
	vector<Organism> organisms; //this holds all the organisms in the world including people and corpses.


	/*Utility Functions*/
	bool move_to(Organism* o, Position p);//returns true when it reaches target position
	Organism* search_for_species(Organism* o, string species);//returns nearest match, moves in a random direction if none found
	Position search_for_terrain(Organism* o, string terrain);//same as above but for terrain such as searching for water
	void delete_organism(Organism* o);
	int new_id();
	bool move_to_new_search_space(Organism* o);
	void idle(Organism* o);

	/*Needs Satisfaction Utility Functions*/
	void change_need_level(Need* need, float change_amt); //increase or decrease the need level of an organism, ex: decrease food need satisfaction (aka increase hunger)
	void periodic_need_deterioration(Organism* o);
	void consume(Organism* o, Organism* food);//o gains the calories in food and destroys food instance

	/*Needs Satisfaction Main Functions*/
	bool satisfy_need_water(Organism* o);
	bool satisfy_need_food(Organism* o);//attempts to satisfy food need, currently default satisfaction is current_level=100


	/*Biology Main Functions*/
	void update(Organism* o);//general update function that handles other functions
};
#endif