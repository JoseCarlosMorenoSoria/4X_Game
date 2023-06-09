#include "Biology.hpp"

using namespace std;

Biology::Biology(){}

Biology::Biology(Environment* env) {
	//recieve game's environment reference
	environment = env;

	//instantiate organisms

	//grass and the like first
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 40; j++) {
			organisms.push_back({new_id(), Biology::grass, j, i});
		}
	}

	for(int i=0;i<3;i++){organisms.push_back({new_id(), Biology::human,{rand()%Environment::columns, rand()%Environment::rows}}); }
	for(int i=0;i<3;i++){organisms.push_back({new_id(), Biology::deer,{rand()%Environment::columns, rand()%Environment::rows}});}
	for(int i=0;i<15;i++){organisms.push_back({new_id(), Biology::tree,{rand()%Environment::columns, rand()%Environment::rows}});}
	for(int i=0;i<30;i++){organisms.push_back({new_id(), Biology::berrybush,{rand()%Environment::columns, rand()%Environment::rows}});}
}

Biology::~Biology() {

}



/*------Utility Functions------------------------------------------------------------------------------------------------*/

int Biology::new_id() {
	int tmp = id_iterator;
	id_iterator++;
	return tmp;
}

bool Biology::move_to(Organism* o, Position p) {//needed to use pointers, therefore look into smart pointers to prevent memory leaks, reassigning a pointer creates leaks
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

	if (o->position.x > p.x) { o->position.x--; }//once collisions are implemented, will need to add behavior for going around impassable objects
	else if (o->position.x < p.x) { o->position.x++; }
	if (o->position.y > p.y) { o->position.y--; }
	else if (o->position.y < p.y) { o->position.y++; }
	//handles hitting the edges of the map		might be redundant with ensuring target location is on the map
	if (o->position.x < 0) { o->position.x = 0; }
	else if (o->position.x > Environment::columns - 1) { o->position.x = Environment::columns - 1; }//should this be columns-1 or columns? likewise for the rows below
	if (o->position.y < 0) { o->position.y = 0; }
	else if (o->position.y > Environment::rows - 1) { o->position.y = Environment::rows - 1; }

	if (o->position.x == p.x && o->position.y == p.y) { return true; }
	return false;
}


Biology::Organism* Biology::search_for_species(Organism* o, string species) {
	for (int i = 0; i < Biology::organisms.size();i++) { //it's not the nearest, just the first match within range
		if (Biology::organisms[i].species.species_name == species && abs(Biology::organisms[i].position.y - o->position.y) < 5 && abs(Biology::organisms[i].position.x - o->position.x) < 5)//true if found match within 5 tiles
		{
			return &Biology::organisms[i];
		}
	}
	Organism* notFound = nullptr;
	return notFound;
}

Biology::Position Biology::search_for_terrain(Organism* o, string terrain) {//iterator indices = 0,1,2
	for (int r = 0; r < Environment::rows; r++) {
		for (int c = 0;c < Environment::columns;c++) {
			if (environment->map[r][c] == 1 && abs(r-o->position.y)<5 && abs(c-o->position.x)<5)//true if found match within 5 tiles, it's not the nearest, just the first match within range
			{
				Position found = { c,r }; 
				//o->o_it[0] = 0; 
				return found;
			} //check if you can define object in the return line such as return{r,c}; Remember that Position is x,y but arrays are y,x
		}
	}
	//if (o->o_it[0] > 5) {//resets direction on having moved 5 tiles
	//	o->o_it[1] = ((rand() % (3)) - 1);//random x
	//	o->o_it[2] = ((rand() % (3)) - 1);//random y
	//	o->o_it[0] = 0; 
	//	if (o->o_it[1] == 0 && o->o_it[2] == 0) { o->o_it[1] = 1; }//prevents non-movement
	//}
	//Position notFound = { o->position.x+ o->o_it[1],o->position.y+ o->o_it[2]};//moves 1 step in random direction if not found
	Position notFound = { -1,-1 };
	//o->o_it[0]++;
	return notFound;
}

//utilizes o_it[0] row			problem with this function is that it's a random direction, needs a way to remember where it has already searched
bool Biology::move_to_new_search_space(Organism* o) {//called after a search fails to find desired target, moves the organism outside its original search range.
	int search_range = 5;
	if (o->o_it[0][0] == 0) {//function initialization
		int rx = (rand() % (3)) - 1;//get random int between -1 and 1
		int ry = (rand() % (3)) - 1;
		if (rx == 0 && ry == 0) { rx++; }//prevents both rx and ry being 0 at the same time
		o->o_it[0][1] = o->position.x+(rx*search_range);//multiplies the random number by the original search radius in order to move out of the original search range
		o->o_it[0][2] = o->position.y+ (ry * search_range);
		o->o_it[0][0] = 1; //marks function as initialized
	}
	bool reached = move_to(o, { o->o_it[0][1], o->o_it[0][2] } );//move out of original search range, return true when reached
	if (reached) {//once out of range, reset function variables
		o->o_it[0][0] = 0;
		o->o_it[0][1] = 0;
		o->o_it[0][2] = 0;
	}
	return reached;
}


void Biology::delete_organism(Organism* o) {//can this cause a memory leak?
	for (int i = 0; i < Biology::organisms.size();i++) { //is Biology:: neccessary before organisms? Might no be.
		if (Biology::organisms[i].id == o->id) {
			Biology::organisms.erase(Biology::organisms.begin()+i);
			return;
		}
	}
}

//utilizes o_it[1] row
void Biology::idle(Organism* o) {//simply moves back and forth
	if (o->o_it[1][0] == 0) {
		move_to(o,{ o->position.x++, o->position.y});
		o->o_it[1][0] = 1;
	}
	else {
		move_to(o, { o->position.x--, o->position.y });
		o->o_it[1][0] = 1;
	}
}




/*------Need Satisfaction Utility Functions------------------------------------------------------------------------------------------------*/

void Biology::consume(Organism* o, Organism* food) {
	int calories = food->species.calories; //get the calories of the food item
	change_need_level(&o->needs_physiological.food, calories);//add calories to the consumer's food need level
	delete_organism(food);//destroy food
}

//ex: change_need_level(&organism.needs_physiological.food, 50); assuming the change_rate for food for this organism is 0.5, this increases level of food need by 25 percentage points (50*0.5), meaning it takes 400 food units to get to 100% food level
void Biology::change_need_level(Need* need, float change_amt) {
	need->current_level += (change_amt * need->change_rate);
	if (need->current_level > 100) { need->current_level = 100; } //max limits current_level to 100
	if (need->current_level < 0) { need->current_level = 0; } //min limits current_level to 0
}

void Biology::periodic_need_deterioration(Organism* o) {//All needs that deteriorate over time such as hunger, thirst and sleep rather than do to specific events/contexts such as being harmed. 
	change_need_level(&o->needs_physiological.food, -1); //reduce food by 1 units per update
	change_need_level(&o->needs_physiological.water, -2); //reduce water by 2 units per update
}






/*------Need Satisfaction Main Functions------------------------------------------------------------------------------------------------*/


bool Biology::satisfy_need_water(Organism* o) {//these actions need to have some time cost associated to them not just instant consumption, animation is optional
	Position tmpPos = search_for_terrain(o, "water");
	if (tmpPos.x == -1) { return false; }//case: water not found
	bool reached = move_to(o, tmpPos);
	int amt = 100; //for now, simply max fill the water need when water is obtained, later figure out how to decrease water source the same way calories are consumed from an organism being consumed
	if (reached) { change_need_level(&o->needs_physiological.water, amt); }
	return true;
}

bool Biology::satisfy_need_food(Organism* o) {//methods include: hunting, gathering			iterator indices = 3,4,5
	//find food; includes: search for it, go to known location, request known location, etc
	Organism* food = search_for_species(o, "berrybush"); //need to expand this to include searching for items as well, currently only searches for nearest one of species
	if (food == nullptr) {
		//random x and y
		//if (o->o_it[3] > 5) {//resets direction on having moved 5 tiles
		//	o->o_it[4] = ((rand() % (3)) - 1);//random x
		//	o->o_it[5] = ((rand() % (3)) - 1);//random y
		//	o->o_it[3] = 0;
		//	if (o->o_it[4] == 0 && o->o_it[5] == 0) { o->o_it[4] = 1; }//prevents non-movement
		//}
		//move_to(o,{o->position.x+ o->o_it[4],o->position.y+ o->o_it[5]});
		return false; }//case: food not found, therefore moves 1 step in a random direction
	//o->o_it[3] = 0;//reset iterator
	//acquire food; includes: grab it, kill it, buy it, ask for it, etc
	bool reached = move_to(o, food->position);//might be better to move adjacent to target rather than the same tile?
	if (reached) { consume(o, food); }
	return true;
}









/*------Biology Main Functions------------------------------------------------------------------------------------------------*/

int flag = false;//<-- this is a problem becuase it is not instance (organism) specific
void Biology::update(Organism* o) {
	periodic_need_deterioration(o);
	if (o->needs_physiological.food.current_level < 80 && satisfy_need_food(o)) {}	//priority right now is a simple if-else, but it needs to be reorderable such that priority can change based on the need and current_levels as well as cost to fulfill such that if the npc is 1 step away from water, they finish getting water instead of going back for food if they get just a little hungry
	else if (o->needs_physiological.water.current_level < 80 && satisfy_need_water(o)) {}
	else {
		move_to_new_search_space(o); //if none of the above needs find their targets
	}
	idle(o);//idle function for if all needs are met
}


