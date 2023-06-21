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
		string species_name; //also used as species relevant portion of filepath for png. ex: human, deer, tree
		int calories; //move to organism struct later given organisms grow and therefore their calories should increase, species should contain a calorie range according to age/size/etc
		string reproduction_method = "";
		string subsistence_method[5];//gather, hunt_ambush, soil, filter, hunt_pack, etc
		string hydration_method = "";
		string mobility = "";
		float max_lifespan = -1; //measured in years
		bool needs_sleep = false;
		//string diet_type = ""; //decomposer, producer, vegetarian, omnivore, carnivore
		string diet[2];
		//string biome = "";
		//string composed_of = ""; //meat, plant, wood, bone
		//string species_physical_traits = "";//the physical variability of the species, for example humans vary in skin tone, dogs in fur coats, etc. This holds the names of traits that can vary.
	};

/*
//create constructors that allow setting various attributes at once according to types, ex: wolf is a mammal, therefore composed_of = "meat, bone" so initialize wolf as mammal by wolf=mammal(wolf) where mammal() takes wolf to set its composed_of value and returns updated wolf, then wolf = {.species{"wolf"}, .biome{"woodland"}};
//might make more sense to divide Species struct into more structs to reduce redundant data, such as simply having Species.kingdom="mammal" and Mammal.composed_of="meat, bone" rather than having various copies of composed_of by wolf=mammal(wolf)
Species wolf = {"wolf","carnivore","pack_hunting, persistance_hunting","woodland", "meat, bone"};
Species deer = {"deer","vegetarian", "grazer", "woodland", "meat, bone" };
Species grass = {"grass", "producer", "sunlight", "woodland", "plant"};
Species tree = {"tree", "producer", "sunlight", "woodland", "plant, wood"};
Species bacteria_decomposing = {"bacteria_decomposing", "decomposer", "corpse, waste", "woodland"}; //is a "species" because it completes the abiotic decomposition process, otherwise you get mummies such as in deserts. Might make more sense to just have this be an environmental process, though decomposers also include fungi, parasites, and certain bugs such as flies. Waste is nutrients returned to soil/water
Species human = {"human", "omnivore", "pack_hunting, persistance_hunting, ambush_hunting", "woodland", "meat, bone"}; //initially, a human is sort of like a more complex wolf
*/



	static const int number_of_species = 6;
	Species species[number_of_species] = {
	{0, "grass", 10, "asexual_spores",{},"","",0.6},
	{1, "tree"},
	{2, "berrybush", 40, "asexual_spores",{},"","",0.6}, //reproduction method is temporarily spores, should be seeds?
	{3, "deer", 100,"sexual_animal", {"gather"}, "find_water", "mobile", 2, true, {"grass"}},
	{4, "wolf" },
	{5, "human", 100,"sexual_animal", {"gather","hunt"}, "find_water", "mobile", 2, true, {"berrybush","deer"}} //initially, a human is sort of like a more complex wolf
	};


	struct Need {//35 needs total. Physiological: 10 needs. Safety: 4 needs. Social: 6 needs. Esteem: 2 needs. Cognitive: 4 needs. Aesthetics: 3 needs. 
		string need_name;
		int priority=1;
		int current_level=100;
		int change_rate=1; 
	//Needs_Physiological {//all needs start at 100% satisfaction, each species (and sometimes individual) has a different rate of decreasing and increasing each
		//[0]	 air = "";
		//[1]	 heat = ""; //maintain proper temperature hot/cold
		//[2]	 clothes = ""; //only applies to humans, might make more sense to merge with temperature as clothes is about enduring the environment
		//[3]	 hygiene = ""; //only applies to humans, maybe cats?
		//[4]	 light = ""; //especially important for plants
		//[5]	 water = "";
		//[6]	 urination = "";
		//[7]	 food = ""; //soil nutrients for plants
		//[8]	 excretion = "";
		//[9]	 shelter = ""; //applies only to animals that live in caves, nests, etc
		//[10]	 sleep = "";
	//Needs_Safety {
		//[11]	 health = ""; //rest to heal injuries, avoid sickness, avoid bad food/water
		//[12]	 personal_security = ""; //avoid danger, flee danger, fight danger    this comes after physiological such that an individual might risk danger in order to obtain food/water
		//[13]	 emotional_security = ""; //stress, sadness, etc    animals may be exempt from this other than maybe pets
		//[14]	 financial_security = ""; //humans only, may make more sense to merge with other needs given that money itself isn't a need but what it gets access to is.
	//Needs_Social {
		//[15]	 family = ""; //protecting one's children and mate
		//[16]	 friendship = ""; //can include pack/herd behavior
		//[17]	 intimacy = ""; //reproduction
		//[18]	 trust = "";
		//[19]	 acceptance = "";
		//[20]	 affection = "";
	//Needs_Esteem {
		//[21]	 social_status = ""; //animals compete in social hierarchy
		// 
		// 
// All below are primarily or exclusively human needs and therefore should take lower priority in implementation and may even make sense to move to the people file.
		// 
		//[22]	 self_confidence = "";
	//Needs_Cognitive {
		//[23]	 creativity = "";
		//[24]	 foresight = "";
		//[25]	 curiosity = ""; //only one that may apply to animals
		//[26]	 meaning = "";
	//should all maslow needs be in this Biology file or should human specific ones be separated into the People file?
	//Needs_Aesthetics { //applies mainly to humans, maybe some animals that nest or do mating rituals but that may fit more under a social need, I don't know. 
		//[27]	 natural_beauty = "";
		//[28]	 surrounding_beauty = "";
		//[29]	 personal_beauty = "";
	//Needs_Self_Actualization { //applies only to humans
		//[30]	 partner_acquisition = ""; //seems redundant with intimacy though maybe one is permanent while the other temporary?
		//[31]	 parenting = ""; //seems redundant with family
		//[32]	 talents = ""; //seems redundant with self confidence?
		//[33]	 pursuing_goals = ""; //unique human/personal goals I guess?
	//Needs_Transcendence { //applies only to humans
		//[34]	 transcendence //desire to feel part of something greater than the self or the material, includes spirituality/altruism/dedication to a cause/etc
		












	};
	static int id_iterator;
	struct Organism {
		int organism_id;
		int species_id;
		int x;
		int y;
		//int pos_z = -1; //of limited use, for birds, underwater, etc. 
		bool sex;
		//int weight = -1; //determines calories/material when dead and impact momentum/carryability when alive
		//string individual_physical_traits; //May be best implemented as an additional struct or array of strings that correspond to different variability. Corresponding to the species_physical_traits, holds the exact variation an individual has, such as the exact skin color, max height, hair color, etc.

		//these are never set when creating a new organism, should always start at default values
		bool can_move = true;
		bool awake = true; //true=awake, false=asleep
		bool alive = true;
		float age = 0;//measured in years
		string png_file_state="";//contains state portion of png file for organism. ex: sleep, dead. Default = ""		should be derived at render time from all attributes rather than kept as a state
		bool deleted = false; //used to track which organisms have been deleted so as not to erase from vector which can invalidate pointers.
		Need needs[35];
		int o_it[2][5] = {//external iterator for functions
			{0,0,0,0,0},//[0] move_to_new_search_space()
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
		vector <Organism*> r_organism;
	};

	int new_id(int species_id);
	//simple move function
	bool move_to(Organism* o, int x, int y);
	//handles if and when ann organism dies and deterioration of the corpse
	bool death(Organism* o);
	//create new organism, allows options for specific contexts
	void birth(Organism* mother, Organism* father);
	//general search function
	return_vars find(Organism* o, string target_type, string target, int search_radius);
	//sorts needs by priority, iterates over all needs attempting to fill them
	void satisfy_needs(Organism* o); //includes consume, sleep, and change_need_level functions
	//carry()						pick up or drop item
	//fight()						cause damage to another organism
	//all periodic changes such as need deterioration should be here as well as aging
	void periodic(Organism* o);
	//a listener that checks the organism"s state and immediate surroundings to respond to things like taking damage or the appearance of a threat
	void context(Organism* o);
	//returns organism
	Organism* get_by_id(int id);
	//gets corresponding species, used to avoid holding a copy per organism without using pointers
	Species get_species(int species_id);
	//check if out of bounds, true if yes, false if no
	bool out_of_bounds(int x, int y);
	void update(Organism* o);
	void update_all();
	void insert_o(Organism o);	//insert organism into radix tree
	bool move_to_new_search_space(Organism* o, int search_range);//problem with this function is that it's a random direction, needs a way to remember where it has already searched. Use Steering Behavior?

	//idle()
	
	//the goal is to have very few and very simple functions which can be combined to create more complex behavior without introducing new bugs





};


#endif



//comments from old biology.cpp

//need to include various methods: live birth, egg, asexual, spores, seeds, etc
//find food; includes: search for it, go to known location, request known location, etc
//acquire food; includes: grab it, kill it, buy it, ask for it, etc
//need to expand this to include searching for items as well, currently only searches for nearest one of species
//some animals can be gathered (swallowed alive or picked up)


//includes aging given it is akin to an unfillable need that reduces over time. Maybe it could even be implemented as a need, though that might be less efficient?
//o->age += 1 / 100; //for now to test, 1 year = 100 seconds (1:40 min:sec), so given humans have a liftime of 2 years, they'll die at 3:20 min

//ex: change_rate=0.5 && current_level=50 && amt=40 --> 50+=40*0.5		--> current_level=100 == amt=200 if change_rate=0.5



/* Need to add this.
struct Position { //expand this later into a vector, as in include direction and acceleration/velocity
		int x;
		int y;
	};//this is absolute position not render position
*/







