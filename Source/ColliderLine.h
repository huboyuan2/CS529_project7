//------------------------------------------------------------------------------
//
// File Name:	ColliderLine.h
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 6
// Purpose:		This component class is responsible for detecting collisions
//   between a circle collider and a line collider.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include <vector>

#include "Collider.h"
#include "Vector2D.h"

//------------------------------------------------------------------------------
// External Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Namespace Declarations:
//------------------------------------------------------------------------------

namespace CS529
{
	// Forward Declarations:
	class ColliderCircle;
	class CollisionRecord;
	class Stream;

	// Typedefs:
	typedef struct LineSegment
	{
		Vector2D p0;
		Vector2D p1;
	} LineSegment;

	// Class Definition:
	class ColliderLine : public Collider
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	public:
		ColliderLine(void);

		// @brief This copy-constructor should perform a shallow copy of the data.
		ColliderLine(const ColliderLine* other);

		~ColliderLine(void) override {};

		// Public Static Functions:
	public:

		// Public Functions:
	public:

		// Public Event Handlers
	public:

		// Private Functions:
	private:
		// @brief This function is required to invoke the copy-constructor in derived classes.
		ColliderLine* Clone() const override { return new ColliderLine(this); }

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
		void Read(Stream& stream);

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
		bool IsColliding(const Collider* other) const override;

		// @brief Add a single line segment to the line segment container.
		// @brief [NOTE: While this function is not strictly necessary, it does provide a
		// @brief   mechanism by which external code can also create a line collider.
		// @brief   Therefore, I would suggest that you call this function from within the
		// @brief   Read function, instead of just calling push_back directly.
		// @brief   This way, if the container were to be changed, fewer lines of code
		// @brief   would have to be modified.]
		// 
		// @param line = The line segment to be added to the container.
		void AddLineSegment(const LineSegment& line);

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
		bool IntersectAndReflect(const ColliderCircle* circle, const Vector2D& Bs, const Vector2D& Be) const;

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
		bool IsOutsideSegment(const Vector2D& Bi, const Vector2D& p0, const Vector2D& p1) const;

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
		void Reflect(const CollisionRecord& collision) const;

		// Private Constants:
	private:

		// Private Static Variables:
	private:

		// Private Variables:
	private:
		// @brief A simple container for storing multiple line segments.
		std::vector<LineSegment> lineSegments;
	};

}	// namespace