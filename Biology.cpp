#include "Biology.hpp"

using namespace std; 

vector<Biology::Organism> Biology::organisms;
Biology::radix Biology::o_root;
int Biology::id_iterator; 

Biology::Biology() {}
//Biology()						init
Biology::Biology(int a) {
	id_iterator = 0;
	Organism new_o;
	new_o = {new_id(1),1,0,0}; //place 1 human
	insert_o(new_o);
}
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
	it->o = o;
}
//done						simple move function
bool Biology::move_to(int id, int x, int y) {//return true if destination reached, else false
	Organism o = get_by_id(id);
	//check if destination is out of bounds
	if (x > Environment::columns) { x = Environment::columns; }
	else if (x < 0) { x = 0; }
	if (y > Environment::rows) { y = Environment::rows; }
	else if (y < 0) { y = 0; }
	//untie from tile
	Environment::Tile* t = &Environment::map[o.y][o.x];
	for (int i = 0; i < t->organism_id.size(); i++) {
		if (t->organism_id[i] == id) {
			t->organism_id.erase(t->organism_id.begin() + i);
			break;
		}
	}
	//change organism's location
	int old_x = o.x;
	int old_y = o.y;
	if (x > o.x) { o.x++; }
	else if (x < o.x) { o.x--; }
	if (y > o.y) { o.y++; }
	else if (y < o.y) { o.y--; }
	//tie to new tile
	Environment::map[o.y][o.x].organism_id.push_back(id);
	
	//return
	insert_o(o);
	if (x == o.x && y == o.y) {
		return true;
	}
	else {
		return false;
	}
}
//death()						handles if and when ann organism dies and deterioration of the corpse
bool Biology::death(int id) {
	Organism o = get_by_id(id);
	//if(o.alive==false){decompose corpse}
	//if(done_decomposing){delete organism object from radix tree}
	//ex: bool death_condition_1 = a == true || b == false;
	//ex: if(death_condition_1 || death_condition_2){o.alive==false;}
	return true;//if dead
}
//birth()						create new organism, allows options for specific contexts
void Biology::birth(int mother_id, int father_id) {

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
Biology::return_vars Biology::find(int id, string target_type, string target, int search_radius) {
	return_vars r;
	Organism o = get_by_id(id);
	//gets list of all tiles within search_radius, sorted by distance to search origin. Iterates in rings in an outward direction.
	vector<Environment::Tile> search_space;
	for (int tmp_radius = 0; tmp_radius <= search_radius; tmp_radius++) {
		int min_x = o.x - tmp_radius;
		int max_x = o.x + tmp_radius;
		int min_y = o.y - tmp_radius;
		int max_y = o.y + tmp_radius;
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
	vector<Organism> found_o;
	for (int i = 0; i < search_space.size(); i++) {
		if (target_type == "terrain") {
			if (search_space[i].terrain == target) {
				found_t.push_back(search_space[i]);
			}
			r.r_tile = found_t;
			return r;
		}
		else if (target_type == "species") {
			bool all = false;
			if (target == "all") { all = true; }
			for (int j = 0; j < search_space[i].organism_id.size(); j++) {
				Organism tmp_o = get_by_id(search_space[i].organism_id[j]);
				if (all || get_species(tmp_o.organism_id).species_name == target && o.organism_id!=tmp_o.organism_id) {
					found_o.push_back(tmp_o);
				}
			}
			r.r_organism = found_o;
			return r;
		}
	}
}
//satisfy_needs()				sorts needs by priority, iterates over all needs attempting to fill them
void Biology::satisfy_needs(int id) {
	Organism o = get_by_id(id);
	int top_priority = 0;
	int need_index=0;
	for (int i = 0; i < sizeof(o.needs) / sizeof(Need); i++) {
		if (o.needs[i].priority > top_priority) { top_priority = o.needs[i].priority; need_index = i; }
	}
	//get need name
	string need = o.needs[need_index].need_name;
	if(need=="food"){
		//search nearby for organisms or items that match diet
		//according to nearest result, choose/use corresponding method (gather, solo hunt, pack hunt, etc)
	}
	if (need == "water") {}
//	if (need == "") {
// 	   //find path/target to satisfy need
//	   //choose method according to target/path
// }
//	if (need == "") {}
//	if (need == "") {}
}
//carry()						pick up or drop item
//fight()						cause damage to another organism
//periodic()					all periodic changes such as need deterioration should be here
void Biology::periodic(int id) {

}
//context()						a listener that checks the organism"s state and immediate surroundings to respond to things like taking damage or the appearance of a threat
void Biology::context(int id) {

}
//get_by_id()					returns organism
Biology::Organism Biology::get_by_id(int id) {
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
	return *it->o;
}

//get_species()					gets corresponding species, used to avoid holding a copy per organism without using pointers
Biology::Species Biology::get_species(int species_id) {
	for (int i = 0; i < number_of_species; i++) {
		if (species_id == species[i].species_id) {
			return species[i];
		}
	}
}


void Biology::update(int id) {

}
void Biology::update_all() {
	move_to(1, 10, 10);
}



