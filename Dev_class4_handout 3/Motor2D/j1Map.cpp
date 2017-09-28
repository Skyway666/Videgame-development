#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include <math.h>

j1Map::j1Map() : j1Module(), map_loaded(false)
{
	name.create("map");
}

// Destructor
j1Map::~j1Map()
{}

// Called before render is available
bool j1Map::Awake(pugi::xml_node& config)
{
	LOG("Loading Map Parser");
	bool ret = true;

	folder.create(config.child("folder").child_value());

	return ret;
}

void j1Map::Draw()
{
	if(map_loaded == false)
		return;

	// TODO 6: Iterate all tilesets and draw all their 
	// images in 0,0 (you should have only one tileset for now)

}

// Called before quitting
bool j1Map::CleanUp()
{
	LOG("Unloading map");

	// TODO 2: Make sure you clean up any memory allocated
	// from tilesets / map
	delete[] tile_array;

	map_file.reset();

	return true;
}

// Load new map
bool j1Map::Load(const char* file_name)
{
	bool ret = true;
	p2SString tmp("%s%s", folder.GetString(), file_name);

	pugi::xml_parse_result result = map_file.load_file(tmp.GetString());

	if(result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		ret = false;
	}

	if(ret == true)
	{
		// TODO 3: Create and call a private function to load and fill
		// all your map data
		Fill_All_Map_Data(map_file);
	}

	// TODO 4: Create and call a private function to load a tileset
	// remember to support more any number of tilesets!
	

	if(ret == true)
	{
		// TODO 5: LOG all the data loaded
		// iterate all tilesets and LOG everything
	}

	map_loaded = ret;

	return ret;
}

void j1Map::Fill_All_Map_Data(const pugi::xml_node& node)
{
	//Version
	map.map_version = node.attribute("version").as_float();
	//Orientation
	if (node.attribute("orientation").as_string() == "orthogonal")
	{
		map.orientation = orthogonal;
	}
	if (node.attribute("orientation").as_string() == "isometric")
	{
		map.orientation = isometric;
	}
	if (node.attribute("orientation").as_string() == "staggered")
	{
		map.orientation = staggered;
	}
	if (node.attribute("orientation").as_string() == "hexagonal")
	{
		map.orientation = hexagonal;
	}
	//Render order
	if (node.attribute("renderorder").as_string() == "right-down")
	{
		map.renderorder = right_down;
	}
	if (node.attribute("renderorder").as_string() == "right-up")
	{
		map.renderorder = right_up;
	}
	if (node.attribute("renderorder").as_string() == "left-up")
	{
		map.renderorder = left_up;
	}
	if (node.attribute("renderorder").as_string() == "left-dowm")
	{
		map.renderorder = left_down;
	}
	//Width
	map.width = node.attribute("width").as_int();
	//Height
	map.height = node.attribute("height").as_int();
	//Tile height
	map.tileheight = node.attribute("tileheight").as_int();
	//Tile width
	map.tilewidth = node.attribute("tilewidth").as_int();
	//Next object id
	map.nextobjectid = node.attribute("nextobjectid").as_int();
}