//------------------------------------------------------------------------------
//
// File Name:	ColliderLine.cpp
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

#include "Precompiled.h"
#include "ColliderLine.h"
#include "ColliderCircle.h"
#include "Stream.h"
#include "Entity.h"
#include "Component.h"
#include "Transform.h"
#include "Physics.h"
#include "CollisionRecord.h"


//------------------------------------------------------------------------------
// External Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Namespace Declarations:
//------------------------------------------------------------------------------

namespace CS529
{
	//--------------------------------------------------------------------------
	// Public Constants:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Public Static Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Public Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Private Static Constants:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Private Constants:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Private Static Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Private Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Constructors/Destructors:
	//--------------------------------------------------------------------------

#pragma region Constructors

	ColliderLine::ColliderLine(void)
	{

	}

	ColliderLine::ColliderLine(const ColliderLine* other)
	{
		this->lineSegments = other->lineSegments;
	}

	//--------------------------------------------------------------------------

	//ColliderLine::~ColliderLine(void)
	//{
	//}

#pragma endregion Constructors

	//--------------------------------------------------------------------------
	// Public Static Functions:
	//--------------------------------------------------------------------------

#pragma region Public Static Functions

#pragma endregion Public Static Functions

	//--------------------------------------------------------------------------
	// Public Functions:
	//--------------------------------------------------------------------------

#pragma region Public Functions

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

		// @brief Read the properties of a ColliderLine component from a stream.
		// @brief Specific Steps:
		// @brief   Check for valid stream (optional).
		// @brief   Traverse down the tree to the "ColliderLine" object (PushNode).
		// @brief   If the stream contains "LineSegments",
		// @brief     Create a lambda expression for reading a single line segment from the stream.
		// @brief       Create a line segment variable.
		// @brief       Read "P0" from the stream.
		// @brief       Read "P1" from the stream.
		// @brief       Add the line segment to the container.
		// @brief         [HINT: There is a function for this purpose.]
		// @brief     Read the contents of "LineSegments" array.
		// @brief   Return to the original location in the tree (PopObject).
		//
		// @param stream = The data stream used for reading.
	void ColliderLine::Read(Stream& stream)
	{
		if (stream.IsValid() && stream.Contains("ColliderLine"))
		{
			stream.PushNode("ColliderLine");
			if (stream.Contains("LineSegments"))
			{
				//stream.PushNode("LineSegments");
				std::vector<LineSegment> lineVec;
				auto readLine = [&]() 
				{
					Vector2D p0, p1;
					if (stream.ReadVector2D("P0",p0) &&
						stream.ReadVector2D("P1", p1))
					{
						lineVec.push_back(LineSegment(p0, p1));
					}
				};
				stream.ReadArray("LineSegments", readLine);
				if (lineVec.size() >= 1)
				{
					for (int i = 0; i < lineVec.size(); i++)
					{
						AddLineSegment(lineVec[i]);
					}
				}
			}
			stream.PopNode();
		}
	}

	// @brief Check for a collision between a line collider and a circle collider.
	// @brief Specific Steps:
	// @brief   Cast the other pointer to a ColliderCircle*.
	// @brief   if the cast was successful,
	// @brief     Get the 'other' entity's old and new translation values (e.g Bs & Be).
	// @brief     Check for intersection and resolve reflection, if necessary.
	// @brief       [HINT: There is a private function for this purpose.]
	// @brief     Return the result of the intersection check.
	// @brief   Return false.
	//
	// @param other = Pointer to the collider associated with the other entity.
	//
	// @return bool = True if the two colliders are intersecting, otherwise false.
	bool ColliderLine::IsColliding(const Collider* other) const
	{
		bool result = false;
		const ColliderCircle* otherCircle = dynamic_cast<const ColliderCircle*>(other);
		if (otherCircle)
		{
			Transform* t = other->Parent()->Get<Transform>();
			Physics* p = other->Parent()->Get<Physics>();
			if (t)
			{
				const Vector2D& ot = p->OldTranslation();
				const Vector2D& nt = t->Translation();
			     result = IntersectAndReflect(otherCircle, ot, nt);
			}
		}
		return result;
	}

	// @brief Add a single line segment to the line segment container.
	// @brief [NOTE: While this function is not strictly necessary, it does provide a
	// @brief   mechanism by which external code can also create a line collider.
	// @brief   Therefore, I would suggest that you call this function from within the
	// @brief   Read function, instead of just calling push_back directly.
	// @brief   This way, if the container were to be changed, fewer lines of code
	// @brief   would have to be modified.]
	// 
	// @param line = The line segment to be added to the container.
	void ColliderLine::AddLineSegment(const LineSegment& line)
	{
		lineSegments.push_back(line);
	}

	// @brief Check for intersection and resolve reflection, if necessary.
	// @brief Specific Steps:
	// @brief   Calculate the 'circle' entity's change in translation during the current frame (v).
	// #brief   Initialize the collision record (A = moving object, B = other object).
	// @brief   Iterate through all line segments:
	// @brief     Get the starting and ending point of the current line segment (p0 & p1).
	// @brief     Calculate the "edge" vector (e).
	// @brief     Calculate the unit-length "normal" vector (n).
	// @brief     If the 'circle' entity is stationary or moving parallel to the line segment,
	// @brief       Continue
	// @brief     Calculate n.Bs, n.Be, and n.P0 for inside/outside half-plane checks.
	// @brief     If both points are on the inside half-plane,
	// @brief       Continue.
	// @brief     If both points are on the outside half-plane,
	// @brief       Continue.
	// @brief     Calculate the time of intersection (ti).
	// @brief     If ti is greater than or equal to the previously stored ti,
	// @brief       Continue.  Ignore this potential collision point, as it won't be reached.
	// @brief     Calculate the point of intersection (Bi).
	// @brief     If the point of intersection is outside of p0 (behind).
	// @brief       Continue.
	// @brief     If the point of intersection is outside of p1 (behind).
	// @brief       Continue.
	// @brief     Update the collision record with a new point of collision.
	// @brief   If a collision has been detected,
	// @brief     Perform reflection.
	// @brief     Return true.
	//
	// @param circle = Pointer to the circle collider to be checked.
	// @param Bs = The starting position of the moving circle collider.
	// @param Be = The ending position of the moving circle collider.
	//
	// @return bool = True if an intersection occured, otherwise false.
	bool  ColliderLine::IntersectAndReflect(const ColliderCircle* circle, const Vector2D& Bs, const Vector2D& Be)const
	{
		const float EPS = 1e-6f;
		bool collided = false;
		Vector2D delta = Vector2D(Be.x - Bs.x, Be.y - Bs.y);
		CollisionRecord rec = CollisionRecord(circle->Parent(), this->Parent(), Bs, Be);
		for (int i = 0; i < lineSegments.size(); i++)
		{
			Vector2D start = lineSegments[i].p0;
			Vector2D end = lineSegments[i].p1;
			Vector2D e = Vector2D(end.x - start.x, end.y - start.y);
			Vector2D n(-e.y, e.x);
			n.Normalize();
			if (n.Length() < EPS) continue;
			if (std::fabs(delta.DotProduct(n)) < EPS || delta.Length() < EPS)
				continue;
			float ds = n.DotProduct(Vector2D(Bs.x-start.x, Bs.y-start.y));
			float de = n.DotProduct(Vector2D(Be.x - start.x, Be.y-start.y));
			if (ds >= 0.0f && de >= 0.0f)
				continue;
			if (ds <= 0.0f && de <= 0.0f)
				continue;
			float ti = ds / (ds - de);
			if (ti < 0.0f || ti > 1.0f) continue;
			Vector2D Bi(Bs.x + delta.x * ti, Bs.y + delta.y * ti);
			if (IsOutsideSegment(Bi, start, end)) continue;
			if (ti < rec.ti)
			{
				rec.Update(ti, Bi, n);
			}
			collided = true;
		}
		if (collided)
		{
			Reflect(rec);
		}
		return collided;
	}

	// @brief Check for non-collision (Bi outside of P0->P1 line segment).
	// @brief Specific Steps:
	// @brief   Calculate the vectors (Bi - p0) and (p1 - p0).
	// @brief   If the resulting dot-product is negative, then no collision.
	// @brief   Return the result of the outside check.
	// 
	// @param Bi = The calculated point of intersection on the infinite extension of the line segment.
	// @param p0 = The 1st point of the line segment.
	// @param p1 = The 2nd point of the line segment.
	//
	// @return bool = True if the point of intersection is outside of the line segment, otherwise false.
	bool  ColliderLine::IsOutsideSegment(const Vector2D& Bi, const Vector2D& p0, const Vector2D& p1) const
	{
		Vector2D e = Vector2D(p1.x - p0.x, p1.y - p0.y);
		Vector2D d = Vector2D(Bi.x - p0.x, Bi.y - p0.y);
		float dot = d.DotProduct(e);
		float len2 = e.DotProduct(e);
		if (dot < 0.0f) return true;
		if (dot > len2)   return true;
		return false;
	}

	// @brief Resolve an elastic collision by reflecting the moving object.
	// @brief Specific Steps:
	// @brief   Calculate the "incident" vector (i = Be - Bi).
	// @brief   Calculate the "reflection" vector (r).
	// @brief   Get the circle collider associated with entityA.
	// @brief   Calculate the new translation for entityA.
	// @brief   Calculate the new rotation for entityA.
	// @brief   Calculate the new velocity for entityA.
	// @brief   Repeat the Intersect and Reflect process for outside corners.
	// @brief     [HINT: new Bs = Bi and new Be = new translation.]
	// 
	// @param collision = The collision record containing the necessary information.
	void  ColliderLine::Reflect(const CollisionRecord& collision) const
	{
		Vector2D i = Vector2D(collision.Be.x - collision.Bi.x, collision.Be.y - collision.Bi.y);
		float dot = i.DotProduct(collision.n);
		bool isEntry = (dot > 0.0f);
		//Vector2D en= isEntry ? collision.n : Vector2D(-collision.n.x, -collision.n.y);
		Vector2D r = Vector2D(i.x - 2.0f * dot * collision.n.x, i.y - 2.0f * dot * collision.n.y);
		ColliderCircle* ca = collision.entityA->Get<ColliderCircle>();
		if (ca)
		{
			Transform* ta = collision.entityA->Get<Transform>();
			if (ta)
			{
				Vector2D newTranslation = Vector2D(collision.Bi.x + r.x, collision.Bi.y + r.y);
				ta->Translation(newTranslation);
				Physics* pa = collision.entityA->Get<Physics>();
				if (pa)
				{
					Vector2D oldVelocity = pa->Velocity();
					float vdot = pa->Velocity().DotProduct(collision.n);
					Vector2D newVelocity = Vector2D(pa->Velocity().x - 2.0f * vdot * collision.n.x, pa->Velocity().y - 2.0f * vdot * collision.n.y);
					pa->Velocity(newVelocity);
					ta->Rotation(atan2(r.y, r.x));
				}
				//IntersectAndReflect(ca, collision.Bi, newTranslation);
				static thread_local int recursionDepth = 0;
				const int MAX_RECURSION = 3;

				if (recursionDepth < MAX_RECURSION)
				{
					++recursionDepth;
					IntersectAndReflect(ca, collision.Bi, newTranslation);
					--recursionDepth;
				}
			}
			
		}
	}
#pragma endregion Private Functions

}	// namespace