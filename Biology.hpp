#ifndef Biology_hpp
#define Biology_hpp
#include "Environment.hpp"
#include <string>
#include <iostream>
#include <vector>


using namespace std;


class Biology {

public:
	Biology();//default constructor
	Biology(Environment* env);
	~Biology();

	Environment* environment;//reference to game's environment

	struct Species {
		int preset_index = -1;
		string species_name="";
		const char* png_file="";  //this is kept in the species struct for now, but will need to be in the organism struct later to allow variability within the species
		int calories; //move to organism struct later given organisms grow and therefore their calories should increase, species should contain a calorie range according to age/size/etc
		string reproduction_method = "";
		string subsistence_method = "";
		string hydration_method = "";
		string mobility = "";
		float max_lifespan = -1; //measured in years
	};
	
	static const int number_of_species = 6;
	Species species_presets[number_of_species] = {//preset index order affects render order, therefore change grass to index 0, tree to 1, berrybush to 2, etc
	{0, "wolf" },
	{1, "deer", "pics/deer.png", },
	{2, "grass", "pics/grass.png"},
	{3, "tree", "pics/tree.png"},
	{4, "berrybush", "pics/berrybush.png", 40, "asexual_spores","","","",0.6}, //reproduction method is temporarily spores, should be seeds?
	{5, "human", "pics/man.png",100,"sexual_animal", "gather", "find_water", "mobile", 2}, //initially, a human is sort of like a more complex wolf
	};



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
	struct Needs_Safety {
		Need health; //rest to heal injuries, avoid sickness, avoid bad food/water
		Need personal_security; //avoid danger, flee danger, fight danger    this comes after physiological such that an individual might risk danger in order to obtain food/water
		Need emotional_security; //stress, sadness, etc    animals may be exempt from this other than maybe pets
		Need financial_security; //humans only, may make more sense to merge with other needs given that money itself isn't a need but what it gets access to is.
	};
	struct Needs_Social {
		Need family; //protecting one's children and mate
		Need friendship; //can include pack/herd behavior
		Need intimacy; //reproduction
		Need trust;
		Need acceptance;
		Need affection;
	};

	struct Position { //expand this later into a vector, as in include direction and acceleration/velocity
		int x;
		int y;
	};//this is absolute position not render position

	int id_iterator = 0;//for tracking next available id number, unsure if int is enough or if id's that have been freed should be resused.
	struct Organism {//needs an automatic increment for ID when creating a new one
		int id;
		Species species;//should this be a pointer or instead an int with the species_preset_index? Tried to change this to a pointer, for some unknown reason it failed to pass a valid pointer when creating a new ogranism
		Position position;
		bool sex; //true==male, false==female

		//these are never set when creating a new organism, should always start at default values
		float age = 0;//measured in years
		Needs_Physiological needs_physiological;
		Needs_Safety needs_safety;
		Needs_Social needs_social;
		//for functions that need an external iterator, convert this into a vector and pass references to each iterator instead of using an array
		int o_it[7][5] = {  {0,0,0,0,0}, //each row is for a separate function
							{0,0,0,0,0},
							{0,0,0,0,0},
							{0,0,0,0,0},
							{0,0,0,0,0},
							{0,0,0,0,0},
							{0,0,0,0,0}  };
	};
	vector<Organism> organisms[number_of_species]; //this holds all the organisms in the world including people. Each index of the array corresponds to preset index of that species, so this is an array of species each with a vector of organisms (What about corpses?)
	

	/*Utility Functions*/
	bool move_to(int id, Position p);//returns true when it reaches target position
	vector<Organism*> get_nearby_organisms(int id, int radius, string species);//gets all organisms within a search radius matching a given species, sorted by nearest organisms first. Later replace the species parameter with a more general condition parameter.
	vector<Position> get_nearby_terrain(int id, int radius, string terrain);//same as above but for terrain such as searching for water
	void delete_organism(int id);
	int new_id();
	bool move_to_new_search_space(int id, int search_range);
	void idle(int id);
	void check_death(int id);//currently only deletes the organism, should instead replace with relevant corpse (corpse is an item?) which then deteriorates into nothing releasing nutrients into soil/water
	Organism* get_by_id(int id); //currently only used at start of update function, used because pointer would sometimes become invalid when passed to the update function, this is a workaround because I couldn't figure out the reason for the pointer becoming invalid

	/*Needs Satisfaction Utility Functions*/
	void change_need_level(Need* need, float change_amt); //increase or decrease the need level of an organism, ex: decrease food need satisfaction (aka increase hunger)
	void periodic_need_deterioration(int id);
	void consume(int id, int food_id);//o gains the calories in food and destroys food instance
	Position find_empty_tile(int id, int search_range);//return location without any organism present, used for asexual_spores reproduction method

	/*Needs Satisfaction Main Functions*/
	bool satisfy_need_water(int id);
	bool satisfy_need_food(int id);//attempts to satisfy food need, currently default satisfaction is current_level=100
	bool satisfy_need_intimacy(int id);

	/*Biology Main Functions*/
	void update(int id);//general update function that handles other functions
	void update_all();//calls update on every organism
};
#endif