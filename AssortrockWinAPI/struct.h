#pragma once

struct Vec2
{
	float x;
	float y;
public:
	float Length() { return (float)sqrt(pow(x, 2) + pow(y, 2)); }

	Vec2& Normalize()
	{
		float fLen = Length();

		// 0으로 나누거나, 곱하는 경우를 없애야 한다(예외처리) -> 연산이 복잡해진다
		assert(fLen != 0.f);

		x /= fLen;
		y /= fLen;
		return *this;
	}

public:
	Vec2& operator = (POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
	}

	Vec2 operator + (Vec2 _vOther) { return Vec2(x + _vOther.x, y + _vOther.y); }
	Vec2 operator - (Vec2 _vOther) { return Vec2(x - _vOther.x, y - _vOther.y); }
	Vec2 operator * (Vec2 _vOther) { return Vec2(x * _vOther.x, y * _vOther.y); }
	Vec2 operator / (Vec2 _vOther) { assert(!(0.f == _vOther.x || 0.f == _vOther.y)); return Vec2(x / _vOther.x, y / _vOther.y); } // 0이 아니여야댐

public:
	Vec2() : x(0.f), y(0.f) {}
	Vec2(float _x, float _y) : x(_x), y(_y) {}
	Vec2(int _x, int _y) : x((float)_x), y((float)_y) {}
	Vec2(const POINT& _pt) : x((float)_pt.x), y((float)_pt.y) {}
};