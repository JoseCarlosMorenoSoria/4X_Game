//all pseudo_X.cpp files are simply some pseudocode to plan/brainstorm how the code will be structured/work.
#include <string>
#include <iostream>
using namespace std;


//This can be divided into 2 parts, the player as npc and the player as UI

struct Player {
	string organism_id; //this is the id of the player's character which can access both the Biological struct and Person struct 
};

//autopilot actions of the player character are just default NPC AI

//All other NPC AI needs to be overloaded or overridden with a player version that responds to player input rather than AI.

//Player as UI is access to things like an ingame notepad, map with related markers/views, planning tools for battles/wars/trade/exploration/building
// /etc, displays for every action so that all options are visible and comparable, save game/load game, menu, game tips/manual, etc.
//is about exposing the data to the player.

//The player can choose heirs, and controls others / shapes the world through navigating human relationships including making the right allies and 
//enemies and climbing ranks, etc. The player's character also has its own personality and it plays similar to CK3 where if the player makes decisions 
//against that character's personality, it causes stress and high stress causes penalties, so as to encourage role play. 
