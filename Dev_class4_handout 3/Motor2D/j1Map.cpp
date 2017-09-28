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
		Fill_All_Tiles(map_file);
	}

	// TODO 4: Create and call a private function to load a tileset
	// remember to support more any number of tilesets!
	

	if(ret == true)
	{
		LOG("Successfully parsed map XML file: %s \n", file_name);

		LOG("Version: %f", map.map_version);

		char* _orientation = "No orientation";

		if (map.orientation == 0) //Should put all the cases here, but i won't as it is not interesting
		{
			_orientation = "orthogonal";
		}
		LOG("Orientation: %s", _orientation);

		char* _renderorder= "No render order";

		if (map.renderorder == 0)
		{
			_renderorder = "right-down";
		}
		LOG("Render order: %s", _renderorder);

		LOG("Width: %i", map.width);

		LOG("Height: %i", map.height);

		LOG("Tile_width: %i", map.tilewidth);

		LOG("Tile_height: %i", map.tileheight);

		LOG("Next object id %i \n", map.nextobjectid);

		// TODO 5: LOG all the data loaded
		// iterate all tilesets and LOG everything

		int counter = 0;
		while (&tile_array->At(counter)->data != nullptr)
		{
			LOG("Tileset---\n");

			LOG("Name: %s", tile_array->At(counter)->data.image.source);

			LOG("Height: %i", tile_array->At(counter)->data.image.height);

			LOG("Width: %i\n", tile_array->At(counter)->data.image.width);

			LOG("Firstgit: %i", tile_array->At(counter)->data.firstid);

			LOG("Margin: %i", tile_array->At(counter)->data.margin);

			LOG("Name: %s", tile_array->At(counter)->data.name);

			LOG("Spacing: %i", tile_array->At(counter)->data.spacing);

			LOG("Tile height: %i", tile_array->At(counter)->data.tileheight);

			LOG("Tile width: %i \n", tile_array->At(counter)->data.tilewidth);

			counter++;
		}
	}

	map_loaded = ret;

	return ret;
}

void j1Map::Fill_All_Map_Data(const pugi::xml_node& node)
{
	//Version
	map.map_version = node.child("map").attribute("version").as_float();
	//Orientation
	if (node.child("map").attribute("orientation").as_string() == "orthogonal")
	{
		map.orientation = orthogonal;
	}
	if (node.child("map").attribute("orientation").as_string() == "isometric")
	{
		map.orientation = isometric;
	}
	if (node.child("map").attribute("orientation").as_string() == "staggered")
	{
		map.orientation = staggered;
	}
	if (node.child("map").attribute("orientation").as_string() == "hexagonal")
	{
		map.orientation = hexagonal;
	}
	//Render order
	if (node.child("map").attribute("renderorder").as_string() == "right-down")
	{
		map.renderorder = right_down;
	}
	if (node.child("map").attribute("renderorder").as_string() == "right-up")
	{
		map.renderorder = right_up;
	}
	if (node.child("map").attribute("renderorder").as_string() == "left-up")
	{
		map.renderorder = left_up;
	}
	if (node.child("map").attribute("renderorder").as_string() == "left-dowm")
	{
		map.renderorder = left_down;
	}
	//Width
	map.width = node.child("map").attribute("width").as_int();
	//Height
	map.height = node.child("map").attribute("height").as_int();
	//Tile height
	map.tileheight = node.child("map").attribute("tileheight").as_int();
	//Tile width
	map.tilewidth = node.child("map").attribute("tilewidth").as_int();
	//Next object id
	map.nextobjectid = node.child("map").attribute("nextobjectid").as_int();
}

void j1Map::Fill_All_Tiles(const pugi::xml_node& node)
{
	pugi::xml_node tileset = node.child("map").child("tileset");
	while (tileset != nullptr)
	{
		Tileset tileset_data;
		tileset_data.firstid = tileset.attribute("firstgit").as_int();
		tileset_data.margin = tileset.attribute("margin").as_int();
		tileset_data.name = tileset.attribute("name").as_string();
		tileset_data.spacing = tileset.attribute("spacing").as_int();
		tileset_data.tileheight = tileset.attribute("tileheight").as_int();
		tileset_data.tilewidth = tileset.attribute("tilewidth").as_int();
		tileset_data.image.height = tileset.child("image").attribute("height").as_int();
		tileset_data.image.width = tileset.child("image").attribute("width").as_int();
		tileset_data.image.source = tileset.child("image").attribute("source").as_string();


		tile_array->add(tileset_data);

	

		tileset = tileset.next_sibling("tileset");
	}
}