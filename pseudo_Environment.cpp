//all pseudo_X.cpp files are simply some pseudocode to plan/brainstorm how the code will be structured/work.
#include <string>
#include <iostream>
using namespace std;


//add day/night cycle and 24hr day. Length of day is affected by both seasons and lattitude. 


struct Tiles {//holds terrain info for individual tiles
	bool isPlateBoundary = false; //for drawing tectonic plate lines, this is the marker that gets "drawn".		tectoninc plates might make more sense as their own map overlay instead of as part of a tile/world map
	bool isPlateIntersection = false; //for the destination points when drawing plate lines
	string belongsToPlate = ""; //name of tectonic plate this tile belongs to.
	string plateBoundaryType = ""; //convergent, divergent, transform
	string isHotSpot = ""; //"no","active","old" <-- this helps mark random volcanoes and their corresponding mountain/island chains

	string Terrain = ""; //water, dirt, stone, etc
};
string Plates = ""; //is 3 tuples that hold all tectonic plates: (plateName, plateSize, plateType) where size is number of tiles and type is oceanic or continental
//Tiles WorldMap[x][y][z]; //the world map that for each tile holds the type such as water, dirt, stone, etc. x,y,z are world coordinates. 

/*
* Topology
when terrain currents and water cycle are finished then simulate long term erosion (glacial, wind, water, includes caves)
*/

//tectonic plates - start at an intial point on the map, draw an uneven (shifts sideways but always forward) line towards 3 random points on the map,
//     when a line reaches the point it splits into 2 lines going to 2 new points. If a line hits an existing line, then that point replaces the old 
// destination point, if a line hits within a small range of an existing intersection then the line endpoint shifts to just out of range on the larger 
//line to its left or right. The idea is to end up with plates where every intersection is of exactly 3 lines. 
//Remember that depending on map implementation, lines may wrap around the map. This mostly ignores the vertical aspect of a map, so it should be held either in a separate 2D map overlay or in a designated z level.


//identify created plates and boundaries, assigning them names/ids and determining their sizes. Then sort them by size and assign the largest as oceanic, if this size
//is less than desired ocean size, assign the next largest plate as oceanic, repeat until total oceanic size is desired size (which is less than desired ocean size). 
//assign a direction to each plate and assign boundary types in accordance such that if 2 plates are moving in the same direction their boundary is convergent, etc.

//create a set number of hot spots, each hot spot has a short random uneven line in any direction to mark where it's old path so as to create mountian/island chains (islands are just mountains/volcanoes that reach above the ocean surface)

//create the corresponding features of plate boundaries, so convergent lines have mountains and volcanoes and divergent line have rift valley and trenches, whether it is continental vs continental or oceanic vs continental, or oceanic vs oceanic matters for what features are made.
//these features then get further specified (active/dormant and cone/dome/etc volano), (shape/type of mountain/mountain range, valley/trench/etc)

//randomly mark tiles from the borders of continental plates expanding inward as continental shelf tiles until desired total ocean size is reached. Sea level is therefore a set max height above this shelf.

//use noise? algorithms to generate topology with corresponding constraints such as the oceanic floor being lower than the continental shelf which is lower than the continents/surface land




/* Terrain
Fill the oceans with salt water upto sea level, according to topology and volcanoes fill with terrain types (sand/soil/stone/etc), after water cycle 
and temp currents assign terrain types again.


* Currents
According to latitudes and topology assign currents for wind and oceans


* Water Cycle
According to currents simulate water cycle which then generates clouds, rain, snow, ice, lakes, rivers, aquafiers and springs wherever water flows 
with local temperature (from latitude+season+currents+cloud cover) affecting evaporation/condesnation and melt/freeze rate.


* Events
According to currents, current temperatures, and clouds/humidity then have chance of tornadoes, thunder and lightning, hurricanes, water spouts, 
sand/dust storms, etc.
*/

