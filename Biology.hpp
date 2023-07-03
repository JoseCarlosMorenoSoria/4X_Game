#ifndef Biology_hpp
#define Biology_hpp
#include "Environment.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

//it's better to have fixed structures rather than looping to find x, for example when getting species by id, it'd be better if the id was an index of the array
// likewise maybe lookup tables might be more efficient
//better than that is simply encoding info in smaller data packets such as an int/bit sequence

using namespace std;

class Biology {
public:
	Biology();//empty default constructor to prevent unintended initialization
	Biology(int a);

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
	struct Species {//later on, restructure Species as sets of ranges rather than hard values so as to allow individual variability in things such as health pool, damage strength, skin/fur colors, etc.
		int species_id;
		string species_name; //also used as species relevant portion of filepath for png. ex: human, deer, tree
		bool is_plant; //if plant, then true, else false		covers: is immobile, doesn't sleep, etc
		int calories; //move to organism struct later given organisms grow and therefore their calories should increase, species should contain a calorie range according to age/size/etc
		string reproduction_method = "";
		vector<string> subsistence_method;//gather, hunt_ambush, soil, filter, hunt_pack, tracking_hunter, etc
		float max_lifespan = -1; //measured in years
		//string diet_type = ""; //decomposer, producer, vegetarian, omnivore, carnivore
		vector<string> diet;
		//string biome = "";
		//string composed_of = ""; //meat, plant, wood, bone
		//string species_physical_traits = "";//the physical variability of the species, for example humans vary in skin tone, dogs in fur coats, etc. This holds the names of traits that can vary.
		string breathes; //air, water, amphibious
		int ideal_light_level;//nocturnal animals prefer darkness
		float ideal_temperature;
		int damage;//amount of damage species can deal. 
		vector<string> instinctual_threats;//innate/instinctually known threats (species)
	};

//these are the variables to set per species, placed here for ease of reference
//{species_id; species_name; is_plant; calories; reproduction_method; subsistence_method; max_lifespan; diet; breathes; ideal_light_level; ideal_temperature; damage;}

//
//to do now: 
// Implement shelter, sleep, reproduction and aging. 
//then test
//

	static const int number_of_species = 6;//grass eaten by deer eaten by wolf and human	berrybush eaten by human		tree cut down for wood by human
	Species species[number_of_species] = {
	{0, "grass", true, 10, "asexual_spores",{"roots"},0.6, {}, "air", 50, 50,0},
	{1, "tree"},
	{2, "berrybush", true, 40, "asexual_spores",{"roots"},0.6, {}, "air", 50, 50,0}, //reproduction method is temporarily spores, should be seeds?
	{3, "deer", false, 100,"sexual_animal", {"gather"}, 2, {"grass"}, "air", 50, 50,0,{"wolf"}},
	{4, "wolf", false, 100,"sexual_animal", {"gather","hunt"}, 2, {"berrybush","deer"}, "air", 50, 50,34},
	{5, "human", false, 100,"sexual_animal", {"gather","hunt"}, 2, {"berrybush","deer"}, "air", 50, 50,34} //initially, a human is sort of like a more complex wolf
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
		//int species_id;
		Species* species;
		int x;
		int y;
		//int pos_z = -1; //of limited use, for birds, underwater, etc. 
		bool sex;
		//int weight = -1; //determines calories/material when dead and impact momentum/carryability when alive
		//string individual_physical_traits; //May be best implemented as an additional struct or array of strings that correspond to different variability. Corresponding to the species_physical_traits, holds the exact variation an individual has, such as the exact skin color, max height, hair color, etc.

		//strength
		//speed
		//awareness range (for search radius, later replace with a sight cone and hearing radius/cones)

		//these are never set when creating a new organism, should always start at default values
		vector<string> learned_threats;//stores known threats (species), learned by seeing another organism of the same species be attacked. 
		float temperature = 50;//measured in Celsius because it makes it easier given water freezes at 0 and boils at 100. Need to limit the number of decimal places.
		bool too_dark_bright = false;
		bool can_move = true;
		bool awake = true; //true=awake, false=asleep
		bool alive = true;
		//float age = 0;//measured in years		need to implement
		string png_file_state="";//contains state portion of png file for organism. ex: sleep, dead. Default = ""		should be derived at render time from all attributes rather than kept as a state
		bool deleted = false; //used to track which organisms have been deleted so as not to erase from vector which can invalidate pointers.
		Need needs[35];
		int o_it[6][5] = {//external iterator for functions		ahould this be a single reusable iterator??
			{0,0,0,0,0},//[0] move_to_new_search_space()
			{0,0,0,0,0},//[1] satisfy_need : urination function
			{0,0,0,0,0},//[2] death()
			{0,0,0,0,0},//[3] satisfy_need : excretion function
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
		vector <Organism*> r_organism;
	};

	int new_id(int species_id);
	bool move_to(Organism* o, int x, int y);//simple move function
	void death(Organism* o);//handles if and when an organism dies and deterioration of the corpse
	void birth(Organism* mother, Organism* father, int x, int y);//create new organism at sepcific location, allows options for specific contexts
	return_vars find(Organism* o, string target_type, vector<string> targets, int search_radius);//general search function
	bool find(vector<string> v, string s);//a wrapper for the std::find() function to make it cleaner. Only implemented for strings for now.	
	//carry()						pick up or drop item
	//fight()						cause damage to another organism
	void periodic(Organism* o);//all periodic changes such as need deterioration should be here as well as aging
	void context(Organism* o);//a listener that checks the organism"s state and immediate surroundings to respond to things like taking damage or the appearance of a threat
	Organism* get_by_id(int id);//returns organism
	bool out_of_bounds(int x, int y);//check if out of bounds, true if yes, false if no
	void update(Organism* o);
	void update_all();
	void insert_o(Organism o);	//insert organism into radix tree
	bool move_to_new_search_space(Organism* o, int search_range);//problem with this function is that it's a random direction, needs a way to remember where it has already searched. Use Steering Behavior?
	void change_need_level(Organism* o, int need, float amt);//needed to bound need level within 0 and 100
	//idle()
	void attack(Organism* o, Organism* target, string attack_method);//should this be replaced with a general combat function for both attack and defense? Currently no defense function implemented.
	void delete_o(Organism* o);//removes organism from radix tree, also need to implement a function to remove deleted objects from organisms vector and then reinsert into tree and reset all pointers
	int distance(int x1, int y1, int x2, int y2);//gets distance between 2 tiles on map.

	//these 3 functions operate as: sort needs by priority*utility, find path to satisfy, execute path
	string calculate_top_need(Organism* o);//returns name of most urgent*low cost need to execute next.
	int satisfy_needs(Organism* o, int search_radius, int need, bool execute); //sorts needs by priority, iterates over all needs attempting to fill them  //if execute==false, returns distance to target cost (int) if path to need satisfaction found, returns search_radius+1 else (therefore must move_to_new_search_space())
	
	//add consume, sleep




};//the goal is to have very few and very simple functions which can be combined to create more complex behavior without introducing new bugs


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



//swimming is an action limited by stamina / exhaustion, need to implement



	//implement these later
		//[13]	 emotional_security = ""; //stress, sadness, etc    animals may be exempt from this other than maybe pets
		// Unsure how to implement this, this may be redundant with other needs or at least heavily derived from them.
		// 
		// 
		//[14]	 financial_security = ""; //humans only, may make more sense to merge with other needs given that money itself isn't a need but what it gets access to is.
		// This if implemented will be done far, far later when monetized economies are implemented. For a long time economies will be non-monetary, instead either gift/bartering/subsistence economies. 
		//[15]	 family = ""; //protecting one's children and mate
		// Depending on context, prioritize helping family, especially one's children, fulfill their needs before one's own.
		// 
		//[16]	 friendship = ""; //can include pack/herd behavior		might be redundant with family, such that family and friends are points on a spectrum of caring for another
	//[2]	 clothes = ""; //only applies to humans (and hermit crabs), might make more sense to merge with temperature as clothes is about enduring the environment
	// Implement this later, requires ability to craft clothes and ingredients to do so, etc. 
	//
	//[3]	 hygiene = ""; //only applies to humans, maybe cats?
	// Dirtiness reduces need level and causes morale/discomfort hits (how is this measured and stored?) and increased chances of disease/infection
	// Need to implement sources and types of dirtiness (dust/dirt/mud/sweat/blood/etc) 
		// 
		//[18]	 trust = "";		implement later
		//[19]	 acceptance = "";		implement later
		//[20]	 affection = "";		implement later
	//Needs_Esteem {
		//[21]	 social_status = ""; //animals compete in social hierarchy (pack leader/male competition/etc)		implement later