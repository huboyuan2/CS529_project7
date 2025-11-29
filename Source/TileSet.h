//------------------------------------------------------------------------------
//
// File Name:	TileMapData.cpp
// Author(s):	Boyuan Hu
// Course:		CS529F25
// Project:		Project 1
// Purpose:		Template for a new .cpp file.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------
#pragma once
#include <string>
#include <string_view>
#include "Mesh.h"

namespace CS529
{
    class SpriteSource;
    class Stream;

    class TileSet
    {
    public:
        TileSet(void);
        ~TileSet(void);

        
        void Read(Stream& stream);

        
        const SpriteSource* GetSpriteSource(unsigned index) const;
        const Mesh* GetMesh() const { return mesh; }
		const int GetSpriteSourceCount() const { return static_cast<int>(spriteSources.size()); }
        unsigned GetTileWidth() const { return tileWidth; }
        unsigned GetTileHeight() const { return tileHeight; }
        const std::string& GetName() const { return name; }

    private:
        std::string name;
        std::vector<const SpriteSource*> spriteSources;
        const Mesh* mesh;
        unsigned tileWidth;
        unsigned tileHeight;
    };
}
