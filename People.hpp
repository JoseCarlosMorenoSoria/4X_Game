#ifndef People_hpp
#define People_hpp
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class People {
public:
	People();//default constructor, do not use
	People(int a);

	struct PersonalRelations {
		int other_person_id;
		vector<string> relation_type;//brother/friend/coworker/etc might be more than one, ex: a brother can also be a coworker.
		int relationship_strength; //decreases periodically, increases everytime there's an interaction. Some interactions/relations might set strength high enough to survive lengths without interactions.
		int opinion=0; //0 is neutral opinion. High is positive opinion (lover, friend, like), low is negative opinion (enemy, rival, dislike). Range bounded: -100 to 100
	};

	struct Group {
		int group_name;//a group has no idea, only a name, because groups exist only in the heads of individuals and can vary between people. Same way cultures can drift, groups can have their definitions drift.
		string type;//religious, political, family, functional, etc.
		vector<string> definition;//group definition, list contains tags to be parsed by a function to determine who is and isn't a member, purpose of the group, etc.

		vector<string> relation_type;//employee/owner/member/not member/etc		It is possible to be a member of a group one hates such as one's workplace or some imposed identity.
		int relationship_strength; //decreases periodically, increases everytime there's an interaction. Some interactions/relations might set strength high enough to survive lengths without interactions.
		int opinion = 0; //0 is neutral opinion. High is positive opinion (like), low is negative opinion (dislike). Range bounded: -100 to 100
	};

	struct Skill {//allows new and improved actions, improved through practice, lost through disuse.
		int skill_id;
		int skill_name;
		int skill_level; //0-10 range (0-5 might be better?)
	};
	/* Skills:
	* Crafting (hands/creation):
	* * Smithing
	* * * Material - stone, wood, bone, metal, wicker, etc
	* * * Item - weapon (spear, atlatl, sword, etc), tool (hammer, tongs, knife, etc)
	* * Art
	* * Building (buildings, structures, fortifications, boats, carts)
	* * * Material - sod, straw, mud, brick, stone, logs, planks, etc
	* * * Structure - hut/house, wall, pallisade, foundation, aquaduct, sewer, tunnel, etc
	* 
	* Social (speech/influence):
	* * Persuasion
	* * Deception
	* * Intimidation
	* * Consolation
	* * People reading (knowing their motivations/feelings)
	* * Inspiration
	* 
	* Intellectual (mind/knowledge):
	* * Medicine
	* * Engineering - mechanical, structural
	* * Administration? Command?
	* * Writing
	* * Astronomy (timekeeping and navigation)
	* * Religious knowledge (correct rituals, traditions, rules, augury)
	* * History (story keeping and transmission)
	* * Horticulture (small scale, finnicky plants, herbalist)
	* 
	* Athletic (physical/movement):
	* * Resource extraction - tree felling, mining
	* * Agriculture ("large" scale, crops) - wheat, rice, barley, maize, potatoes
	* * Combat - melee, ranged
	*/

	struct Person {
		int organism_id; //human as animal
		int person_id;//might be redundant with organism id, but could also be used for encoding info
		string person_name;
		vector<PersonalRelations> p_relations;//limit size to 50? 150? people. Weak relationships forgotten first. 
		vector<Skill> skills;
	};

	void change_skill(Person* p, int skill_id);//handles if a skill is learned or improved and lost or deteriorated. 
	void change_opinion(Person* p, int amt);//bounds opinion between -100 and 100
	void new_id();//person_id
	void new_group();//group formation. Checks first, attempts to form, if successful form new group
	void mind_birth();//a person is created not at actual birth, but when the human is no longer an infant or toddler. This is when they start speaking and therefore engaging in social relations as a person. Also reduces unnecessary memory usage when infant mortality is high.
	void communication();//handles and contains human interactions regarding communication. Chatting, insults, questions, orders, gossip, etc.
	//need way for Biology functions to send info to this file to influence relationships if say someone steals someone else's food, etc. Biology must include People not vice versa.
};


//humans build buildings, grow crops, hunt and gather resources, engage in rituals and socialization, compete cooperatively over resources and influence, wage war, create social structures to define roles, settle disputes, etc.


#endif