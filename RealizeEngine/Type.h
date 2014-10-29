#pragma once
#include "Constant.h"
#include <cassert>

namespace RE_NAMESPACE
{
	class Rect;

	class Vector {
	private:
		float _x;
		float _y;
	public:
		Vector(const float x = 0.0f, const float y = 0.0f);
		Vector(const Vector& source);
		float getX() const;
		void setX(const float x);
		float getY() const;
		void setY(const float y);
		Vector operator+(const Vector& right) const;
		Vector operator-(const Vector& right) const;
		bool isInRect(Rect rect) const;
	};

	class Size {
	private:
		float _width;
		float _height;
	public:
		Size(const float width = 0.0f, const float height = 0.0f);
		Size(const Size& source);
		float getWidth() const;
		void setWidth(const float width);
		float getHeight() const;
		void setHeight(const float height);
		Size operator+(const Size& right) const;
		Size operator-(const Size& right) const;
	};

	class Rect {
	private:
		Vector _origin;
		Size _size;
	public:
		Rect(const float x = 0.0f, const float y = 0.0f, const float width = 0.0f, const float height = 0.0f);
		Rect(const Vector& origin, const Size& size);
		Rect(const Rect& source);
		Vector getOrigin() const;
		void setOrigin(const Vector& origin);
		Size getSize() const;
		void setSize(const Size& size);
		float getX() const;
		void setX(const float x);
		float getY() const;
		void setY(const float y);
		float getWidth() const;
		void setWidth(const float width);
		float getHeight() const;
		void setHeight(const float height);
		bool doesContain(Vector vector) const;
	};

	inline Vector::Vector(const float x, const float y) : _x(x), _y(y) {
	}

	inline Vector::Vector(const Vector& source) {
		this->_x = source._x;
		this->_y = source._y;
	}

	inline float Vector::getX() const {
		return _x;
	}

	inline void Vector::setX(const float x) {
		_x = x;
	}

	inline float Vector::getY() const {
		return _y;
	}

	inline void Vector::setY(const float y) {
		_y = y;
	}

	inline Vector Vector::operator+(const Vector& right) const {
		return Vector(_x + right._x, _y + right._y);
	}

	inline Vector Vector::operator-(const Vector& right) const {
		return Vector(_x - right._x, _y - right._y);
	}

	inline bool Vector::isInRect(Rect rect) const {
		return this->getX() >= rect.getX() && this->getX() <= rect.getX() + rect.getWidth() && this->getY() >= rect.getY() && this->getY() <= rect.getY() + rect.getHeight();
	}

	inline Size::Size(const float width, const float height) : _width(width), _height(height) {
		assert(width >= 0 && height >= 0);
	}

	inline Size::Size(const Size& source) {
		this->_width = source._width;
		this->_height = source._height;
	}

	inline float Size::getWidth() const {
		return _width;
	}

	inline void Size::setWidth(const float width) {
		assert(width >= 0);
		_width = width;
	}

	inline float Size::getHeight() const {
		return _height;
	}

	inline void Size::setHeight(const float height) {
		assert(height >= 0);
		_height = height;
	}

	inline Size Size::operator+(const Size& right) const {
		return Size(_width + right._width, _height + right._height);
	}

	inline Size Size::operator-(const Size& right) const {
		return Size(_width - right._width, _height - right._height);
	}

	inline Rect::Rect(const float x, const float y, const float width, const float height) {
		_origin = Vector(x, y);
		_size = Size(width, height);
	}

	inline Rect::Rect(const Vector& origin, const Size& size) {
		_origin = origin;
		_size = size;
	}

	inline Rect::Rect(const Rect& source) {
		_origin = source._origin;
		_size = source._size;
	}

	inline Vector Rect::getOrigin() const {
		return _origin;
	}

	inline void Rect::setOrigin(const Vector& origin) {
		_origin = origin;
	}

	inline Size Rect::getSize() const {
		return _size;
	}

	inline void Rect::setSize(const Size& size) {
		_size = size;
	}

	inline float Rect::getX() const {
		return _origin.getX();
	}

	inline void Rect::setX(const float x) {
		_origin.setX(x);
	}

	inline float Rect::getY() const {
		return _origin.getY();
	}

	inline void Rect::setY(const float y) {
		_origin.setY(y);
	}

	inline float Rect::getWidth() const {
		return _size.getWidth();
	}

	inline void Rect::setWidth(const float width) {
		_size.setWidth(width);
	}

	inline float Rect::getHeight() const {
		return _size.getHeight();
	}

	inline void Rect::setHeight(const float height) {
		_size.setHeight(height);
	}

	inline bool Rect::doesContain(Vector vector) const {
		return vector.isInRect(*this);
	}
}