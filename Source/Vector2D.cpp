#include "Precompiled.h"
#include "Vector2D.h"
#include <cmath>
#include <numbers>
#include "DGL.h"
namespace CS529
{
    Vector2D::Vector2D()
    {
        this->x = 0.0f;
        this->y = 0.0f;
    }

    Vector2D::Vector2D(float x, float y)
    {
		this->x = x;
        this->y = y;
    }

    Vector2D::Vector2D(const Vector2D& other)
    {
        this->x = other.x;
        this->y = other.y;
    }

    void Vector2D::Zero()
    {
        this->x = 0.0f;
        this->y = 0.0f;
    }

    void Vector2D::Set(float x, float y)
    {
        this->x = x;
        this->y = y;
    }

    void Vector2D::Negate()
    {
        this->x = -x;
        this->y = -y;
    }

    void Vector2D::Add(const Vector2D& offset)
    {
        this->x += offset.x;
        this->y += offset.y;
    }

    void Vector2D::Sub(const Vector2D& offset)
    {
        this->x -= offset.x;
        this->y -= offset.y;
    }

    void Vector2D::Normalize()
    {
		float len = Length();
        this->x /= len;
        this->y /= len;
    }

    void Vector2D::Scale(float scale)
    {
        this->x *= scale;
        this->y *= scale;
    }
    // @brief This function scales the 2D vector by 'scale" and adds the offset.
//
// @param scale = The value by which to scale the vector.
// @param offset = The offset to be added to the 2D vector.
    void Vector2D::ScaleAdd(float scale, const Vector2D& offset)
    {
        this->x += scale * offset.x;
        this->y += scale * offset.y;
    }

    void Vector2D::ScaleSub(float scale, const Vector2D& offset)
    {
        this->x -= scale * offset.x;
        this->y -= scale * offset.y;
    }

    float Vector2D::Length() const
    {
        return std::sqrt(SquareLength());
    }

    float Vector2D::SquareLength() const
    {
        return x * x + y * y;
    }

    float Vector2D::Distance(const Vector2D& point2) const
    {
        return std::sqrt(SquareDistance(point2));
    }

    float Vector2D::SquareDistance(const Vector2D& point2) const
    {
        return (point2.x - this->x) * (point2.x - this->x) + (point2.y - this->y) * (point2.y - this->y);
    }

    float Vector2D::DotProduct(const Vector2D& vector2) const
    {
		return this->x * vector2.x + this->y * vector2.y;
    }

    void Vector2D::FromAngleDeg(float angle)
    {
        float radians = static_cast<float>((angle * std::numbers::pi) / 180.0f);
        this->x = std::cos(radians);
        this->y = std::sin(radians);
    }

    void Vector2D::FromAngleRad(float angle)
    {
        this->x = std::cos(angle);
        this->y = std::sin(angle);
    }

    float Vector2D::ToAngleRad() const
    {
		return std::atan2(this->y, this->x);
    }
}