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
	new_o = {new_id(5),&species[5],0,0}; //place 1 human
	insert_o(new_o);

	//instantiate organisms
	
	for (int i = 0; i < 20; i++) {//generates about 800 grass tiles
		for (int j = 0; j < 40; j++) {
			new_o = { new_id(0), &species[0], j, i};//grass		grass might make more sense to not update on every global update but instead only a portion does at a time. Another approach to increase efficiency would be to try to conceptualize grass as a single organism and only track its internal and external edges/holes. Or maybe create a fixed number of grass entities (object and pointer) for every state it could be in and use those for various tiles, switching between states as a tile is affected by external factors.
			insert_o(new_o);
		}
	}
	for(int i=0;i<15;i++){
		int new_x = rand() % Environment::columns;
		int new_y = rand() % Environment::rows;
		new_o = { new_id(1), &species[1], new_x, new_y };//tree
		insert_o(new_o);
	}
	for(int i=0;i<30;i++){
		int new_x = rand() % Environment::columns;
		int new_y = rand() % Environment::rows;
		new_o = { new_id(2), &species[2], new_x, new_y };//berrybush
		insert_o(new_o);
	}
	for(int i=0;i<4;i++){
		int new_x = rand() % Environment::columns;
		int new_y = rand() % Environment::rows;
		new_o = { new_id(3), &species[3], new_x, new_y, (bool)(i % 2)};//ensures a 50/50 sex ratio //deer
		insert_o(new_o);
	}
	for (int i = 0;i < 4;i++) {
		int new_x = rand() % Environment::columns;
		int new_y = rand() % Environment::rows;
		new_o = { new_id(5), &species[5], new_x, new_y, (bool)(i % 2)};//ensures a 50/50 sex ratio //human
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
	bool air_deprivation_death = o->needs[0].current_level == 0;
	bool heat_cold_death = o->needs[1].current_level == 0 || o->needs[1].current_level == 100;


	if (air_deprivation_death || heat_cold_death) { o->alive = false; }


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

void Biology::change_need_level(Organism* o, int need, float amt) {
	o->needs[need].current_level += amt * o->needs[need].change_rate;
	if (o->needs[need].current_level > 100) { o->needs[need].current_level = 100; }
	else if (o->needs[need].current_level < 0) { o->needs[need].current_level = 0; }
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



//forgot to break out / return of if statement when executing move_to_new_search_space() which is the fail state for not finding target/path to satisfy need, applies to all need functions.
//also need to add a return statement for successful finds/reaching target.
//The triggers for each satisfaction function also aren't properly implemented, it should be both triggered by priority && need[_].current_level
//every need function also needs a corresponding attribute in the organism struct that controls if the satisfaction/deterioration even executes in the first place and if so, which version given it might have different versions such as subsistence type, plant behavior vs animals, etc.

//Needs to implement right now			Think first in terms of conditional statements, then in functions to be able to check those conditionals.
	//Needs_Physiological {//all needs start at 100% satisfaction, each species (and sometimes individual) has a different rate of decreasing and increasing each
		
/*done-ish*/if (need == "air") {//function essentially reduces to if in x, reduce need level, if need level is below y, get out of x.
	//[0]	 air = "";
	// if submerged in water, air need_level falls and death occurs when it reaches 0, need_level rises once out of water again. Inverse for fish.
	// if air has smoke/poison air need_level falls until death at 0 same as submerged underwater. Poison (maybe smoke?) has added damage effects
	// Requires a way to check if submerged/buried and whether tile has airborne smoke/poison
	// Satisfy need by moving to nearest source of clean air
	// Low need causes lung damage? Reduces ability to move/think.
		if(o->move_to_breathable_tile){//get out of unbreathable tile to breathable tile
			return_vars r1 = find(o, "terrain", "all", 10);
			vector<Environment::Tile> breathable_tiles = r1.r_tile;
			for (int i = breathable_tiles.size()-1; i > -1; i--) {
				if (breathable_tiles[i].has_smoke==false || breathable_tiles[i].has_toxic_gas==true) {
					breathable_tiles.erase(breathable_tiles.begin() + i);
				}
				if (breathable_tiles[i].terrain == "deep water" && o->species->breathes_water == false) {
					breathable_tiles.erase(breathable_tiles.begin() + i);
				}
				if ((breathable_tiles[i].terrain != "deep water" || breathable_tiles[i].terrain != "shallow water") && o->species->breathes_air == false) {
					breathable_tiles.erase(breathable_tiles.begin() + i);
				}
			}
			if (breathable_tiles.size() == 0) { move_to_new_search_space(o,10); }
			else {
				move_to(o, breathable_tiles[0].x, breathable_tiles[0].y);
			}
		}
	}
/*done-ish*/if (need == "heat") {//similar to air need, simply move to tile with better temperature
	//[1]	 heat = ""; //maintain proper temperature hot/cold
	// if tile or item carried is too hot or too cold, adjust need level according to temperature and take damage at a certain level. 
	// Unlike other needs, this one is good at level 50, 100 is deadly hot and 0 is deadly cold with corresponding damage types (frozen solid, frostbite, hypothermia, heat stroke, burning, charred, incinerated) and affects ability to move
	// Satisfy need by moving towards better temperature tiles or dropping hot/cold item. 
	// Need to implement a temperature system in the environment/items influenced by air/sun/shade/etc.
		if (o->needs[1].current_level > 60) {
			return_vars r1 = find(o, "terrain", "all", 10);
			vector<Environment::Tile> better_temperature_tiles = r1.r_tile;
			float better_temp = Environment::map[o->y][o->x].temperature;
			int better_index=-1;
			for (int i = better_temperature_tiles.size() - 1; i > -1; i--) {
				if (better_temperature_tiles[i].temperature < better_temp) {
					better_temp = better_temperature_tiles[i].temperature;
					better_index = i;
				}
			}
			if (better_index==-1) { move_to_new_search_space(o, 10); }
			else {
				move_to(o, better_temperature_tiles[better_index].x, better_temperature_tiles[better_index].y);
			}
		}
		else if (o->needs[1].current_level < 40) {
			return_vars r1 = find(o, "terrain", "all", 10);
			vector<Environment::Tile> better_temperature_tiles = r1.r_tile;
			float better_temp = Environment::map[o->y][o->x].temperature;
			int better_index = -1;
			for (int i = better_temperature_tiles.size() - 1; i > -1; i--) {
				if (better_temperature_tiles[i].temperature > better_temp) {
					better_temp = better_temperature_tiles[i].temperature;
					better_index = i;
				}
			}
			if (better_index==-1) { move_to_new_search_space(o, 10); }
			else {
				move_to(o, better_temperature_tiles[better_index].x, better_temperature_tiles[better_index].y);
			}
		}


	}
		//[2]	 clothes = ""; //only applies to humans (and hermit crabs), might make more sense to merge with temperature as clothes is about enduring the environment
		// Implement this later, requires ability to craft clothes and ingredients to do so, etc. 
		//
		//[3]	 hygiene = ""; //only applies to humans, maybe cats?
		// Dirtiness reduces need level and causes morale/discomfort hits (how is this measured and stored?) and increased chances of disease/infection
		// Need to implement sources and types of dirtiness (dust/dirt/mud/sweat/blood/etc)
/*done-ish*/if (need == "light") {//can tolerate being in bad light for a while, moves to better lighting after that while or if blinded by light level (too dark/too bright)
	//[4]	 light = ""; //especially important for plants
	// Need to implement a light (and therefore also shade) system in the environment for tiles, have organisms move to tiles with more light. Light level adjusts need level.
	// If need level is 0 then the organism is blind and moves blindly until it gets to better lighting. Low light causes mood hit (how to measure/store this?)
	// A plant with lower light level grows slower and if the level is too low it begins to take damage (wilt) and die
		//need to add an option to create light, such as with fire/torch/lamp/etc rather if one can rather than moving to a better lighting.
	//need a way to differentiate between if an organism can move or if it can't, differentiation between organism immobility and species immobility as well. This applies to all functions.
	//in a way, a plant does "move" towards light by growing in the direction of more light.
	if (o->needs[4].current_level<50 || o->too_dark_bright==true) {//unsure what light level numbers actually mean yet. If the difference between the ideal light level is too high, then move to a better light level. (too dark or too bright = blindness/lowered sight)
			return_vars r1 = find(o, "terrain", "all", 10);
			vector<Environment::Tile> better_light_tiles = r1.r_tile;
			float better_light = abs(Environment::map[o->y][o->x].light_level - o->species->ideal_light_level);
			int better_index = -1;
			for (int i = better_light_tiles.size() - 1; i > -1; i--) {
				if (abs(better_light_tiles[i].light_level- o->species->ideal_light_level) < better_light) {
					better_light = abs(better_light_tiles[i].light_level - o->species->ideal_light_level);
					better_index = i;
				}
			}
			if (better_index == -1) { move_to_new_search_space(o, 10); }
			else {
				move_to(o, better_light_tiles[better_index].x, better_light_tiles[better_index].y);
			}
		}
	}		
/*done-ish*/if (need == "water") {
	//[5]	 water = "";
	// Need to implement water system later on as well as containers for water like pots/cups/waterskins. 
	// Need level deteriorates over time, with deterioration rate influenced by heat
	// Satisfy need by finding nearest water source and consuming it
	// Plants get their water need satisfied by growing out roots into surrounding tiles in preference towards tiles that contain more water. Dirt tiles can hold water.
	// These tiles get their water level replenished by either surrounding water over time or rain. 
	if (o->needs[5].current_level < 60) {
		return_vars r1 = find(o, "terrain", "shallow water", 10);
		return_vars r2 = find(o, "terrain", "deep water", 10);//can simplify and therefore remove these by passing an array of strings to the find() function such that one can search for multiple terrain types, etc. Likewise for diet.
		bool reached;
		if (r1.r_tile.size() == 0 && r2.r_tile.size() == 0) { move_to_new_search_space(o, 10); }
		else if (r1.r_tile.size() == 0) { reached = move_to(o, r2.r_tile[0].x, r2.r_tile[0].y); }
		else if (r2.r_tile.size() == 0) { reached = move_to(o, r1.r_tile[0].x, r1.r_tile[0].y); }
		else {
			int d1 = o->x - r1.r_tile[0].x;
			int d2 = o->y - r1.r_tile[0].y;
			int d3 = o->x - r2.r_tile[0].x;
			int d4 = o->y - r2.r_tile[0].y;
			if (abs(d1) + abs(d2) <= abs(d3) + abs(d4)) { reached = move_to(o, r1.r_tile[0].x, r1.r_tile[0].y); }//if shallow water is closer, go to it, else go to deeper water
			else {
				reached = move_to(o, r2.r_tile[0].x, r2.r_tile[0].y);
			}
			if (reached) { change_need_level(o, 5, 100); }//if reached water, drink and fill all water. Currently haven't implemented a draining of source for smaller sources like puddes/containers/etc. Even larger sources eventually should drain. 
		}
	}
}
/*done-ish*/if (need == "urination") {//uses o_it[1]		need to add an external reset for if function is interrupted/does not finish/etc  same for all functions that use an external iterator
		//[6]	 urination = "";
		// Need is inversely proportional to water need, as in if hydrated need to piss, else no. If need reaches 0, piss. Need deteriorates periodically. 
		// Satisfied by taking a piss which resets need level to 100. Pissing adds piss, a type of contaminated water, to tile.
		bool reached = false;
		if (o->needs[6].current_level < 30 ) {//move to spot to urinate
			//for now, simply move 10 tiles away and urinate there, then move back to original position
			if (o->o_it[1][0] == 0) { 
				o->o_it[1][0] = 1; 
				o->o_it[1][1] = o->x;
				o->o_it[1][2] = o->y;
			}//init function
			if (!out_of_bounds(o->o_it[1][1] + 10, o->o_it[1][2])) { reached=move_to(o, o->o_it[1][1] + 10, o->o_it[1][2]); }
			else if (!out_of_bounds(o->o_it[1][1] - 10, o->o_it[1][2])) { reached = move_to(o, o->o_it[1][1] - 10, o->o_it[1][2]); }
			if (reached) {
				o->o_it[1][0] = 0;//reset iterator
				o->needs[6].current_level = 100;//reset need
				Environment::map[o->y][o->x].item_id.push_back(1);//for now, an item id of 1 is piss, all piss shares this id. Later on, liquids should be treated as a different object rather than just an item so that they both behave and integrate with a complete water cycle system.
				//need to add a way to delete piss after a period of time, otherwise it will endlessley accumulate.
			}
		}
		if (o->needs[6].current_level == 0) {//if 0, force urinate
			o->o_it[1][0] = 0;//reset iterator
			o->needs[6].current_level = 100;//reset need
			Environment::map[o->y][o->x].item_id.push_back(1);
		}
	}
/*almost done-ish*/if (need == "food") {//currently simply chooses nearest edible organism, later add a way to pick so that a hunting omnivore doesn't stop to pick berries in the middle of a hunt.
	//[7]	 food = ""; //soil nutrients for plants
		// Need level deteriorates over time, satisfy need by consuming food that matches organism's diet, obtain food through corresponding subsistence methods
		// Food is either an organism or an item, contains calories which fill up according to need level change rate, 
		// If need level reaches 0, die of starvation. Later add a calorie in / calorie out system to control fat/skinny levels. Then a nutrition system for malnourishment.
		// Plants get their food need satisfied the same way they get water, by growing roots towards dirt tiles with higher soil fertility/nutrition levels. These tiles level are replenished by decomposing corpses and decomposing excrement.
		if (o->needs[7].current_level < 50) {
			return_vars nearby_food = find(o, "species", o->species->diet, 10);//need to include food items not just food organisms
			if (nearby_food.r_organism.size() == 0) { move_to_new_search_space(o, 10); }
			if (nearby_food.r_organism[0]->species->species_name == "grass" || nearby_food.r_organism[0]->species->species_name == "berrybush") {//could also just combine all strings and check if string1 is a substring of the longer string2		makes more sense to have a "plant/animals" attribute			need to implement a utility function that checks if string x is or isn't equal to one of many strings
				//if plant, gather/forage/graze
				if (o->species->subsistence_method[0] == "gather") {//move to target, consume target
					bool reached = move_to(o, nearby_food.r_organism[0]->x, nearby_food.r_organism[0]->y);
					if (reached) {
						change_need_level(o, 7, nearby_food.r_organism[0]->species->calories);//currently consumes entire food organism, need to implement partial consumption, this will necessitate moving calories from species to organism struct
						delete_o(nearby_food.r_organism[0]); //need to implement a function to delete the organism from the radix tree and then later handle deleting from organisms vector
					}
				}
			}
			else if (nearby_food.r_organism[0]->species->species_name == "deer") {
				//if animal, hunt by: ambush, persistance, pack, solo, trap, lure
				if (o->species->subsistence_method[1] == "hunt") {//currently is simply persistence chase prey until prey is exhausted or overrun, then attack prey until dead, then consume
					bool reached = move_to(o, nearby_food.r_organism[0]->x, nearby_food.r_organism[0]->y);//need to implement walk/run choice, species speed, and species and organism exhaustion/stamina					
					if (reached) {
						attack(o, nearby_food.r_organism[0], "basic melee"); //need to implement an attack function, attack(attacker, target, attack method); Also requires implementing health, damage, etc.
						if (nearby_food.r_organism[0]->alive == false) {
							change_need_level(o, 7, nearby_food.r_organism[0]->species->calories);//currently consumes entire food organism, need to implement partial consumption, this will necessitate moving calories from species to organism struct
							delete_o(nearby_food.r_organism[0]); //need to implement a function to delete the organism from the radix tree and then later handle deleting from organisms vector
						}
					}
				}
			}
		}
	}	
/*done-ish*/if (need == "excretion") {//niether this nor the urination function will actually move back both because its not implemented but also becuase it won't trigger once need is satisfied other than the first step back
	//[8]	 excretion = "";
		// Need is inversly proportional to food need, so if food need level is high, excretion level deteriorates over time. If level hits 0, take a shit. This creates a shit item in the tile which decomposes over time until it dissappears, increasing soil nutrition as it does. 
		// While the shit item is still present, it has a chance to infect nearby organisms with a disease. If it is contact with water either as a water tile or held in the soil, the water becomes contaminated water.
	//currently the same as urination but with item id of "2" and tied to food instead of water need level
		bool reached = false;
		if (o->needs[8].current_level < 30) {//move to spot to shit
			//for now, simply move 10 tiles away and shit there, then move back to original position
			if (o->o_it[1][0] == 0) {
				o->o_it[1][0] = 1;
				o->o_it[1][1] = o->x;
				o->o_it[1][2] = o->y;
			}//init function
			if (!out_of_bounds(o->o_it[1][1] + 10, o->o_it[1][2])) { reached = move_to(o, o->o_it[1][1] + 10, o->o_it[1][2]); }
			else if (!out_of_bounds(o->o_it[1][1] - 10, o->o_it[1][2])) { reached = move_to(o, o->o_it[1][1] - 10, o->o_it[1][2]); }
			if (reached) {
				o->o_it[1][0] = 0;//reset iterator
				o->needs[8].current_level = 100;//reset need
				Environment::map[o->y][o->x].item_id.push_back(2);//for now, an item id of 2 is shit, all shit shares this id. Later on, shit should be treated as a type of corpse or other thing that decomposes rather than just an item so that it slowly dissapears and refills local soil/water with nutrients for plants/filter feeders. Also needs to be a biohazard that can cause infections nearby.
				//need to add a way to delete piss after a period of time, otherwise it will endlessley accumulate.
			}
		}
		if (o->needs[8].current_level == 0) {//if 0, force shit
			o->o_it[1][0] = 0;//reset iterator
			o->needs[8].current_level = 100;//reset need
			Environment::map[o->y][o->x].item_id.push_back(2);
		}
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

/*not done*/if (need == "sleep") {
	//[10]	 sleep = "";
		// Need level deteriorates over time. If it reaches 0 organism falls asleep then and there. Affected by exhaustion level (need to implement). If it falls below a certain level, organism actively seeks a place to sleep.
		// Need satisfied by sleeping, sleep environment affects rate of satisfaction (light/sound/danger/getting hit/rain/wind/hard or rough sleep spot/etc). 
		// Wake up when need level reaches 100 or if another need such as food/water/heat/etc deteriorates to a certain point so that it takes priority over sleep.
		// Sleep need level affects movement/thinking
		if (o->needs[10].current_level == 0) {//if it hits 0, this should take top priority in needs as it is forced sleep and sleep satisfies need
			o->awake = false;
			change_need_level(o, 10, 1);
		}
		else if (o->needs[10].current_level < 30) {//if sleep level is low, search for adequate sleep spot
			//need to implement a sleep spot identification method
		}
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
void Biology::periodic(Organism* o) {//might make more sense to just call this function need_deterioration
	//air need deterioration. Deteriorates over time depending on the breathability of the tile currently on.
	//"deep water" is used until a proper z axis is implemented, "shallow water" is currently breathable by air breathers as it assumes their head is above water
	bool is_drowning = o->species->breathes_air = true && o->species->breathes_water == false && Environment::map[o->y][o->x].terrain == "deep water";
	bool fish_out_of_water = o->species->breathes_air = false && o->species->breathes_water == true && Environment::map[o->y][o->x].terrain != "deep water" && Environment::map[o->y][o->x].terrain != "shallow water";
	bool is_suffocating = false; //need to implement, not sure how. Check if organism is buried, but exempt burrowing animals? What about damaged lungs?
	bool in_smoke = Environment::map[o->y][o->x].has_smoke == true;
	bool in_poison_gas = Environment::map[o->y][o->x].has_toxic_gas == true;
	if (is_drowning || fish_out_of_water || is_suffocating || in_smoke || in_poison_gas) {//makes more sense to restructure this to only check what's relevant rather than check all conditionals
		if (o->needs[0].current_level < 50) { o->move_to_breathable_tile = true; }//can tolerate being in unbreathable tile for a certain amount of time, until need level falls below 50
		change_need_level(o, 0, -1);//reduce air need level, 0=death				need to separate need deterioration and checks from attempt to satisfy need
	}
	else {
		o->move_to_breathable_tile = false;
		change_need_level(o, 0, 1);//if in breathable tile, increase need level
	}



	//heat need change
	float diff_temp = Environment::map[o->y][o->x].temperature - o->temperature;
	o->temperature += 0.2 * diff_temp;//increases/decreases organism temp by 20% of difference. So that hotter/colder tiles heat/cool organism faster but the organism never overshoots the tile temperature.
	//unsure whether to add the same to the tile, so a hot organism can heat up a tile, etc
	change_need_level(o, 1, 0.2 * diff_temp);
	bool combust = o->temperature > 200;//this should apply to corpses too
	bool burn = o->temperature > 150;//skin burn, no ignition
	bool heatstroke = o->temperature > 100;
	bool hypothermia = o->temperature < 20;
	bool frostbite = o->temperature < 0;
	bool freeze = o->temperature < -20;
	if(combust){}//need to implement
	else if(burn){}
	else if(heatstroke){}
	else if(freeze){}
	else if (frostbite) {}
	else if (hypothermia) {}

	//light need change
	int diff_light = Environment::map[o->y][o->x].light_level - o->species->ideal_light_level;
	if (diff_light > 50) { o->too_dark_bright = true; }
	else if (diff_light > 10) { o->too_dark_bright = false; change_need_level(o,4,-1); }
	else{ o->too_dark_bright = false; change_need_level(o, 4, 1); }


	//water need change
	change_need_level(o, 5, -1);

	//urination need change
	if (o->needs[5].current_level > 50) { change_need_level(o,6,-1); }//if water need level above 50, decrease urination need level (low level means have to urinate)

	//food need change
	change_need_level(o, 7, -1);

	//defecation need change
	if (o->needs[7].current_level > 50) { change_need_level(o, 8, -1); }//if food need level above 50, decrease defecation need level (low level means have to shit)

	//sleep need change
	change_need_level(o, 10, -1);
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



