#pragma once

class CObject
{
private:
	Vec2 m_vPos;
	Vec2 m_vScale;

public:
	void SetPos(Vec2 vPos) { m_vPos = vPos; }
	void SetScale(Vec2 vScale) { m_vScale = vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

public:
	void Update();
	void Render(HDC hdc);

public:
	CObject();
	virtual ~CObject();
};