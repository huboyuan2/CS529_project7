//------------------------------------------------------------------------------
//
// File Name:	SpriteSource.cpp
// Author(s):	Boyuan Hu
// Course:		CS529F25
// Project:		Project 2
// Purpose:		Template for a new .cpp file.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once
#include <string>
#include <string_view>

#include "DGL.h"
#include "SpriteSource.h"
#include "Mesh.h"
#include "Component.h"
#include "TileMapData.h"
#include "TileSet.h"
#include "Transform.h"
#include "Physics.h"
namespace CS529
{
    class TileMap : public Component
    {
    private:
        //std::vector<unsigned> tileData;
        //const TileMapData* tileMapData;
        TileMapData* tileMapData;
    public:
        TileMap(void);
        TileMap(const TileMap* other);
        ~TileMap(void) override;
        bool Initialize() override { return true; }
        void Update(float dt) override {}
        void Render() const override;
        void Read(Stream& stream) override;
        int GetCollisionFlags(float worldX, float worldY, float width, float height) const
        {
            return tileMapData ? tileMapData->IsAreaPassable(worldX, worldY, width, height) : HP_NONE;
        }
        bool CheckCollisionAt(float worldX, float worldY, float width = 10.0, float height = 15.0);
        int CheckAndResolveCollision(Entity* entity, float width, float height);
        unsigned GetTileAt(unsigned row, unsigned col) const;
        void SetTileAt(unsigned row, unsigned col, unsigned tileIndex);

    private:
        TileMap* Clone() const override { return new TileMap(this); }
        void ResolveCollision(
            Transform* transform,
            Physics* physics,
            const Vector2D& oldPos,
            const Vector2D& newPos,
            float width,
            float height,
            int collisionFlags
        ) const;
    };
}