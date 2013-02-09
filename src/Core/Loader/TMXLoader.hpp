/*
 *  TMXLoader.hpp
 *  TMXLoader
 *
 *  Created by mooglwy on 28/11/10.
 *
 *  This software is provided 'as-is', without any express or
 *  implied warranty. In no event will the authors be held
 *  liable for any damages arising from the use of this software.
 *  
 *  Permission is granted to anyone to use this software for any purpose,
 *  including commercial applications, and to alter it and redistribute
 *  it freely, subject to the following restrictions:
 *  
 *  1. The origin of this software must not be misrepresented;
 *     you must not claim that you wrote the original software.
 *     If you use this software in a product, an acknowledgment
 *     in the product documentation would be appreciated but
 *     is not required.
 *  
 *  2. Altered source versions must be plainly marked as such,
 *     and must not be misrepresented as being the original software.
 *  
 *  3. This notice may not be removed or altered from any
 *     source distribution.
 *
 */

#ifndef _TMX_LOADER_
#define _TMX_LOADER_

#include <string>
#include <vector>
#include <memory>

namespace TMX
{
	class Loader;
	class Map;
	class TileSet;
	class Layer;
	/*
	class ObjectGroup;	//not implemented yet
	class Object;		//not implemented yet
	class Properties;	//not implemented yet
	class Property;		//not implemented yet
	*/
	
	/*	This loader only support : 
	 *		- version 1.0
	 *		- XML version
	 *		- orthogonal orientation
	 *		- no TSX tileset
	 */
	class Loader
	{
	public:
		static std::auto_ptr<Map> LoadFromFile(const std::string& filename);
	};
	
	class Map
	{
	public:
		Map()
		: width(0)
		, height(0)
		, tileWidth(0)
		, tileHeight(0)
		, tilesets()
		, layers()
		{}
		~Map();
		
		int width;
		int height;
		int tileWidth;
		int tileHeight;
		std::vector<TileSet*> tilesets;
		std::vector<Layer*>   layers;
	};
	
	class TileSet
	{
	public:
		TileSet()
		: firstGlobalID(0)
		, name("")
		, sourceFileName("")
		, tileWidth(0)
		, tileHeight(0)
		, spacing(0)
		, margin(0)
		{}
		~TileSet();
		int firstGlobalID;
		std::string name;
		std::string sourceFileName;
		int tileWidth;
		int tileHeight;
		int spacing;
		int margin;
	};
	
	class Layer
	{
	public:
		Layer()
		: name("")
		, opacity(0.0)
		, visible(0)
		, data()
		{}
		~Layer();
		std::string name;
		float opacity;
		int  visible;
		std::vector<int> data;
	};
	
} //end of namespace TMX

#endif //end of _TMX_LOADER_
