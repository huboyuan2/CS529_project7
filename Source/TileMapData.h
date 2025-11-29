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
#include <vector>
#include <string>

namespace CS529
{
    class Stream;
    class TileSet;

    class TileMapData
    {
    public:
        TileMapData(void);
        ~TileMapData(void);

		// Read tile map data from a stream
        void Read(Stream& stream);

		// Getters and Setters
        unsigned GetTileAt(unsigned row, unsigned col) const;
        void SetTileAt(unsigned row, unsigned col, unsigned tileIndex);

        unsigned GetRows() const { return rows; }
        unsigned GetCols() const { return cols; }
		bool IsPassable(unsigned row, unsigned col) const;
        const TileSet* GetTileSet() const { return tileSet; }
        bool IsPassableAtWorldPos(float worldX, float worldY) const;
    private:
        std::string name;                     
        unsigned rows;
        unsigned cols;
        std::vector<unsigned> tileData;
        const TileSet* tileSet;
    };
}