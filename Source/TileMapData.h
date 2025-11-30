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

        //void SetBaseX(float worldx) { mapBaseX = worldx; }
        //void SetBaseY(float worldy) { mapBaseY = worldy; }
        unsigned GetRows() const { return rows; }
        unsigned GetCols() const { return cols; }
        unsigned GetBaseX() const { return mapBaseX; }
        unsigned GetBaseY() const { return mapBaseY; }
		bool IsPassable(unsigned row, unsigned col) const;
        const TileSet* GetTileSet() const { return tileSet; }
        bool IsPassableAtWorldPos(float worldX, float worldY) const;
        bool IsAreaPassable(float worldX, float worldY, float width, float height) const;
    private:
        std::string name;                     
        unsigned rows;
        unsigned cols;
        unsigned scale;
        float mapBaseX;
        float mapBaseY;
        std::vector<unsigned> tileData;
        const TileSet* tileSet;
    };
}