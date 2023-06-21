#include "Biology.hpp"

using namespace std; 

vector<Biology::Organism> Biology::organisms;
Biology::radix Biology::o_root;
int Biology::id_iterator; 

Biology::Biology() {}
//Biology()						init
Biology::Biology(int a) {
	organisms.reserve(5000);//reserve space for 5,000 organisms
//whenever the vector resizes or adjusts it will invalidate all pointers to its elements, therefore all organisms will need to be 
//reinserted into the radix tree as if for the first time. To avoid this either use arrays instead of vectors or set vector to a minimum size and 
//throw a custom error message if vector exceeds this size so as to later implement a reset of all pointers when vector grows past limit.

/*
* instead of storing a pointer in the hash-table, you can store index of the element in your vector
*/

	id_iterator = 0;
	Organism new_o;
	new_o = {new_id(5),5,0,0}; //place 1 human
	insert_o(new_o);

	//instantiate organisms
	
	for (int i = 0; i < 20; i++) {//generates about 800 grass tiles
		for (int j = 0; j < 40; j++) {
			new_o = { new_id(0), 0, j, i };//grass		grass might make more sense to not update on every global update but instead only a portion does at a time. Another approach to increase efficiency would be to try to conceptualize grass as a single organism and only track its internal and external edges/holes. Or maybe create a fixed number of grass entities (object and pointer) for every state it could be in and use those for various tiles, switching between states as a tile is affected by external factors.
			insert_o(new_o);
		}
	}
	for(int i=0;i<15;i++){
		int new_x = rand() % Environment::columns;
		int new_y = rand() % Environment::rows;
		new_o = { new_id(1), 1, new_x, new_y };//tree
		insert_o(new_o);
	}
	for(int i=0;i<30;i++){
		int new_x = rand() % Environment::columns;
		int new_y = rand() % Environment::rows;
		new_o = { new_id(2), 2, new_x, new_y };//berrybush
		insert_o(new_o);
	}
	for(int i=0;i<4;i++){
		int new_x = rand() % Environment::columns;
		int new_y = rand() % Environment::rows;
		new_o = { new_id(3), 3, new_x, new_y, (bool)(i % 2)};//ensures a 50/50 sex ratio //deer
		insert_o(new_o);
	}
	for (int i = 0;i < 4;i++) {
		int new_x = rand() % Environment::columns;
		int new_y = rand() % Environment::rows;
		new_o = { new_id(5), 3, new_x, new_y, (bool)(i % 2)};//ensures a 50/50 sex ratio //human
		insert_o(new_o);
	}
	
}
//done
int Biology::new_id(int species_id) {//creates new id for new organism, id can encode further info such as species id, etc. Given organisms are sorted by id through radix sort/search, it speeds up access time
	int id = id_iterator;
	id_iterator++;
	//set first digit from right as species id (this means it's temp limited to only 10 species)
	id *= 10;
	id += species_id;
	return id;
}
//done
void Biology::insert_o(Organism organism) {
	organisms.push_back(organism);
	if (organisms.size() >= 1000) { 
		cout << "error: vector reserved size exceeded, all pointers will be invalidated, need to implement a full reinsertion of vector into tree and reserving of a larger vector size" << endl; 
		return;
	}
	Organism* o = &organisms.back();
	radix* it = &o_root;
	int digits = 0;
	int tmp_id = o->organism_id;
	while (tmp_id) {
		tmp_id /= 10;
		digits++;
	}
	int num = o->organism_id;
	for (int i = 1; i <= digits; i++) {
		int d = num % (10);
		num /= 10;
		switch (d)
		{
		case 0:
			if (it->_0 == nullptr) {it->_0 = new radix();}
			it = it->_0;
			break;
		case 1:
			if (it->_1 == nullptr) { it->_1 = new radix(); }
			it = it->_1;
			break;
		case 2:
			if (it->_2 == nullptr) { it->_2 = new radix(); }
			it = it->_2;
			break;
		case 3:
			if (it->_3 == nullptr) { it->_3 = new radix(); }
			it = it->_3;
			break;
		case 4:
			if (it->_4 == nullptr) { it->_4 = new radix(); }
			it = it->_4;
			break;
		case 5:
			if (it->_5 == nullptr) { it->_5 = new radix(); }
			it = it->_5;
			break;
		case 6:
			if (it->_6 == nullptr) { it->_6 = new radix(); }
			it = it->_6;
			break;
		case 7:
			if (it->_7 == nullptr) { it->_7 = new radix(); }
			it = it->_7;
			break;
		case 8:
			if (it->_8 == nullptr) { it->_8 = new radix(); }
			it = it->_8;
			break;
		case 9:
			if (it->_9 == nullptr) { it->_9 = new radix(); }
			it = it->_9;
			break;
		default:
			break;
		}
	}

	if(it->o==nullptr){//if first time inserting this id, tie it to its tile
		Environment::map[o->y][o->x].organism_id.push_back(o->organism_id);
	}
	cout << o->organism_id << " inserted at " << o->x << ", " << o->y << endl;
	it->o = o;
}
//done						simple move function
bool Biology::move_to(Organism* o, int x, int y) {//return true if destination reached, else false
	//check if destination is out of bounds
	if (x > Environment::columns) { x = Environment::columns; }
	else if (x < 0) { x = 0; }
	if (y > Environment::rows) { y = Environment::rows; }
	else if (y < 0) { y = 0; }
	//untie from tile
	Environment::Tile* t = &Environment::map[o->y][o->x];
	for (int i = 0; i < t->organism_id.size(); i++) {
		if (t->organism_id[i] == o->organism_id) {
			t->organism_id.erase(t->organism_id.begin() + i);
			break;
		}
	}
	//change organism's location
	int old_x = o->x;
	int old_y = o->y;
	if (x > o->x) { o->x++; }
	else if (x < o->x) { o->x--; }
	if (y > o->y) { o->y++; }
	else if (y < o->y) { o->y--; }
	//tie to new tile
	Environment::map[o->y][o->x].organism_id.push_back(o->organism_id);
	
	//return
	if (x == o->x && y == o->y) {
		return true;
	}
	else {
		return false;
	}
}
//death()						handles if and when ann organism dies and deterioration of the corpse
bool Biology::death(Organism* o) {
	//if(o.alive==false){decompose corpse}
	//if(done_decomposing){delete organism object from radix tree}
	//ex: bool death_condition_1 = a == true || b == false;
	//ex: if(death_condition_1 || death_condition_2){o.alive==false;}
	return true;//if dead
}
//birth()						create new organism, allows options for specific contexts
void Biology::birth(Organism* mother, Organism* father) {

}
//out_of_bouds()	true if out of bounds, false if in bounds
bool Biology::out_of_bounds(int x, int y) {
	if (x > Environment::columns) { return true; }
	else if (x < 0) { return true; }
	if (y > Environment::rows) { return true; }
	else if (y < 0) { return true; }
	return false;
}
//find()						general search function
Biology::return_vars Biology::find(Organism* o, string target_type, string target, int search_radius) {//to find an empty tile (no organisms), just search "terrain" "all" to get all tiles in search space and then select the first tile that has an organism id vector size of 0 (or 1 and check if it's grass or not)
	bool found_target = false;
	return_vars r;
	//gets list of all tiles within search_radius, sorted by distance to search origin. Iterates in rings in an outward direction.
	vector<Environment::Tile> search_space;
	for (int tmp_radius = 0; tmp_radius <= search_radius; tmp_radius++) {
		int min_x = o->x - tmp_radius;
		int max_x = o->x + tmp_radius;
		int min_y = o->y - tmp_radius;
		int max_y = o->y + tmp_radius;
		for (int y = min_y; y < max_y; y++) {
			int x = tmp_radius;
			if (!out_of_bounds(x, y)) { search_space.push_back(Environment::map[y][x]); }
			x *= -1;
			if (!out_of_bounds(x, y)) { search_space.push_back(Environment::map[y][x]); }
		}
		for (int x = min_x + 1; x < max_x - 1; x++) {
			int y = tmp_radius;
			if (!out_of_bounds(x, y)) { search_space.push_back(Environment::map[y][x]); }
			y *= -1;
			if (!out_of_bounds(x, y)) { search_space.push_back(Environment::map[y][x]); }
		}
	}
	vector<Environment::Tile> found_t;
	vector<Organism*> found_o;
	for (int i = 0; i < search_space.size(); i++) {
		if (target_type == "terrain") {
			bool all = false;
			if (target == "all") { all = true; }
			if (all || search_space[i].terrain == target) {
				found_t.push_back(search_space[i]);
			}
			if(found_t.size()!=0){
				found_target = true;
				r.r_bool.push_back(found_target);
				r.r_tile = found_t;
				return r;
			}
		}
		else if (target_type == "species") {
			bool all = false;
			if (target == "all") { all = true; }
			for (int j = 0; j < search_space[i].organism_id.size(); j++) {
				Organism* tmp_o = get_by_id(search_space[i].organism_id[j]);
				if (all || get_species(tmp_o->organism_id).species_name == target && o->organism_id!=tmp_o->organism_id) {
					found_o.push_back(tmp_o);
				}
			}
			if (found_o.size() != 0) {
				found_target = true;
				r.r_bool.push_back(found_target);
				r.r_organism = found_o;
				return r;
			}
		}
	}
	r.r_bool.push_back(found_target);
	return r;
}

//need to add an external reset for this, so that when x is found, this function's iterators reset for next time
//utilizes o_it[0] row			problem with this function is that it's a random direction, needs a way to remember where it has already searched
bool Biology::move_to_new_search_space(Organism* o, int search_range) {//called after a search fails to find desired target, moves the organism outside its original search range.
	if (o->o_it[0][0] == 0) {//function initialization
		int rx = (rand() % (3)) - 1;// = -1 | 0 | 1		gets direction
		int ry = (rand() % (3)) - 1;
		if (rx == 0 && ry == 0) { rx++; }//prevents (rx & ry)==0
		o->o_it[0][1] = o->x + (rx * search_range);//move out of the original search range in chosen direction
		o->o_it[0][2] = o->y + (ry * search_range);
		o->o_it[0][0] = 1; //marks function as initialized
	}
	bool reached = move_to(o, o->o_it[0][1], o->o_it[0][2] );//return true when reached
	if (reached) {//once out of range, reset function variables
		o->o_it[0][0] = 0;
		o->o_it[0][1] = 0;
		o->o_it[0][2] = 0;
	}
	return reached;
}


//satisfy_needs()				sorts needs by priority, iterates over all needs attempting to fill them
void Biology::satisfy_needs(Organism* o) {
	int top_priority = 0;
	int need_index=0;
	for (int i = 0; i < sizeof(o->needs) / sizeof(Need); i++) {
		if (o->needs[i].priority > top_priority) { top_priority = o->needs[i].priority; need_index = i; }
	}
	//get need name
	string need = o->needs[need_index].need_name;
	
//	if (need == "") {
// 	   //find path/target to satisfy need
//	   //choose method according to target/path
// }
//	if (need == "") {}
//	if (need == "") {}





//Needs to implement right now			Think first in terms of conditional statements, then in functions to be able to check those conditionals.
	//Needs_Physiological {//all needs start at 100% satisfaction, each species (and sometimes individual) has a different rate of decreasing and increasing each
		//[0]	 air = "";
		// if submerged in water, air need_level falls and death occurs when it reaches 0, need_level rises once out of water again. Inverse for fish.
		// if air has smoke/poison air need_level falls until death at 0 same as submerged underwater. Poison (maybe smoke?) has added damage effects
		// Requires a way to check if submerged/buried and whether tile has airborne smoke/poison
		// Satisfy need by moving to nearest source of clean air
		// Low need causes lung damage? Reduces ability to move/think.
	if (need == "air") {
		//function
	}
		//[1]	 heat = ""; //maintain proper temperature hot/cold
		// if tile or item carried is too hot or too cold, adjust need level according to temperature and take damage at a certain level. 
		// Unlike other needs, this one is good at level 50, 100 is deadly hot and 0 is deadly cold with corresponding damage types (frozen solid, frostbite, hypothermia, heat stroke, burning, charred, incinerated) and affects ability to move
		// Satisfy need by moving towards better temperature tiles or dropping hot/cold item. 
		// Need to implement a temperature system in the environment/items influenced by air/sun/shade/etc.
	if (need == "heat") {
		//function
	}

		//[2]	 clothes = ""; //only applies to humans (and hermit crabs), might make more sense to merge with temperature as clothes is about enduring the environment
		// Implement this later, requires ability to craft clothes and ingredients to do so, etc. 
		// 
		//
		//[3]	 hygiene = ""; //only applies to humans, maybe cats?
		// Dirtiness reduces need level and causes morale/discomfort hits (how is this measured and stored?) and increased chances of disease/infection
		// Need to implement sources and types of dirtiness (dust/dirt/mud/sweat/blood/etc)
		// 
		// 
		//[4]	 light = ""; //especially important for plants
		// Need to implement a light (and therefore also shade) system in the environment for tiles, have organisms move to tiles with more light. Light level adjusts need level.
		// If need level is 0 then the organism is blind and moves blindly until it gets to better lighting. Low light causes mood hit (how to measure/store this?)
		// A plant with lower light level grows slower and if the level is too low it begins to take damage (wilt) and die
	if (need == "light") {
		//function
	}
		// 
		//[5]	 water = "";
		// Need to implement water system later on as well as containers for water like pots/cups/waterskins. 
		// Need level deteriorates over time, with deterioration rate influenced by heat
		// Satisfy need by finding nearest water source and consuming it
		// Plants get their water need satisfied by growing out roots into surrounding tiles in preference towards tiles that contain more water. Dirt tiles can hold water.
		// These tiles get their water level replenished by either surrounding water over time or rain. 
	if (need == "water") {
		//function
	}
		// 
		//[6]	 urination = "";
		// Need is inversely proportional to water need, as in if hydrated need to piss, else no. If need reaches 0, piss. Need deteriorates periodically. 
		// Satisfied by taking a piss which resets need level to 100. Pissing adds piss, a type of contaminated water, to tile.
	if (need == "urination") {
		//function
	}
		// 
		//[7]	 food = ""; //soil nutrients for plants
		// Need level deteriorates over time, satisfy need by consuming food that matches organism's diet, obtain food through corresponding subsistence methods
		// Food is either an organism or an item, contains calories which fill up according to need level change rate, 
		// If need level reaches 0, die of starvation. Later add a calorie in / calorie out system to control fat/skinny levels. Then a nutrition system for malnourishment.
		// Plants get their food need satisfied the same way they get water, by growing roots towards dirt tiles with higher soil fertility/nutrition levels. These tiles level are replenished by decomposing corpses and decomposing excrement.
	if (need == "food") {
		//function
	}
		// 
		//[8]	 excretion = "";
		// Need is inversly proportional to food need, so if food need level is high, excretion level deteriorates over time. If level hits 0, take a shit. This creates a shit item in the tile which decomposes over time until it dissappears, increasing soil nutrition as it does. 
		// While the shit item is still present, it has a chance to infect nearby organisms with a disease. If it is contact with water either as a water tile or held in the soil, the water becomes contaminated water.
	if (need == "excretion") {
		//function
	}
		// 
		//[9]	 shelter = ""; //applies only to animals that live in caves, nests, etc
		// Find shelter, if no shelter found, build shelter. Use shelter to sleep at night, shade, lay eggs, stockpile food/materials, idle, etc. 
		// Need to implement both a natural shelter system (caves/holes) and the ability to build shelters (dig hole, build nest, build walls and roof, etc)
		// Need is 0 when sleeping without shelter, 100 if sleeping with shelter. Later on add a quality system for shelter. Shelter deteriorates according to type/material/quality/etc so it must be constantly repaired. 
		// Need to implement a system of territoriality, where an organism designates certain tiles as theirs, other's or unclaimed and either shares or competes with others for those tiles. Ownership/claims over tiles should be a spectrum such that certain things increase or decrease the strength ofthe claim/ownership such as marking territory, how often territory is walked through or seen, fights over it, etc.
		// Shelter that has the strongest ownership to the organism is preferred over those that have less or no ownership to the organism, and unclaimed is prefferred to claimed by another. Balanced by distance such that if the organism cannot reach their home before sleep reaches 0, they choose the best nearest option.
	if (need == "shelter") {
		//function
	}
		// 
		//[10]	 sleep = "";
		// Need level deteriorates over time. If it reaches 0 organism falls asleep then and there. Affected by exhaustion level (need to implement). If it falls below a certain level, organism actively seeks a place to sleep.
		// Need satisfied by sleeping, sleep environment affects rate of satisfaction (light/sound/danger/getting hit/rain/wind/hard or rough sleep spot/etc). 
		// Wake up when need level reaches 100 or if another need such as food/water/heat/etc deteriorates to a certain point so that it takes priority over sleep.
		// Sleep need level affects movement/thinking
	if (need == "sleep") {
		//function
	}
		// 
	//Needs_Safety {
		//[11]	 health = ""; //rest to heal injuries, avoid sickness, avoid bad food/water
		// Need to implement health system that includes injury/damage and disease/contamination
		// Damage and being contaminated lowers health need level. If health need level reaches 0, organism dies. Level affects movement/thinking. 
		// Satisfy need by resting. 
	if (need == "health") {
		//function
	}
		// 
		//[12]	 personal_security = ""; //avoid danger, flee danger, fight danger    this comes after physiological such that an individual might risk danger in order to obtain food/water
		// Items/tiles/organisms have a calculated threat level to an individual organism. If the threat is static such as contaminated food/tile on fire, response is to simply not consume or touch it.
		// If the threat is an organism then engage in fight/flight/hide/submit behavior according to the situation.
	if (need == "personal_security") {
		//function
	}
		// 
		//[13]	 emotional_security = ""; //stress, sadness, etc    animals may be exempt from this other than maybe pets
		// Unsure how to implement this, this may be redundant with other needs or at least heavily derived from them.
		// 
		// 
		//[14]	 financial_security = ""; //humans only, may make more sense to merge with other needs given that money itself isn't a need but what it gets access to is.
		// This if implemented will be done far, far later when monetized economies are implemented. For a long time economies will be non-monetary, instead either gift/bartering/subsistence economies. 
	//Needs_Social {
		//[15]	 family = ""; //protecting one's children and mate
		// Depending on context, prioritize helping family, especially one's children, fulfill their needs before one's own.
		// 
		//[16]	 friendship = ""; //can include pack/herd behavior		might be redundant with family, such that family and friends are points on a spectrum of caring for another
		//[17]	 intimacy = ""; //reproduction
		// If asexual, reproduce if empty tile nearby. (seeds/spores/division)
		// If sexual, depends on type (monogamous, polygamous exclusive (alpha male), polygamous non exclusive (some fish)) relation types might fit more in family than pure reproduction.
		// Find available/preferred mate. If necessary attract mate (mating ritual). Mate. Female is now either pregnant or laid eggs which have been or become fertilized. 
		// New organism is born with some characteristics of both parents. 
	if (need == "intimacy") {
		//function
	}
		// 
		//[18]	 trust = "";		implement later
		//[19]	 acceptance = "";		implement later
		//[20]	 affection = "";		implement later
	//Needs_Esteem {
		//[21]	 social_status = ""; //animals compete in social hierarchy (pack leader/male competition/etc)		implement later







}
//carry()						pick up or drop item
//fight()						cause damage to another organism
//periodic()					all periodic changes such as need deterioration should be here
void Biology::periodic(Organism* o) {

}
//context()						a listener that checks the organism"s state and immediate surroundings to respond to things like taking damage or the appearance of a threat
void Biology::context(Organism* o) {

}
//get_by_id()					returns organism
Biology::Organism* Biology::get_by_id(int id) {
	radix* it = &o_root;
	int digits = 0;
	int tmp_id = id;
	while (tmp_id) {
		tmp_id /= 10;
		digits++;
	}
	int num = id;
	for (int i = 1; i <= digits; i++) {
		int d = num % (10);
		num /= 10;
		switch (d)
		{
		case 0:
			it = it->_0;
			break;
		case 1:
			it = it->_1;
			break;
		case 2:
			it = it->_2;
			break;
		case 3:
			it = it->_3;
			break;
		case 4:
			it = it->_4;
			break;
		case 5:
			it = it->_5;
			break;
		case 6:
			it = it->_6;
			break;
		case 7:
			it = it->_7;
			break;
		case 8:
			it = it->_8;
			break;
		case 9:
			it = it->_9;
			break;
		default:
			break;
		}
		if (it == nullptr) {
			cout << "id not found" << endl; //need to include an error exception or some way to catch because I can't use a null return
		}
	}

	if (it->o == nullptr) {
		cout << "id not found" << endl;//same as other not found above
	}
	return it->o;
}

//get_species()					gets corresponding species, used to avoid holding a copy per organism without using pointers
Biology::Species Biology::get_species(int species_id) {
	for (int i = 0; i < number_of_species; i++) {
		if (species_id == species[i].species_id) {
			return species[i];
		}
	}
}




void Biology::update(Organism* o) {

}
void Biology::update_all() {
	Organism* o = get_by_id(5);
	return_vars r = find(o, "terrain", "water", 10);
	if (r.r_bool[0] == true) {
		move_to(o, r.r_tile[0].x, r.r_tile[0].y); 
	}
	else {
		//if not found within search space, move to new search space
		move_to_new_search_space(o, 10);
	}
}



