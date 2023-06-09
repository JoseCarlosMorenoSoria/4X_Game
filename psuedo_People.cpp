//all pseudo_X.cpp files are simply some pseudocode to plan/brainstorm how the code will be structured/work.
#include <string>
#include <iostream>
using namespace std;



struct Information {//x r y <-- x is in r relation with y    information must be held by a person/book or else is erased.  Information requires a creation event such as a person walking past a tree creates the information "tree at x location"
	string x = "";
	string r = "";
	string y = "";
	//x, y types:
	// Individual, Role (cop, priest, etc), Item, Skill, Knowledge, Land
	//r types: relations that can be derived are not stored, so a sibling is not stored, instead to find sibling one must look at the children of one's parents or compare if they have the same parents
	//Social relations: is parent to (doubles as is child to), has authority over (doubles as is subordinate to), is lover to		<-- certain relations might be better "hard coded" rather than left open to the x r y format, for example x is parent of y should be "hard coded"
	//^things like "has authority over" are contextual and so need additional tags such as what orgnaization/circumstances x has authority over y. 
	//Property: is, contains, owns, knows, is at position, claims      <-- if the relations are finite, which they should be, it might make more sense to have each relation be a separate array so as to make searching all knowledge faster (though there searching should be kept to minimum anyway)
	//^something like "is at position" might be better held as the id of the object/individual with a tag for what is known about it, can be applied to other things such as knowing the name of a person by holding the id of the person and a tag that their name is known, may not apply sometimes.
	//^ownership is also something that has modifiers such as rent/exclusive/shared/borrowed/etc
	//Potential: can, promised to, might, buys, sells
	//Desires: wants, likes, dislikes, fears
	//^ may need an additional tag to hold degree, for example like/dislike should be a number tying x to y and apply to items, people, events, states, etc. 
	//History: did, had, was, said   <-- might be better as a past date added to a piece of information?
	//Path: is reachable by path, 
};
//use vectors instead of arrays
Information Social_Relation[];
Information Property[];
Information Potential[];
Information Desires[];
Information History[];
Information Path[];

struct Motivations { //ontop of maslow's
	//achieve x state
	//personal achievement (status/trait/relation, follow maslows hierarchy)
	//achievement for others (protect x, destroy x, make x achieve y)
	//contextual/personality motivation (if x observed then do y, ex: if a curious npc sees something out of place, investigate until probable cause found)
};


//all that can be known is kept in a global repository (which will need its own forgetting routine to cap amount held)
//an individual does not hold a copy of every bit of knowledge, instead they hold an id for each bit of knowledge, therefore if someone knows that x is the parent of y, they simply hold the id to that info. 
//This both reduces repetition and also facilitates learning and forgetting information and prevents knowing things that an individual shouldn't know, as well as the potential to learn/spread lies without others knowing it's a lie.
//for example, an individual might not know who their parents are because that information isn't learned until they are a certain age but they were orphaned/kidnapped before then.
//this allows a lot more potential and flexibility with organic personal stories, etc. 
struct Knowledge {//includes memory, relations, ownership, goals/paths/etc. must be capped by forgetting less important things
	//will be an array (use vectors, never arrays) with markers for priority so that low priorities get forgotten, array is of tuples such as (x, "brother of", y) or ("food", "at", position)
};

struct Personality { // the Big 5 traits are on a scale of -1 to 1
	double openness = 0;//openness to experience (inventive/curious vs. consistent/cautious)
	double conscientiousness = 0;//conscientiousness (efficient/organized vs. extravagant/careless)
	double extraversion = 0;//extraversion (outgoing/energetic vs. solitary/reserved)
	double agreeableness = 0;//agreeableness (friendly/compassionate vs. critical/rational)
	double neuroticism = 0;//neuroticism (sensitive/nervous vs. resilient/confident)
};

struct Person {
	string organism_id = ""; //individual's id to tie it with corresponding organism struct, human as animal
	Knowledge knowledge; //what the person knows
	string name = "";
	Motivations motivations;
//	string Skills[]; //make a vector of strings, might need to be tuples/struct (skill_name, skill_level)
//	string culture_id[]; //a vector of the id's for this individual's cultures - might need some way to reconcile differences between cultures, for example if an American is culturally "rude" but the individual is also a Mormon which is "nice", then which one takes priority?
	Personality personality;
};

//Groups - this encompasses everything from political units, demographics?, factions, states, etc.
//There might be some groups that shouldn't be groups, for example demographics is too unstructured, etc to count. Groups based on traits/pure labels should be handled differently.
//remember that groups don't actually exist, rather individuals form specific relations with each other under a group label, this group label may have group specific info such as org type
//a group is handled as an agent only to make things simpler to implement but maybe that separation should be limited to better reflect the importance of individuals as the true agents and groups are only somewhat like emergent behavior
struct Group {
//	string Members[]; //make as a vector, holds organism_id of every person who is a member   - error is maybe because it's an array without a size, don't know why the rest don't have an error
//	string Composition[]; //a vector of tuples that determine who is/isn't a member or can/can't become one. Ex: [("includes", "initiated members"),("excludes","people who like french fries"),("excludes","members of other countries")]
	string Structure; //need to create a list of structures for groups (formal, informal, no structure, corporate, co-op, voluntarist, etc), includes positions/offices and their powers/jurisdictions/routines/etc such as president, CEO, leader, etc. May need to be a dedicated struct. Also who holds the positions currently.
	string Type; //state, military, religious, national/ethnic/cultural, administrative, commercial, clan, family, ideological, occupation, status (nobility?), trait?, coalitional (common goal)
	string Defined_By; //goal defined (common motivation) or tribe defined (simple differentiation with an outgroup)
	string Growth; //type/method of growth, is it insular or actively recruiting? Forced joining or voluntarist?
	string Democratic_Autocratic_Ratio; //a 3-tuple ratio (interchangeables (nominal selectorate), influentials (real selectorate), essentials (winning coalition))
};

//Group Creation (functions) - the conditions and methods in which a group is formed
//Recruitment	Imposition	familiarity/similarity triggered (excarbated by resource/political competition)	goal triggered (coalition building)

//Group Behavior (functions)
//To survive in this political system of interchangeables, influentials, and essentials, leaders must follow five rules to rule by. These five rules are: keep the coalition as small as possible, expand the set of interchangeables, take control of the treasury, reward essentials at all costs to stay in power, and do not take from the essentials to give to the everyday people.
//Coordination	Communication	Assignments	Rewards/Punishments	Protocols/Behavior



//Culture - cultures are shared and individuals can independently drift culturally, therefore all cultures arer held in a global repository and when an individual drifts culturally or combination of culture, they create a new culture entry. Individuals hold a culture entry's id. This also means there has to be a forgetting function to remove cultures no longer needed (not held by a: person, book, artifact, memory, etc)
struct Culture {
	string culture_id;//for this specific version of this culture
	string type; //belief/philosophy/religion/language/art/architecture/food/music/clothes/ceramics/other material/traditions/rituals/values?/funerary customs/gender roles/coming of age/etc
	string traits[]; //specific traits of this culture type, might make more sense to separate the Culture struct into structs of each culture type, especially for something like religion
};


//Culture Spread and Drift (functions)
//religion/philosophy/language/culture/etc reinforces itself through contact with others who have the same, but changes over time such that if a group is split for a long time, those changes will add up until both groups are different, rate of change can be modified by books and enforcers (institution/individuals)






//Behavior (functions)
//individual behavior
//competitive behavior
//cooperative behavior
//personality/trait/etc affected behavior
//proactive
//reactive
//create
//destroy
//change
//move
//communicate (teach/share/request)
//job/role (soldier/carpenter/farmer/father/etc)


//Skills: (functions, ex: new_item = craft(smith, condition, skill_level, ingredients); condition is "be near forge")
	//_Behavioral: 
	// __Speech: persuasion, intimidation, deceit, inspiration, charm
	// __Combat: melee, ranged, tactic_x
	// __Tool_Use: weapon_x, tool_x, station_x (forge, stove, etc)
	//_Crafting: make_x_item_type (smithing, carpentry, pottery, etc), build_x