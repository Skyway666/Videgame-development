#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"

// TODO 2: Create a struct to hold information for a TileSet
// Ignore Terrain Types and Tile Types for now, but we want the image!
// ----------------------------------------------------

enum orientation
{
	orthogonal = 0,
	isometric,
	staggered,
	hexagonal
    
};

enum render_order
{
    right_down = 0,
	right_up,
	left_down,
	left_up
};

struct image
{
	const char* source;
	uint width;
	uint height;
};

struct Map_node
{
	float map_version;
	orientation orientation;
	render_order renderorder;
	uint width;
	uint height;
	uint tilewidth;
	uint tileheight;
	int nextobjectid;
	int tilesets;
};

struct Tileset
{
	uint firstid;
	const char* name;
	uint tilewidth;
	uint tileheight;
	uint spacing;
	uint margin;
	image image;
};

struct Layer
{
	const char* name;
	unsigned int* data;
	int width;
	int height;
};
// TODO 1: Create a struct needed to hold the information to Map node


// ----------------------------------------------------
class j1Map : public j1Module
{
public:

	j1Map();

	// Destructor
	virtual ~j1Map();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called each loop iteration
	void Draw();

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load(const char* path);

	void Fill_All_Map_Data(const pugi::xml_node& node);

	void Fill_All_Tiles(const pugi::xml_node& node);

	void Fill_All_Layers(const pugi::xml_node& node);

private:


public:

	Map_node map;
    p2List<Tileset>* tile_array = new p2List<Tileset>;
	p2List<Layer>* layer_array = new p2List<Layer>;
 	// TODO 1: Add your struct for map info as public for now

private:
	
	pugi::xml_document	map_file;
	p2SString			folder;
	bool				map_loaded;
};

#endif // __j1MAP_H__