//all pseudo_X.cpp files are simply some pseudocode to plan/brainstorm how the code will be structured/work.
#include <string>
#include <iostream>
using namespace std;


struct Species{ //these are static
	string species_name = "";
	string diet_type = ""; //decomposer, producer, vegetarian, omnivore, carnivore
	string subsistence_method = "";
	string biome = "";
	string composed_of = ""; //meat, plant, wood, bone
	string species_physical_traits = "";//the physical variability of the species, for example humans vary in skin tone, dogs in fur coats, etc. This holds the names of traits that can vary.
};

struct Organism { //these are instances of each species, aka individuals
	string organism_id = ""; //individual's id
	string species = ""; //either the name or a reference to the relevant species struct
	string sex = "";
	string alive_dead = "";
	int age = -1;
	int weight = -1; //determines calories/material when dead
	int pos_x = -1;
	int pos_y = -1;
	int pos_z = -1; //of limited use, for birds, underwater, etc. 
	string individual_physical_traits; //corresponding to the species_physical_traits, holds the exact variation an individual has, such as the exact skin color, max height, hair color, etc.
};

struct Needs_Physiological {
	string air = "";
	string heat = ""; //maintain proper temperature hot/cold
	string clothes = ""; //only applies to humans, might make more sense to merge with temperature as clothes is about enduring the environment
	string hygiene = ""; //only applies to humans, maybe cats?
	string light = ""; //especially important for plants
	string water = "";
	string urination = "";
	string food = ""; //soil nutrients for plants
	string excretion = "";
	string shelter = ""; //applies only to animals that live in caves, nests, etc
	string sleep = "";
};

struct Needs_Safety {
	string health = ""; //rest to heal injuries, avoid sickness, avoid bad food/water
	string personal_security = ""; //avoid danger, flee danger, fight danger    this comes after physiological such that an individual might risk danger in order to obtain food/water
	string emotional_security = ""; //stress, sadness, etc    animals may be exempt from this other than maybe pets
	string financial_security = ""; //humans only, may make more sense to merge with other needs given that money itself isn't a need but what it gets access to is.
};

struct Needs_Social {
	string family = ""; //protecting one's children and mate
	string friendship = ""; //can include pack/herd behavior
	string intimacy = ""; //reproduction
	string trust = "";
	string acceptance = "";
	string affection = "";
};

struct Needs_Esteem {
	string social_status = ""; //animals compete in social hierarchy
	string self_confidence = "";
};

struct Needs_Cognitive {
	string creativity = "";
	string foresight = "";
	string curiosity = ""; //only one that may apply to animals
	string meaning = "";
};

//should all maslow needs be in this Biology file or should human specific ones be separated into the People file?
struct Needs_Aesthetics { //applies only to humans
	string natural_beauty = "";
	string surrounding_beauty = "";
	string personal_beauty = "";
};

struct Needs_Self_Actualization { //applies only to humans
	string partner_acquisition = ""; //seems redundant with intimacy though maybe one is permanent while the other temporary?
	string parenting = ""; //seems redundant with family
	string talents = ""; //seems redundant with self confidence?
	string pursuing_goals = ""; //unique human/personal goals I guess?
};

struct Needs_Transcendence { //applies only to humans
	string transcendence = ""; //desire to feel part of something greater than the self or the material, includes spirituality/altruism/dedication to a cause/etc
};

//create constructors that allow setting various attributes at once according to types, ex: wolf is a mammal, therefore composed_of = "meat, bone" so initialize wolf as mammal by wolf=mammal(wolf) where mammal() takes wolf to set its composed_of value and returns updated wolf, then wolf = {.species{"wolf"}, .biome{"woodland"}};
//might make more sense to divide Species struct into more structs to reduce redundant data, such as simply having Species.kingdom="mammal" and Mammal.composed_of="meat, bone" rather than having various copies of composed_of by wolf=mammal(wolf)

Species wolf = {"wolf","carnivore","pack_hunting, persistance_hunting","woodland", "meat, bone"};
Species deer = {"deer","vegetarian", "grazer", "woodland", "meat, bone" };
Species grass = {"grass", "producer", "sunlight", "woodland", "plant"};
Species tree = {"tree", "producer", "sunlight", "woodland", "plant, wood"};
Species bacteria_decomposing = {"bacteria_decomposing", "decomposer", "corpse, waste", "woodland"}; //is a "species" because it completes the abiotic decomposition process, otherwise you get mummies such as in deserts. Might make more sense to just have this be an environmental process, though decomposers also include fungi, parasites, and certain bugs such as flies. Waste is nutrients returned to soil/water
Species human = {"human", "omnivore", "pack_hunting, persistance_hunting, ambush_hunting", "woodland", "meat, bone"}; //initially, a human is sort of like a more complex wolf


