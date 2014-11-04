#pragma once
#include "Constant.h"
#include <cassert>

namespace RE_NAMESPACE
{
	struct Rect;

	struct Vector {
		float x;
		float y;

		Vector(const float x = 0.0f, const float y = 0.0f);
		Vector operator+(const Vector& right) const;
		Vector operator-(const Vector& right) const;
		Vector& operator+=(const Vector& right);
		Vector& operator-=(const Vector& right);
		bool isInRect(Rect rect) const;
	};

	struct Size {
		float width;
		float height;

		Size(const float width = 0.0f, const float height = 0.0f);
		Size operator+(const Size& right) const;
		Size operator-(const Size& right) const;
		Size& operator+=(const Size& right);
		Size& operator-=(const Size& right);
	};

	struct Rect {
		Vector origin;
		Size size;

		Rect(const float x = 0.0f, const float y = 0.0f, const float width = 0.0f, const float height = 0.0f);
		Rect(const Vector& origin, const Size& size);
		bool doesContain(Vector vector) const;
		bool doesIntersect(Rect rect) const;
	};

	struct Color {
		float red;
		float green;
		float blue;
		float alpha;

		Color();
		Color(float red, float green, float blue);
		Color(float red, float green, float blue, float alpha);
		Color(int red, int green, int blue);
		Color(int red, int green, int blue, int alpha);
	};

	inline Vector::Vector(const float x, const float y) : x(x), y(y) {
	}

	inline Vector Vector::operator+(const Vector& right) const {
		return Vector(x + right.x, y + right.y);
	}

	inline Vector Vector::operator-(const Vector& right) const {
		return Vector(x - right.x, y - right.y);
	}

	inline Vector& Vector::operator+=(const Vector& right) {
		return *this = *this + right;
	}

	inline Vector& Vector::operator-=(const Vector& right) {
		return *this = *this - right;
	}

	inline bool Vector::isInRect(Rect rect) const {
		return this->x >= rect.origin.x && this->x <= rect.origin.x + rect.size.width && this->y >= rect.origin.y && this->y <= rect.origin.y + rect.size.height;
	}

	inline Size::Size(const float width, const float height) : width(width), height(height) {
		assert(width >= 0 && height >= 0);
	}

	inline Size Size::operator+(const Size& right) const {
		return Size(width + right.width, height + right.height);
	}

	inline Size Size::operator-(const Size& right) const {
		return Size(width - right.width, height - right.height);
	}

	inline Size& Size::operator+=(const Size& right) {
		return *this = *this + right;
	}

	inline Size& Size::operator-=(const Size& right) {
		return *this = *this - right;
	}

	inline Rect::Rect(const float x, const float y, const float width, const float height) {
		origin = Vector(x, y);
		size = Size(width, height);
	}

	inline Rect::Rect(const Vector& origin, const Size& size) {
		this->origin = origin;
		this->size = size;
	}

	inline bool Rect::doesContain(Vector vector) const {
		return vector.isInRect(*this);
	}

	inline bool Rect::doesIntersect(Rect rect) const {
		return !(this->origin.x > rect.origin.x + rect.size.width || this->origin.x + this->size.width < rect.origin.x || this->origin.y > rect.origin.y + rect.size.height || this->origin.y + this->size.height < rect.origin.y);
	}

	inline Color::Color() : Color(1.0f, 1.0f, 1.0f, 1.0f) {

	}

	inline Color::Color(float red, float green, float blue) : Color(red, green, blue, 1.0f) {

	}

	inline Color::Color(float red, float green, float blue, float alpha) : red(red), green(green), blue(blue), alpha(alpha) {

	}

	inline Color::Color(int red, int green, int blue) : Color(red, green, blue, 255) {

	}

	inline Color::Color(int red, int green, int blue, int alpha) : Color(red / 255.0f, green / 255.0f, blue / 255.0f, alpha / 255.0f) {

	}
}