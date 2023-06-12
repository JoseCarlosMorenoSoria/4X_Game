#include "Biology.hpp"
using namespace std;

Biology::Biology(){}

Biology::Biology(Environment* env) {
	//recieve game's environment reference
	environment = env;

	//instantiate organisms
	Organism tmpOrganism;
	Position tmpPosition;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 40; j++) {
			tmpOrganism = { new_id(), /*grass*/species_presets[2], j, i };
			organisms[2].push_back(tmpOrganism);
		}
	}

	for(int i=0;i<4;i++){
		tmpPosition = { rand() % Environment::columns, rand() % Environment::rows };
		tmpOrganism = { new_id(), /*human*/species_presets[5],tmpPosition, (bool)(i % 2)/*ensures a 50/50 sex ratio*/ };
		environment->tie_to_tile(tmpOrganism.id, tmpOrganism.position.x, tmpOrganism.position.y);
		organisms[5].push_back(tmpOrganism); }
	for(int i=0;i<3;i++){
		tmpPosition = { rand() % Environment::columns, rand() % Environment::rows };
		tmpOrganism = { new_id(), /*deer*/species_presets[1],tmpPosition };
		environment->tie_to_tile(tmpOrganism.id, tmpOrganism.position.x, tmpOrganism.position.y);
		organisms[1].push_back(tmpOrganism); }
	for(int i=0;i<15;i++){
		tmpPosition = { rand() % Environment::columns, rand() % Environment::rows };
		tmpOrganism = { new_id(), /*tree*/species_presets[3],tmpPosition };
		environment->tie_to_tile(tmpOrganism.id, tmpOrganism.position.x, tmpOrganism.position.y);
		organisms[3].push_back(tmpOrganism); }
	for(int i=0;i<30;i++){
		tmpPosition = { rand() % Environment::columns, rand() % Environment::rows };
		tmpOrganism = { new_id(), /*berrybush*/species_presets[4],tmpPosition };
		environment->tie_to_tile(tmpOrganism.id, tmpOrganism.position.x, tmpOrganism.position.y);
		organisms[4].push_back(tmpOrganism); }
}

Biology::~Biology() {

}



/*------Utility Functions------------------------------------------------------------------------------------------------*/

int Biology::new_id() {
	int tmp = id_iterator;
	id_iterator++;
	return tmp;
}

bool Biology::move_to(int id, Position p) {
	Organism* o = get_by_id(id);
	//moves organism to target location
	if (p.x > Environment::columns - 1) { p.x = Environment::columns - 1; } //if target location is off the map, moves target location to map boundary
	else if (p.x < 0) { p.x = 0; }
	if (p.y > Environment::rows - 1) { p.y = Environment::rows - 1; }//might be better to reformat the function to return an int so as to return a "invalid target" signal
	else if (p.y < 0) { p.y = 0; }



	//these comparisons should be replaced with pos1-pos2 and then add the result to pos1, if result==0 return true

	//determine which format is prefferable, arithmetic or if-else    if result=0 there may be an error (divide by 0), might need a try catch block to handle it
	//this works as a replacement for the if statements below, though less legible, it might be better for both speed and simulation given that instead of calling the function multiple times, it can be multiplied by how many updates would have happened
	//int result = o->position.x - p.x; // gets difference in positions
	//o->position.x += (result/result); // result/result equals either 1 or -1, add it to move 1 step closer to target

	environment->untie_from_tile(o->id, o->position.x, o->position.y);

	if (o->position.x > p.x) { o->position.x--; }//once collisions are implemented, will need to add behavior for going around impassable objects
	else if (o->position.x < p.x) { o->position.x++; }
	if (o->position.y > p.y) { o->position.y--; }
	else if (o->position.y < p.y) { o->position.y++; }
	//handles hitting the edges of the map		might be redundant with ensuring target location is on the map
	if (o->position.x < 0) { o->position.x = 0; }
	else if (o->position.x > Environment::columns - 1) { o->position.x = Environment::columns - 1; }//should this be columns-1 or columns? likewise for the rows below
	if (o->position.y < 0) { o->position.y = 0; }
	else if (o->position.y > Environment::rows - 1) { o->position.y = Environment::rows - 1; }

	environment->tie_to_tile(o->id, o->position.x, o->position.y);

	if (o->position.x == p.x && o->position.y == p.y) { return true; }
	return false;
}


vector<Biology::Organism*> Biology::get_nearby_organisms(int id, int radius, string species) {
	Organism* o = get_by_id(id);
	if (species == "all") {
		vector<Organism*> nearby_organisms;
		vector<Organism*> tmp_nearby_organisms;
		for (int i = 0; i < sizeof(species_presets)/sizeof(Species); i++) {//get all nearby organisms, all species
			tmp_nearby_organisms = get_nearby_organisms(id, radius, species_presets[i].species_name);
			if (tmp_nearby_organisms.size() == 0) { continue; }
			if (nearby_organisms.size() == 0) { nearby_organisms = tmp_nearby_organisms; }
			else if (nearby_organisms.size() >= tmp_nearby_organisms.size()) {
				nearby_organisms.insert(nearby_organisms.end(), tmp_nearby_organisms.begin(), tmp_nearby_organisms.end());//append tmp_nearby to nearby. Done this way (append to larger vector) to reduce amount of copying when appending.
			}
			else {
				tmp_nearby_organisms.insert(tmp_nearby_organisms.end(), nearby_organisms.begin(), nearby_organisms.end());//append nearby to tmp_nearby
				nearby_organisms = tmp_nearby_organisms;
			}
		}
		return nearby_organisms;
	}

	vector<Organism*> found;
	int min_y = o->position.y - radius;
	int max_y = o->position.y + radius;
	int min_x = o->position.x - radius;
	int max_x = o->position.x + radius;

	int a = 0;
	for (int r = min_y; r < max_y; r++) {
		for (int c = min_x;c < max_x;c++) {
			Environment::Tile* tile = environment->get_tile(c,r);
			if (tile == nullptr) { continue; }
			for (int i = 0; i < tile->tile_organisms_id.size(); i++) {
				a = 1;
				Organism* tmpOrganism = get_by_id(tile->tile_organisms_id[i]);
				if (tmpOrganism == nullptr) { continue; }
				if (tmpOrganism->species.species_name == species && tmpOrganism->id!=o->id) {
					found.push_back(tmpOrganism);
				}
			}
		}
	}

	vector<Organism*> found_sorted; //sorted by distance from searching organism
	int sort_radius = 0;
	while (found.size() > 0) {
		for (int i = found.size()-1; i > -1; i--) {
			if (abs(o->position.x - found[i]->position.x) == sort_radius || abs(o->position.y - found[i]->position.y) == sort_radius) {
				found_sorted.push_back(found[i]);
				found.erase(found.begin() + i);
			}
		}
		sort_radius++;
	}
	return found_sorted;
}


vector<Biology::Position> Biology::get_nearby_terrain(int id, int radius, string terrain) {//can this somehow be merged fully or partially with get_nearby_organism?
	Organism* o = get_by_id(id);
	vector<Position> found;
	int min_y = o->position.y - radius;
	int max_y = o->position.y + radius;
	int min_x = o->position.x - radius;
	int max_x = o->position.x + radius;

	for (int r = min_y; r < max_y; r++) {
		for (int c = min_x;c < max_x;c++) {
			Environment::Tile* tile = environment->get_tile(c,r);
			if (tile==nullptr) { continue; }
			if (tile->terrain == "water") {
				found.push_back({ c,r });
			}
		}
	}

	vector<Position> found_sorted; //sorted by distance from searching organism
	int sort_radius = 0;
	while (found.size() > 0) {
		for (int i = found.size()-1; i > -1; i--) {
			if (abs(o->position.x - found[i].x) == sort_radius || abs(o->position.y - found[i].y) == sort_radius) {
				found_sorted.push_back(found[i]);
				found.erase(found.begin() + i);
			}
		}
		sort_radius++;
	}
	return found_sorted;
}


//utilizes o_it[0] row			problem with this function is that it's a random direction, needs a way to remember where it has already searched
bool Biology::move_to_new_search_space(int id, int search_range) {//called after a search fails to find desired target, moves the organism outside its original search range.
	Organism* o = get_by_id(id);
	if (o->species.mobility == "mobile") {}
	else { return false; }//default value for if organism does not have corresponding method in this function

	if (o->o_it[0][0] == 0) {//function initialization
		int rx = (rand() % (3)) - 1;//get random int between -1 and 1
		int ry = (rand() % (3)) - 1;
		if (rx == 0 && ry == 0) { rx++; }//prevents both rx and ry being 0 at the same time
		o->o_it[0][1] = o->position.x+(rx*search_range);//multiplies the random number by the original search radius in order to move out of the original search range
		o->o_it[0][2] = o->position.y+ (ry * search_range);
		o->o_it[0][0] = 1; //marks function as initialized
	}
	bool reached = move_to(id, { o->o_it[0][1], o->o_it[0][2] } );//move out of original search range, return true when reached
	if (reached) {//once out of range, reset function variables
		o->o_it[0][0] = 0;
		o->o_it[0][1] = 0;
		o->o_it[0][2] = 0;
	}
	return reached;
}


void Biology::delete_organism(int id) {//can this cause a memory leak?
	Organism* o = get_by_id(id);
	for (int i = 0; i < organisms[o->species.preset_index].size();i++) {
		if (organisms[o->species.preset_index][i].id == o->id) {
			environment->untie_from_tile(o->id, o->position.x, o->position.y);
			organisms[o->species.preset_index].erase(organisms[o->species.preset_index].begin()+i);
			return;
		}
	}
}


//utilizes o_it[1] row
void Biology::idle(int id) {//simply moves back and forth
	Organism* o = get_by_id(id);
	if (o->species.mobility == "mobile") {}
	else { return; }

	if (o->o_it[1][0] == 0) {
		move_to(id,{ o->position.x++, o->position.y});
		o->o_it[1][0] = 1;
	}
	else {
		move_to(id, { o->position.x--, o->position.y });
		o->o_it[1][0] = 1;
	}
}


void Biology::check_death(int id) {
	Organism* o = get_by_id(id);
	//check need based death conditions			exempt berrybushes for now, need to implement method for plants to obtain food/nutrients
	if (o->species.species_name != "berrybush" && o->needs_physiological.food.current_level == 0) {
		delete_organism(id); //temporary implementation, death should instead replace/convert organism into a corpse which decomposes.
	}
	if (o->age >= o->species.max_lifespan) {
		delete_organism(id);
	}
}

Biology::Organism* Biology::get_by_id(int id) {
	for (int i = 0; i < sizeof(organisms)/sizeof(vector<Organism>); i++) {
		for (int j = 0; j < organisms[i].size();j++) {
			if (organisms[i][j].id == id) {
				return &organisms[i][j];
			}
		}
	}
	return nullptr; // this shouldn't happen (not finding the organism by id), I don't know why it does, though in the future it may be possible that a not found is a valid result
}


/*------Need Satisfaction Utility Functions------------------------------------------------------------------------------------------------*/

void Biology::consume(int id, int food_id) {
	Organism* o = get_by_id(id);
	Organism* food = get_by_id(food_id);
	int calories = food->species.calories; //get the calories of the food item
	change_need_level(&o->needs_physiological.food, calories);//add calories to the consumer's food need level
	delete_organism(food_id);//destroy food
}

//ex: change_need_level(&organism.needs_physiological.food, 50); assuming the change_rate for food for this organism is 0.5, this increases level of food need by 25 percentage points (50*0.5), meaning it takes 400 food units to get to 100% food level
void Biology::change_need_level(Need* need, float change_amt) {
	need->current_level += (change_amt * need->change_rate);
	if (need->current_level > 100) { need->current_level = 100; } //max limits current_level to 100
	if (need->current_level < 0) { need->current_level = 0; } //min limits current_level to 0
}

void Biology::periodic_need_deterioration(int id) {//All needs that deteriorate over time such as hunger, thirst and sleep rather than do to specific events/contexts such as being harmed. 
	Organism* o = get_by_id(id);
	change_need_level(&o->needs_physiological.food, -1); //reduce food by 1 units per update
	change_need_level(&o->needs_physiological.water, -2); //reduce water by 2 units per update
	change_need_level(&o->needs_social.intimacy, -1); //reduce intimacy by 1 units per update

	//includes aging given it is akin to an unfillable need that reduces over time. Maybe it could even be implemented as a need, though that might be less efficient?
	o->age += 1 / 100; //for now to test, 1 year = 100 seconds (1:40 min:sec), so given humans have a liftime of 2 years, they'll die at 3:20 min
}


Biology::Position Biology::find_empty_tile(int id, int search_range) {
	Organism* o = get_by_id(id);
	int min_distance = 0; //radius of exclusion, as in tiles within this distance are not valid. This helps spread out organism. Unsure if this is the proper implementation or even if it should used.
	bool found = false;
	vector<Organism*> nearby_organisms = get_nearby_organisms(id, search_range, "all");
	if (nearby_organisms.size() == 0) { return { -1,-1 }; }//check empty
	
	for (int i = nearby_organisms.size()-1;i > -1; i--) {
		if (nearby_organisms[i]->species.species_name == "grass") {
			nearby_organisms.erase(nearby_organisms.begin()+i);//grass/moss/etc tiles count as empty (unless the reproducer is grass/etc), therefore remove from nearby organisms list
		}
	}
	if (nearby_organisms.size() == 0) { return { -1,-1 }; }//check empty after removing grass

	//if (nearby_organisms.size() == search_range * search_range-1/*-1 excludes own tile*/) { return {-1,-1}; }//no empty tile found	<-- this doesn't work correctly because nearby organisms can be in the same tile apart from grass, need to implement tile exclusivity between organisms with exemptions for grass, etc.
	for (int i = 0-search_range; i <= search_range; i++) {//finds first empty tile, no distance preference
		for (int j = 0-search_range; j <= search_range; j++) {
			for (int k = 0; k < nearby_organisms.size();k++) {
				if ((abs(j) <= min_distance && abs(i) <= min_distance) == false && nearby_organisms[k]->position.x != j && nearby_organisms[k]->position.y != i) {
					found = true;
				}
				else {
					found = false;
				}
			}
			if (found) { 
				if (o->position.x + j<0 || o->position.x + j>Environment::columns) { found = false; }//if the empty tile is out of bounds. This shouldn't happen, need to rewrite function to prevent the need for this check
				else if (o->position.y + i<0 || o->position.y + i>Environment::rows) { found = false; }
				else {
					return { o->position.x + j,o->position.y + i };
				}
				}//if this tile is empty, return this tile
		}
	}
	return {-1,-1};//no empty tile found		unsure if this line is reachable but may be needed in a later version of this method?
}




/*------Need Satisfaction Main Functions------------------------------------------------------------------------------------------------*/


bool Biology::satisfy_need_water(int id) {//these actions need to have some time cost associated to them not just instant consumption, animation is optional
	Organism* o = get_by_id(id);
	if (o->species.hydration_method == "find_water") {
		vector<Position> tmpPos_list = get_nearby_terrain(id, 5, "water");
		if (tmpPos_list.size()==0) { return false; }//case: water not found
		Position tmpPos = tmpPos_list[0];//get first element (nearest result)
		bool reached = move_to(id, tmpPos);
		int amt = 100; //for now, simply max fill the water need when water is obtained, later figure out how to decrease water source the same way calories are consumed from an organism being consumed
		if (reached) { change_need_level(&o->needs_physiological.water, amt); }
		return true;
	}
	return false;//default value for if organism does not have corresponding method in this function
}

bool Biology::satisfy_need_food(int id) {//methods include: hunting, gathering			need to add method of nondestructive consumption for consuming berrybush and for partial consumption of the target organism
	Organism* o = get_by_id(id);
	if (o->species.subsistence_method == "gather") {
		//find food; includes: search for it, go to known location, request known location, etc
		vector<Organism*> food_list = get_nearby_organisms(id, 5, "berrybush"); //need to expand this to include searching for items as well, currently only searches for nearest one of species
		if (food_list.size() == 0) { return false; }//case: food not found
		//acquire food; includes: grab it, kill it, buy it, ask for it, etc
		bool reached = move_to(id, food_list[0]->position);//might be better to move adjacent to target rather than the same tile?
		if (reached) { consume(id, food_list[0]->id); }
		return true;
	}
	return false;//default value for if organism does not have corresponding method in this function
}

//need to include various methods: live birth, egg, asexual, spores, seeds, etc
bool Biology::satisfy_need_intimacy(int id) {//need to control how many are created, for some reason too many berrybushes are created, more than on screen so they may be overlapping position
	Organism* o = get_by_id(id);
	Organism tmpOrganism;
	if (o->species.reproduction_method == "asexual_spores"){
		Position tmpPos = find_empty_tile(id,5);
		if (tmpPos.x == -1) { return false; }//no empty tile found
		tmpOrganism = { new_id(),species_presets[o->species.preset_index],tmpPos };

		//double check that the tile does not contain a copy of the same species, for some reason, find_empty_tile is not returning empty tiles and causing an explosion of berrybushes on the same tiles, I don't know why, this is a band aid
		Environment::Tile* tile = environment->get_tile(tmpPos.x, tmpPos.y);
		for (int i = 0; i < tile->tile_organisms_id.size(); i++) {
			Organism* tmpO = get_by_id(tile->tile_organisms_id[i]);
			if (tmpO == nullptr) { cout << "tile had id of nonexisting organism" << endl; return false; }//this should not happen, I don't know why it does, implemented this check to handle it
			if (tmpO->species.species_name == o->species.species_name) {
				return false;
			}
		}

		organisms[o->species.preset_index].push_back(tmpOrganism);//creates new organism within search_range tiles of originator    for some unknown reason, this is creating an excessive amount of new berrybushes that don't appear onscreen
		environment->tie_to_tile(tmpOrganism.id, tmpOrganism.position.x, tmpOrganism.position.y);
		change_need_level(&o->needs_social.intimacy, 100);
		return true;
	}
	//sexual_animal: find mate that also is searching for mate, move to the same tile, new organism is created. Implement pregnancy later.
	else if (o->species.reproduction_method=="sexual_animal") { //is this fine as if statements or is switch-case better?
		vector<Organism*> potential_mates = get_nearby_organisms(id,5, o->species.species_name);
		if (potential_mates.size() == 0) { return false; }
		for (int i = 0; i < potential_mates.size(); i++) {
			if (potential_mates[i]->sex != o->sex) {//selects first match
				bool reached = move_to(id, potential_mates[i]->position);
				if (reached) {
					change_need_level(&o->needs_social.intimacy, 100);
					if (o->sex == false) {//if female reaches location of male, births new organism
						tmpOrganism = { new_id(),species_presets[o->species.preset_index],o->position,(bool)(rand() % 2/*50/50 chance of male/female*/)};
						organisms[o->species.preset_index].push_back(tmpOrganism);
						environment->tie_to_tile(tmpOrganism.id, tmpOrganism.position.x, tmpOrganism.position.y);
					}
				}
				return reached;
			}
		}
		return false;
	}
	return false;//default value for if organism does not have corresponding method in this function
}







//next function to implement is death from lack of needs and old age. The goal is to create a stable simple ecosystem with simple behaviors and then implement a way for the player to interact with it.
/*------Biology Main Functions------------------------------------------------------------------------------------------------*/

void Biology::update(int id) {
	periodic_need_deterioration(id);
	Organism* o = get_by_id(id);
	if (o->needs_physiological.food.current_level < 80 && satisfy_need_food(id)) {}	//priority right now is a simple if-else, but it needs to be reorderable such that priority can change based on the need and current_levels as well as cost to fulfill such that if the npc is 1 step away from water, they finish getting water instead of going back for food if they get just a little hungry. This should be expanded to include finishing complex tasks, such as an organism that is on the hunt should not go back home in the middle of the hunt if avoidable.
	else if (o->needs_physiological.water.current_level < 80 && satisfy_need_water(id)) {}//these only trigger if the previous need did not find its target or the previous need level is high enough
	else if(o->needs_social.intimacy.current_level<50 && satisfy_need_intimacy(id)){}
	else{
		move_to_new_search_space(id,5); //if none of the above needs find their targets
	}
	idle(id); //idle function for if all needs are met
	check_death(id);//should this go at the start or end? Could it be merged with need_deterioration?
}

void Biology::update_all() {//moving this into the Biology class instead of running it in the Game class seems to have resolved the failed pass by reference error
	for (int i = 0; i < sizeof(organisms) / sizeof(vector<Organism>); i++) {
		//iterates in reverse order in case an element is deleted, to avoid skipping over an element. See: https://stackoverflow.com/a/63598736/22054183
		for (int j = organisms[i].size() - 1; j > -1; j--) {
			string tmpString = organisms[i][j].species.species_name;
			if (tmpString == "berrybush" || tmpString == "human") {
				update(organisms[i][j].id);
			}
		}
	}
}

