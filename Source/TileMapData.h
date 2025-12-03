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
    enum HotPointFlags
    {
        HP_NONE = 0,              // 0000
        HP_BOTTOM_LEFT = 1 << 0,  // 0001 - 脚部左侧（Y 小）
        HP_BOTTOM_RIGHT = 1 << 1, // 0010 - 脚部右侧（Y 小）
        HP_TOP_LEFT = 1 << 2,     // 0100 - 头部左侧（Y 大）
        HP_TOP_RIGHT = 1 << 3     // 1000 - 头部右侧（Y 大）
    };
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
        float GetBaseX() const { return mapBaseX; }
        float GetBaseY() const { return mapBaseY; }
		bool IsPassable(unsigned row, unsigned col) const;
        const TileSet* GetTileSet() const { return tileSet; }
        bool IsPassableAtWorldPos(float worldX, float worldY) const;
        int IsAreaPassable(float worldX, float worldY, float width, float height) const;
        static bool HasCollision(int flags) { return flags != HP_NONE; }
        static bool IsStanding(int flags) { return (flags & (HP_BOTTOM_LEFT | HP_BOTTOM_RIGHT)) != 0; }
        static bool IsTouchingCeiling(int flags) { return (flags & (HP_TOP_LEFT | HP_TOP_RIGHT)) != 0; }
        static bool IsTouchingLeftWall(int flags) {
            
            bool leftTop = (flags & HP_TOP_LEFT) != 0;
            bool leftBottom = (flags & HP_BOTTOM_LEFT) != 0;
            if (!leftTop && leftBottom)
                return false;
            return leftTop;
        }
        static bool IsTouchingRightWall(int flags) {
            bool rightTop = (flags & HP_TOP_RIGHT) != 0;
            bool rightBottom = (flags & HP_BOTTOM_RIGHT) != 0;
            if (!rightTop && rightBottom)
                return false;
            return rightTop;
        }
        static int GetCollisionCount(int flags);
    private:
        std::string name;                     
        unsigned rows;
        unsigned cols;
        float scale;
        float mapBaseX;
        float mapBaseY;
        std::vector<unsigned> tileData;
        const TileSet* tileSet;
    };
}