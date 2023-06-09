//all pseudo_X.cpp files are simply some pseudocode to plan/brainstorm how the code will be structured/work.
#include <string>
#include <iostream>
using namespace std;


struct Structural {//buildings/aquaducts/etc anything that is built/architectural
	int pos_x;
	int pos_y;
	int pos_z;
	string type = ""; //room with a role, functional structure, or symbolic structure. Rooms with roles can be repurposed. 
	string structure_name = ""; //house, storeroom, watermill, stele, bridge, etc. 
	string blueprint = ""; //the blueprint of the structure (size and shape of house, materials, style, etc)
	string structure_state = ""; //the parts of the structure that are complete given that a building might be unfinished or damaged/deteriorated. 
};


//these structs below are just items, they could be merged into an Item struct.
struct Item {
	int pos_x;
	int pos_y;
	int pos_z;
	int weight; //affects things like carry weight, throwable, etc.
	int size; //affects things like can be carried, can be stored in pockets/bag, etc
};

struct Tools {
	string name;
	string material;
	string quality; //quality and condition of tool, novice quality/worn out. Tools like other items have lifespans. 
};

struct Weapon {
	int damage_cut;
	int damage_punture; //spear stab or arrow/bullet penetration strength at point blank range
	int damage_blunt;
	string name;
	string type; //spear/sword/mace/bow
	string melee_ranged; //is it melee or ranged?
	int range; //projectile strength decreases with distance travelled.
	string material;
};

struct Armor {//damage taken = damage-defense, armor deteriorates when it is hit, so multiple hits might eventually break through armor.
	int defense_cut;
	int defense_punture;
	int defense_blunt;
	string name;
	string type; //helmet, cuirass, greaves, etc.
	string material;
};

struct Material {
	string name;
	string deterioration_rate;
	string strength;
};

/*
* Smithing:
Station/Furniture:
Machine:


Energy Source:
Agricultural:
Animal use:
Knowledge:

Clothing: 
*/




/*
* Political	political maps determined by most dominant group, judged particularly with monopoly on force
Government:	Organization:
	Decision Making:
	Govt. Powers: 
	Rights and Duties:
	Jurisdiction:
	Insitutions:
	Crimes: 

	Social:
Religious:
Subsistence:
Economic:
*/



/*
* Military
Tactics:
Operations:
Strategy:
System:
Political Aims:
Casus Belli:
seasonal/extended campaigns
*/