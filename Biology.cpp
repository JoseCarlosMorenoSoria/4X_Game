#include "Biology.hpp"

using namespace std; 

vector<Biology::Organism> Biology::organisms;
Biology::radix Biology::o_root;
int Biology::id_iterator; 

Biology::Biology() {}
//initialization
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
bool Biology::find(vector<string> v, string s) {
	if (std::find(v.begin(), v.end(), s) != v.end()) {
		return true;
	}
	else {
		return false;
	}
}
int Biology::new_id(int species_id) {//creates new id for new organism, id can encode further info such as species id, etc. Given organisms are sorted by id through radix sort/search, it speeds up access time
	int id = id_iterator;
	id_iterator++;
	//set first digit from right as species id (this means it's temp limited to only 10 species)
	id *= 10;
	id += species_id;
	return id;
}
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
//returns organism
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
			cout << "id not found" << endl;
			return nullptr;
		}
	}

	if (it->o == nullptr) {
		cout << "id not found" << endl;
		return nullptr;
	}
	return it->o;
}
void Biology::delete_o(Organism* o) {//mark as deleted and remove pointer from tree. Object is deleted from vector in another function so as to not invalidate pointers in radix tree.
	o->deleted = true;
	radix* it = &o_root;
	int digits = 0;
	int tmp_id = o->organism_id;
	while (tmp_id) {
		tmp_id /= 10;
		digits++;
	}
	int num = o->organism_id;
	vector<radix*> to_delete;

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
			cout << "id not found" << endl;
			return;
		}
		to_delete.push_back(it);
	}

	if (it->o == nullptr) {
		cout << "id not found" << endl;
		return;
	}
	else {
		int d_num = o->organism_id;
		it->o = nullptr;
		delete it;
		for (int i = to_delete.size() - 1; i > -1; i--) {//delete any empty nodes going back up the tree, stop at first non empty node
			radix* rem = to_delete[i];
			if (rem->o == nullptr && rem != &o_root) {//if empty and not root just to be safe
				delete rem;
			}
			else {
				return;
			}
		}
	}
}
//simple move function
bool Biology::move_to(Organism* o, int x, int y) {//return true if destination reached, else false		need to add: return true if adjacent to target location && location is occupied by collidable object (not grass/etc)
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
//handles if and when ann organism dies and deterioration of the corpse
void Biology::death(Organism* o) {//uses o_it[2]
	if(o->alive==false){
		if (o->o_it[2][0] == 20) {//if(done_decomposing){delete organism object from radix tree}
			delete_o(o);
		}
		o->o_it[2][0]++;
		//decompose corpse
		//need to implement, includes adding nutrients to surrounding soil / water
	}
	else {//check if any death condition met
		//need related deaths
		bool air_deprivation_death = o->needs[0].current_level == 0;
		bool heat_cold_death = o->needs[1].current_level == 0 || o->needs[1].current_level == 100;
		bool health_death = o->needs[11].current_level == 0;
		bool food_death = o->needs[7].current_level == 0;
		bool water_death = o->needs[5].current_level == 0;

		if (air_deprivation_death || heat_cold_death || health_death || food_death || water_death) {
			o->alive = false;
		}
	}
}
//true if out of bounds, false if in bounds
bool Biology::out_of_bounds(int x, int y) {
	if (x > Environment::columns) { return true; }
	else if (x < 0) { return true; }
	if (y > Environment::rows) { return true; }
	else if (y < 0) { return true; }
	return false;
}
//general search function
Biology::return_vars Biology::find(Organism* o, string target_type, vector<string> targets, int search_radius) {//to find an empty tile (no organisms), just search "terrain" "all" to get all tiles in search space and then select the first tile that has an organism id vector size of 0 (or 1 and check if it's grass or not)
	bool found_target = false;
	return_vars r;
	//gets list of all tiles within search_radius, sorted by distance to search origin. Iterates in rings in an outward direction.
	vector<Environment::Tile> search_space;
	for (int tmp_radius = 0; tmp_radius <= search_radius; tmp_radius++) {
		for (int y = o->y - tmp_radius; y < o->y + tmp_radius; y++) {
			if (!out_of_bounds(tmp_radius, y)) { search_space.push_back(Environment::map[y][tmp_radius]); }
			if (!out_of_bounds(-tmp_radius, y)) { search_space.push_back(Environment::map[y][-tmp_radius]); }
		}
		for (int x = o->x - tmp_radius + 1; x < o->x + tmp_radius - 1; x++) {
			if (!out_of_bounds(x, tmp_radius)) { search_space.push_back(Environment::map[tmp_radius][x]); }
			if (!out_of_bounds(x, -tmp_radius)) { search_space.push_back(Environment::map[-tmp_radius][x]); }
		}
	}
	vector<Environment::Tile> found_t;
	vector<Organism*> found_o;
	//find targets
	for (int i = 0; i < search_space.size(); i++) {
		if (target_type == "terrain") {
			if (targets[0] == "all") {//if all, then adds all tiles to found vector
				r.r_tile = search_space;
				return r;
			}
			if (find(targets, search_space[i].terrain)) {//else add to found vector if the tile's terrain matches one of the targets
				found_t.push_back(search_space[i]);
			}
		}
		else if (target_type == "species") {
			for (int j = 0; j < search_space[i].organism_id.size(); j++) {
				Organism* tmp_o = get_by_id(search_space[i].organism_id[j]);
				if (targets[0] == "all" || find(targets, tmp_o->species->species_name) && o->organism_id!=tmp_o->organism_id) {
					found_o.push_back(tmp_o);
				}
			}
		}
		else if (target_type == "sleep spot") {//currently a valid sleep spot is any tile that's not water and has no organism on it (other than grass)
			bool is_not_water = r.r_tile[i].terrain != "shallow water" || r.r_tile[i].terrain != "deep water";
			bool no_organism = r.r_tile[i].organism_id.size() == 0 || (r.r_tile[i].organism_id.size() == 1 && get_by_id(r.r_tile[i].organism_id[0])->species->species_name == "grass");
			bool valid_sleep_spot = is_not_water && no_organism;
			if (valid_sleep_spot) {
				found_t.push_back(search_space[i]);
			}
		}
	}
	//return results
	if (target_type == "terrain"){
		if (found_t.size() != 0) {
			found_target = true;
			r.r_bool.push_back(found_target);
			r.r_tile = found_t;
			return r;
		}
	}
	else if (target_type == "species") {
		if (found_o.size() != 0) {
			found_target = true;
			r.r_bool.push_back(found_target);
			r.r_organism = found_o;
			return r;
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
int Biology::distance(int x1, int y1, int x2, int y2) {
	int dx = x1 - x2;
	int dy = y1 - y2;
	return abs(dx) + abs(dy) - 1;
}
string Biology::calculate_top_need(Organism* o) {
	int need_index;
	if (o->species->is_plant == true) {//plants don't have to prioritize, simply execute all need satisfactions at once
		satisfy_needs(o, 10, 5, true);//restructure Organism struct so that plants have a different sized Needs array so it only has 7 needs rather than 35
		satisfy_needs(o, 10, 7, true);
		satisfy_needs(o, 10, 11, true);
		satisfy_needs(o, 10, 17, true);
		return "is_plant";
	}

	int distance_cost;
	int search_radius = 10;
	bool no_emergency_priority = true;//if false skips over selecting for top priority

	for (int i = 0; i < sizeof(o->needs) / sizeof(Need); i++) {	//calculate urgency*utility scores
		vector<string> primary = { "air","heat"/*ideal is 50*/,"water","food","health"};//these cause death if they hit 0 and so are always top priority
		vector<string> autoneeds = { "sleep","urination","excretion" };//these are satisfied on the spot involuntarily when they hit current_level=0
		vector<string> secondary = { "light"/*ideal is 50*/,"clothes","shelter","hygiene","personal_security" };//these are support needs for primary needs?
		vector<string> tertiary = { "intimacy" };

		distance_cost = satisfy_needs(o, search_radius, i, false);
		if (distance_cost == 0) { distance_cost += 1; }
		else if (distance_cost == -1) { o->needs[i].priority = -1; continue; }//if -1, then that means this need intentionally has no satisfaction method

		if (find(autoneeds, o->needs[i].need_name)) {
			if (o->needs[10].current_level<60 && o->awake == false) {//if asleep and not well rested, keep sleeping. Need to add a way to modify how much is enough according to other needs. Ex: if not hungry, enough sleep == 60, if hungry then enough sleep == 30
				need_index = 10;
				no_emergency_priority = false;
				break;
			}
			else {
				o->awake = true; //if enough sleep, then wake up
			}
			if (o->needs[i].current_level == 0) {//if reaches 0, no need to compare it to other scores.
				need_index = i;
				no_emergency_priority = false;
				break;
			}
			else {//else calculate a score
				o->needs[i].priority = (100-o->needs[i].current_level) / distance_cost;  //this is the current implementation but it might make more sense to reverse current_level such that 100 (not 0) is the number that triggers death/negative effects/etc. Otherwise the 100-current_level is necessary to align calculation with higher number == top priority. Alternatively, cahnge priority calculation such that 0 is top priority?
			}
		}
		else if (find(primary, o->needs[i].need_name)) {
			o->needs[i].priority = (100 - o->needs[i].current_level) / distance_cost;//initial default formula calculation, adds 1 to prevent divide by 0
			if (o->needs[i].need_name == "heat") {
				//has special calculation where 50 (51 might be better?) is the desired state whereas 0 and 100 are death
				if (o->needs[i].current_level < 33 || o->needs[i].current_level > 67) {
					o->needs[i].priority *= 10;
				}
			}
			else if (o->needs[i].current_level < 50) {//if below 50, increase priority multiplying by 10
				o->needs[i].priority *= 10;
			}
		}
		else if (find(secondary, o->needs[i].need_name)) {
			o->needs[i].priority = (100 - o->needs[i].current_level) / distance_cost;//initial default formula calculation
			if (o->needs[i].need_name == "light") {
				//has special calculation where 50 (51 might be better?) is the desired state //has a special case? trigger based on if currently blinded or not
				if (o->needs[i].current_level < 20 || o->needs[i].current_level > 80 || o->too_dark_bright == true) {
					o->needs[i].priority *= 5;
				}
			}
			else if (o->needs[i].current_level < 25) {//if below 25, increase priority multiplying by 5
				o->needs[i].priority *= 5;
			}
		}
		else if (find(tertiary, o->needs[i].need_name)) {
			o->needs[i].priority = (100 - o->needs[i].current_level) / distance_cost;//initial default formula calculation
		}
		else {
			//do nothing for needs not implemented
		}	
	}

	int max_piority = 0;// need to make sure that no priority can accidentally be less than 0?
	if (no_emergency_priority) {
		for (int i = 0; i < sizeof(o->needs) / sizeof(Need); i++) {//get top priority
			if (max_piority < o->needs[i].priority) {
				max_piority = o->needs[i].priority;
				need_index = i;
			}
		}
	}

	if (max_piority == 0) {//no need needs satisfying
		return "none";
	}

	if ((satisfy_needs(o, search_radius, need_index, false) == search_radius + 1)) {//if this need is top priority but no target/path found then move to new search space, else execute path
		move_to_new_search_space(o, 10);
	}
	else {
		satisfy_needs(o, search_radius, need_index, true);
	}
	return o->needs[need_index].need_name;//return the need that is either being focused on or has been satisfied
}
int Biology::satisfy_needs(Organism* o, int search_radius, int need_index, bool execute) {//returns distance_cost to fulfill need, executes fulfillment if execute==true
	//Need to add an external reset for if function is interrupted/does not finish/etc  same for all functions that use an external iterator
	//Pull out common variables such as reached, temporary vectors, etc. Also need to add a need initialization given that some needs should start at 50 rather than 100, unless I reformat them to fit the 0-100 template
	//Think first in terms of conditional statements, then in functions to be able to check those conditionals.	

	if ((need_index != 10 || need_index != 11) && (o->can_move == false || o->awake==false)) {//except for sleep, an animal that loses it's ability to move temporarily (be it sleep or injury) or permanently cannot satisfy any needs
		return -1;
	}

	if (o->species->is_plant == true) {//plants have their own need system because they are so different and limited
		//it can grow towards better light, not sure how to implement that
		switch (need_index) {//plants also have the needs air, heat and light but can't do anything to satisfy these needs if the environment changes. Total 7 needs. 
		case 5:/*water*/
		{
			if (Environment::map[o->y][o->x].water_level > 0) {//Look into is there is a way to simplify a system of flow and equilibriums so as to reduce the number of operations executed, for example, if a system is in equilibrium no operation should execute ideally, or if there is flow in a line but the net change only affects the source and destination tiles, all "pipeline" tiles should not execute
				Environment::map[o->y][o->x].water_level -= 1;//reduces/consumes water from tile
				change_need_level(o, 5, 1);//plant draws water from the tile it's in. Later implement a root system to get water from other tiles.
			}
			break;
		}
		case 7:/*food*/
		{
			// Plants get their food need satisfied the same way they get water, by growing roots towards dirt tiles with higher soil fertility/nutrition levels. These tiles level are replenished by decomposing corpses and decomposing excrement.
			if (Environment::map[o->y][o->x].nutrient_level > 0) {
				Environment::map[o->y][o->x].nutrient_level -= 1;//get nutrients from current soil tile, behave the same as water need
				change_need_level(o, 7, 1);
			}
			break;
		}
		case 11:/*health*/
		{
			change_need_level(o, 11, 1);//simply constant regeneration
			break;
		}
		case 17: /*intimacy*/ //reproduction  spores vs seeds, spores?? simply spawn plant nearby, seeds?? can be carried by animals / sown by people,	also reproduction by division (seastars and plant buds)
		{
			if (o->species->reproduction_method == "spores") {
				return_vars r1 = find(o, "terrain", { "all" }, search_radius);
				for (int i = 0; i < r1.r_tile.size(); i++) {
					if (r1.r_tile[i].organism_id.size() <= 1) {
						if (r1.r_tile[i].organism_id.size() == 0) {
							birth(o, o, r1.r_tile[i].x, r1.r_tile[i].y);//birth a new organism
							change_need_level(o, 17, 100);
						}
						else if (get_by_id(r1.r_tile[i].organism_id[0])->species->species_name=="grass" && o->species->species_name!="grass") {//if the tile has grass and the reproducing organism is not grass, then can reproduce on that tile. (should this kill the grass on the tile?)
							birth(o, o, r1.r_tile[i].x, r1.r_tile[i].y);//birth a new organism
							change_need_level(o, 17, 100);
						}
					}
				}
			}
			break;
		}
		default:
			break;
		}
		return -1;
	}
	
	//all cases succes/fail/etc must return an int, even if not actually moving, otherwise calculate function can't give it a score
	switch (need_index)//given the extremely static and limited nature of plants, it makes more sense to pull them out into their own need system, so less needs and less satisfaction functions.
	{
	case 0: /* air */   //air need behavior essentially reduces to if in unbreathable tile x, reduce need level, if need level is below y, get out of x to breathable tile.
	{
		// Add a way to check if buried.		 Low air need level causes lung damage? Reduces ability to move/think.
		return_vars r1 = find(o, "terrain", { "all" }, search_radius);
		vector<Environment::Tile> search_space = r1.r_tile;
		int better_index = -1;
		for (int i = 0; i < search_space.size(); i++) {//find nearest (first) breathable tile from search space
			bool smoke_gas = search_space[i].has_smoke == true || search_space[i].has_toxic_gas == true;
			if (o->species->breathes == "air") {
				bool drowning = search_space[i].terrain == "deep water" && o->species->breathes == "air";//non-aquatic animals can breathe in shallow water but not deep water
				if (!(smoke_gas || drowning)) {
					better_index = i;
					break;
				}
			}
			else if (o->species->breathes == "water") {
				bool fish_out_of_water = (search_space[i].terrain != "deep water" || search_space[i].terrain != "shallow water");
				if (!(smoke_gas || fish_out_of_water)) {
					better_index = i;
					break;
				}
			}
		}
		if (better_index == -1) { return search_radius + 1; }
		else {
			if (execute) {
				move_to(o, search_space[better_index].x, search_space[better_index].y);
			}
			return distance(o->x, o->y, search_space[better_index].x, search_space[better_index].y);
		}
		break;
	}
	case 1: /*heat*/    //same behavior as air need, except it's bad temperature tile rather than unbreathable tile
	{	
		// need to add item temperature? For carrying hot/cold items? 
		// Unlike other needs, this one is good at level 50, 100 is deadly hot and 0 is deadly cold with corresponding effects (frozen solid, frostbite, hypothermia, heat stroke, burning, charred, incinerated) and affects ability to move
		// Need to implement a temperature system in the environment/items influenced by air/sun/shade/etc.
		return_vars r1 = find(o, "terrain", { "all" }, search_radius);
		vector<Environment::Tile> search_space = r1.r_tile;
		int better_temp_diff = abs(Environment::map[o->y][o->x].temperature - o->species->ideal_temperature);
		int better_index = -1;
		for (int i = 0; i < search_space.size(); i++) {
			if (abs(search_space[i].temperature - o->species->ideal_temperature) < better_temp_diff) {
				better_temp_diff = abs(search_space[i].temperature - o->species->ideal_temperature);
				better_index = i;
			}
		}
		if (better_index == -1) { return search_radius + 1; }
		else {
			if (execute) {
				move_to(o, search_space[better_index].x, search_space[better_index].y);
			}
			return distance(o->x, o->y, search_space[better_index].x, search_space[better_index].y);
		}
		break;
	}
	case 4: /*light*/   //can tolerate being in bad light for a while, moves to better lighting after that while or if blinded by light level (too dark/too bright)
	{
		//especially important for plants. Need to implement a light (and therefore also shade) system in the environment for tiles.
		// If need level is 0 then the organism is blind. Low light causes mood hit (how to measure/store this?)
		// A plant with lower light level grows slower and if the level is too low it begins to take damage (wilt) and die
		//need to add an option to create light, such as with fire/torch/lamp/etc rather if one can rather than moving to a better lighting.
		//in a way, a plant does "move" towards light by growing in the direction of more light.
		//unsure what light level numbers actually mean yet. If the difference between the ideal light level is too high, then move to a better light level. (too dark or too bright = blindness/lowered sight)
		return_vars r1 = find(o, "terrain", { "all" }, search_radius);
		vector<Environment::Tile> search_space = r1.r_tile;
		float better_light = abs(Environment::map[o->y][o->x].light_level - o->species->ideal_light_level);
		int better_index = -1;
		for (int i = search_space.size() - 1; i > -1; i--) {
			if (abs(search_space[i].light_level - o->species->ideal_light_level) < better_light) {
				better_light = abs(search_space[i].light_level - o->species->ideal_light_level);
				better_index = i;
			}
		}
		if (better_index == -1) { return search_radius + 1; }
		else {
			if (execute) {
				move_to(o, search_space[better_index].x, search_space[better_index].y);
			}
			return distance(o->x, o->y, search_space[better_index].x, search_space[better_index].y);
		}
		break;
	}
	case 5: /*water*/   // Satisfy need by finding nearest water source and consuming it
	{
		// Need to implement water system later on as well as containers for water like pots/cups/waterskins.	deterioration rate influenced by heat
		// Need to implement: Plants get their water need satisfied by growing out roots (? ) into surrounding tiles in preference towards tiles that contain more water. Dirt tiles can hold water.
		// These tiles get their water level replenished by either surrounding water over time or rain. 
		return_vars r1 = find(o, "terrain", { "shallow water", "deep water" }, search_radius);
		bool reached;
		if (r1.r_tile.size() == 0) { return search_radius + 1; }
		else {
			if (execute) {
				reached = move_to(o, r1.r_tile[0].x, r1.r_tile[0].y);
				if (reached) { change_need_level(o, 5, 100); }//if reached water, drink and fill all water. Currently haven't implemented a draining of source for smaller sources like puddes/containers/etc. Even larger sources eventually should drain. 
			}
			return distance(o->x, o->y, r1.r_tile[0].x, r1.r_tile[0].y);
		}
		break;
	}
	case 6: /*urination*/   //uses o_it[1] (replace with a cross function external iterator?)  // Need is inversely proportional to water need, as in if hydrated need to piss, else no. If need reaches 0, piss. Need deteriorates periodically. 
	{
		// Satisfied by taking a piss which resets need level to 100. Pissing adds piss, a type of contaminated water, to tile.
		bool reached = false;
		//move to spot to urinate
		if (o->needs[6].current_level != 0) {//if 0, urinate now, else find spot to do so first
			//for now, simply move 10 tiles away and urinate there
			if (o->o_it[1][0] == 0) {
				if (execute) {
					o->o_it[1][0] = 1;
				}
				if (!out_of_bounds(o->x + 10, o->y)) {
					o->o_it[1][1] = o->x + 10;
					o->o_it[1][2] = o->y;
				}
				else if (!out_of_bounds(o->x - 10, o->y)) {
					o->o_it[1][1] = o->x - 10;
					o->o_it[1][2] = o->y;
				}
			}//init function
			if (execute) {
				reached = move_to(o, o->o_it[1][1], o->o_it[1][2]);
			}
			if (!reached) {
				return distance(o->x, o->y, o->o_it[1][1], o->o_it[1][2]);
			}
		}
		o->o_it[1][0] = 0;//reset iterator
		o->needs[6].current_level = 100;//reset need
		Environment::map[o->y][o->x].item_id.push_back(1);//for now, an item id of 1 is piss, all piss shares this id. Later on, liquids should be treated as a different object rather than just an item so that they both behave and integrate with a complete water cycle system.
		//need to add a way to delete piss after a period of time, otherwise it will endlessly accumulate.
		return 0;//reached
		break;
	}
	/*hunt not done*/case 7: /*food*/ //currently simply chooses nearest edible organism, later add a way to pick so that a hunting omnivore doesn't stop to pick berries in the middle of a hunt.
	{
		// Need level deteriorates over time, satisfy need by consuming food that matches organism's diet, obtain food through corresponding subsistence methods
		// Food is either an organism or an item, contains calories which fill up according to need level change rate, 
		// Later add a calorie in / calorie out system to control fat/skinny levels. Then a nutrition system for malnourishment.
		return_vars nearby_food = find(o, "species", o->species->diet, 10);//need to include food items not just food organisms
		if (nearby_food.r_organism.size() == 0) { return search_radius + 1; }

		vector<string> plants = { "grass", "berrybush" };//makes more sense to have a "plant/animals" attribute instead of this makeshift temporary vector
		vector<string> animals = { "deer" };
		vector<string> methods = o->species->subsistence_method;//simply to make code easier to read
		bool consume = false;
		bool reached = false;
		if (find(plants, nearby_food.r_organism[0]->species->species_name)) {//if plant, gather/forage/graze
			if (find(methods, "gather")) {//move to target, consume target
				if (execute) {
					reached = move_to(o, nearby_food.r_organism[0]->x, nearby_food.r_organism[0]->y);
				}
				else {
					return distance(o->x, o->y, nearby_food.r_organism[0]->x, nearby_food.r_organism[0]->y);
				}
				if (reached) {
					consume = true;
				}
			}
		}

		else if (find(animals, nearby_food.r_organism[0]->species->species_name)) {//if animal, hunt by: ambush, persistance, pack, solo, trap, lure
			if (find(methods, "hunt")) {//currently is simply persistence chase prey until prey is exhausted or overrun, then attack prey until dead, then consume
				if (execute) {
					reached = move_to(o, nearby_food.r_organism[0]->x, nearby_food.r_organism[0]->y);//need to implement walk/run choice, species speed, and species and organism exhaustion/stamina					
				}
				else {
					return distance(o->x, o->y, nearby_food.r_organism[0]->x, nearby_food.r_organism[0]->y);
				}
				if (reached) {
					attack(o, nearby_food.r_organism[0], "basic melee");
					if (nearby_food.r_organism[0]->alive == false) {
						consume = true;
					}
				}
			}
		}

		if (consume) {
			change_need_level(o, 7, nearby_food.r_organism[0]->species->calories);//currently consumes entire food organism, need to implement partial consumption, this will necessitate moving calories from species to organism struct
			delete_o(nearby_food.r_organism[0]);
		}
		return 0;//done
		break;
	}
	case 8: /*excretion*/ //Uses o_it[3] Need is inversely proportional to food need, so if food need level is high, excretion level deteriorates over time. If level hits 0, take a shit. This creates a shit item in the tile which decomposes over time until it dissappears, increasing soil nutrition as it does. 
	{
		// While the shit item is still present, it has a chance to infect nearby organisms with a disease. If it is contact with water either as a water tile or held in the soil, the water becomes contaminated water.
		//currently the same as urination but with item id of "2" and tied to food instead of water need level
		//for now, an item id of 2 is shit, all shit shares this id. Later on, shit should be treated as a type of corpse or other thing that decomposes rather than just an item so that it slowly dissapears and refills local soil/water with nutrients for plants/filter feeders. Also needs to be a biohazard that can cause infections nearby.
		bool reached = false;
		if (o->needs[8].current_level != 0) {//if 0, shit now, else find spot to do so first
			if (o->o_it[1][0] == 0) {
				if (execute) {
					o->o_it[1][0] = 1;
				}
				if (!out_of_bounds(o->x + 10, o->y)) {//for now, simply move 10 tiles away and shit there
					o->o_it[1][1] = o->x + 10;
					o->o_it[1][2] = o->y;
				}
				else if (!out_of_bounds(o->x - 10, o->y)) {
					o->o_it[1][1] = o->x - 10;
					o->o_it[1][2] = o->y;
				}
			}//init function
			if (execute) {//move to spot to shit
				reached = move_to(o, o->o_it[1][1], o->o_it[1][2]);
			}
			if (!reached) {
				return distance(o->x, o->y, o->o_it[1][1], o->o_it[1][2]);
			}
		}
		o->o_it[1][0] = 0;//reset iterator
		o->needs[8].current_level = 100;//reset need
		Environment::map[o->y][o->x].item_id.push_back(1);
		return 0;//reached
		break;
	}
	/*not done*/case 9: /*shelter*/ // Find shelter, if no shelter found, build shelter. Use shelter to sleep at night, shade, lay eggs, stockpile food/materials, idle, etc. 
	{
		//might make sense to merge this with sleep need? or not?
		//applies only to animals that live in caves, nests, etc
	   // Need to implement both a natural shelter system (caves/holes) and the ability to build shelters (dig hole, build nest, build walls and roof, etc)
	   // Need is 0 when sleeping without shelter, 100 if sleeping with shelter. Later on add a quality system for shelter. Shelter deteriorates according to type/material/quality/etc so it must be constantly repaired. 
	   // Need to implement a system of territoriality, where an organism designates certain tiles as theirs, other's or unclaimed and either shares or competes with others for those tiles. Ownership/claims over tiles should be a spectrum such that certain things increase or decrease the strength ofthe claim/ownership such as marking territory, how often territory is walked through or seen, fights over it, etc.
	   // Shelter that has the strongest ownership to the organism is preferred over those that have less or no ownership to the organism, and unclaimed is prefferred to claimed by another. Balanced by distance such that if the organism cannot reach their home before sleep reaches 0, they choose the best nearest option.
		if (o->needs[9].current_level == 0) {//if no shelter		an extremely simple implementation of a shelter is to have it act as an item such that it takes up only 1 tile for now
			//find shelter		what is shelter? an enclosed space that protects from the elements (from heat/cold/threats/wind/rain). 
			return_vars r = find(o, "structure", { "shelter" }, 10); //need to implement this version of find() as in structure:shelter
			if (r.r_bool[0]) {//if found valid shelter (preferrably unoccupied/unclaimed, need to implement check and system for both as well as if choosing to challenge a claim)

			}
			//if none found, build shelter
		}
		break;
	}
	case 10: /*sleep*/ //If it reaches 0 organism falls asleep then and there. Affected by exhaustion level (need to implement). If it falls below a certain level, organism actively seeks a place to sleep.
	{
		// Need satisfied by sleeping, sleep environment affects rate of satisfaction (light/sound/danger/getting hit/rain/wind/hard or rough sleep spot/etc). 
		// Sleep need level affects movement/thinking
		bool reached = false;
		if (o->needs[10].current_level > 0 && o->awake==true) {//if sleep level is low, search for adequate sleep spot
			return_vars r1 = find(o,"sleep spot",{""},10);//need to implement a sleep spot identification method
			if (r1.r_tile.size() == 0) { return search_radius + 1; }
			else {
				reached = move_to(o, r1.r_tile[0].x, r1.r_tile[0].y);
				if (reached) {
					if (execute) {
						o->awake = false;//Also, turn off sight, reduce sound awareness, etc.
						change_need_level(o, 10, 1);
					}
				}
			}
		}
		else {//if == 0 or already asleep, force sleep
			if (execute) {
			o->awake = false;//Also, turn off sight, reduce sound awareness, etc.
			change_need_level(o, 10, 1);
			}
		}
		break;
	}
	case 11: /*health*/ //need a visual marker for each action/need so I know the organism is still runnning and not stuck if it's just resting
	{
		//rest to heal injuries, avoid sickness, avoid bad food/water. If human bandage injuries and use herbal medicines.
		// Need to implement health system that includes injury/damage and disease/contamination
		// Damage and being contaminated lowers health need level. If health need level reaches 0, organism dies. Level affects movement/thinking. 
		// Satisfy need by resting or priority based regen. 
		//Later implement a more detailed version that specifies damage to specific body parts which have specific effects on sight/speed/mobility/etc
		if (o->needs[11].current_level < 50) {//if health below half, stop moving and focus on healing
			if (execute) {
				o->can_move = false;
				change_need_level(o, 11, 1);
			}
		}
		else {
			if (execute) {//else heal now and then
				change_need_level(o, 11, 1);
			}
		}
		return 0;
		break;
	}
	/*not done*/case 12: /*personal_security*/ //
	{
		//avoid danger, flee danger, fight danger    this comes after physiological such that an individual might risk danger in order to obtain food/water
		// Items/tiles/organisms have a calculated threat level to an individual organism. If the threat is static such as contaminated food/tile on fire, response is to simply not consume or touch it.
		// If the threat is an organism then engage in fight/flight/hide/submit behavior according to the situation.

		//identify threats //instinctual threats (co evolved predator), learned threats (new predator), assumed threats (large animal)
		break;
	}
	case 17: /*intimacy*/ //reproduction 
	{
		// If sexual, depends on type (monogamous, polygamous exclusive (alpha male), polygamous non exclusive (some fish)) relation types might fit more in family than pure reproduction.
		// Find available/preferred mate. If necessary attract mate (mating ritual). Mate. Female is now either pregnant or laid eggs which have been or become fertilized. 
		return_vars r1 = find(o, "species", { o->species->species_name }, 10);
		Organism* mate=nullptr;
		for (int i = 0; i < r1.r_organism.size(); i++) {
			if (r1.r_organism[i]->sex != o->sex) {
				mate = r1.r_organism[i];
				break;
			}
		}
		if (mate == nullptr) { return search_radius + 1; }
		bool reached;
		if (execute) {
			reached = move_to(o, mate->x, mate->y);
		}
		else {
			return distance(o->x, o->y, mate->x, mate->y);
		}
		if (reached) {
			if (o->sex == false) { birth(o, mate, o->x, o->y); }
			change_need_level(o, 17, 100);
		}
		break;
	}
	default:
		break;
	}
}
//create new organism, allows options for specific contexts
void Biology::birth(Organism* mother, Organism* father, int x, int y) {//currently just makes a new basic organism, herititable traits not yet implemented
	Organism o = { new_id(mother->species->species_id), &species[mother->species->species_id], x, y, false };
}
//combat and hunting might make more sense as the same thing, pull hunting out into a general combat function as a specific combat method.
void Biology::attack(Organism* o, Organism* target, string attack_method) {
	if (attack_method == "basic melee") {
		change_need_level(target, 11, -(o->species->damage));//reduce target's health need level by the attacker's damage strength.
	}
}



//carry()	pick up or drop item
//all periodic changes such as need deterioration should be here
void Biology::periodic(Organism* o) {//might make more sense to just call this function need_deterioration
	//air need deterioration. Deteriorates over time depending on the breathability of the tile currently on.
	//"deep water" is used until a proper z axis is implemented, "shallow water" is currently breathable by air breathers as it assumes their head is above water
	bool is_drowning = o->species->breathes == "air" && Environment::map[o->y][o->x].terrain == "deep water";
	bool fish_out_of_water = o->species->breathes == "water" && Environment::map[o->y][o->x].terrain != "deep water" && Environment::map[o->y][o->x].terrain != "shallow water";
	bool is_suffocating = false; //need to implement, not sure how. Check if organism is buried, but exempt burrowing animals? What about damaged lungs?
	bool in_smoke = Environment::map[o->y][o->x].has_smoke == true;
	bool in_poison_gas = Environment::map[o->y][o->x].has_toxic_gas == true;
	if (is_drowning || fish_out_of_water || is_suffocating || in_smoke || in_poison_gas) {//makes more sense to restructure this to only check what's relevant rather than check all conditionals
		//can tolerate being in unbreathable tile for a certain amount of time, until need level falls below 50
		change_need_level(o, 0, -1);//reduce air need level, 0=death
	}
	else {
		change_need_level(o, 0, 1);//if in breathable tile, increase need level
	}



	//heat need change
	float diff_temp = Environment::map[o->y][o->x].temperature - o->temperature;
	o->temperature += 0.2 * diff_temp;//increases/decreases organism temp by 20% of difference. So that hotter/colder tiles heat/cool organism faster but the organism never overshoots the tile temperature.
	//unsure whether to add the same to the tile, so a hot organism can heat up a tile, etc
	change_need_level(o, 1, 0.2 * diff_temp);
	/*	Not Yet Implemented
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
	*/

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

	//excretion(aka defecation) need change
	if (o->needs[7].current_level > 50) { change_need_level(o, 8, -1); }//if food need level above 50, decrease defecation need level (low level means have to shit)

	//sleep need change
	change_need_level(o, 10, -1);
}
//context()						a listener that checks the organism"s state and immediate surroundings to respond to things like taking damage or the appearance of a threat
void Biology::context(Organism* o) {

}



void Biology::update(Organism* o) {
	calculate_top_need(o);

	//sets render attributes
	if (o->can_move == false) { o->png_file_state = "resting"; }
	if (o->awake == false) { o->png_file_state = "sleeping"; }
	if (o->alive == false) { o->png_file_state = "dead"; }
}
void Biology::update_all() {
	for (int i = 0; i < organisms.size(); i++) {
		if (organisms[i].deleted == true) {
			continue;
		}
		else {
			update(&organisms[i]);
		}
	}
}



