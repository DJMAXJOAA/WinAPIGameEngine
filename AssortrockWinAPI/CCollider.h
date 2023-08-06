#pragma once

class CObject;

class CCollider
{
private:
	CObject* m_pOwner;		// �ݶ��̴��� �پ��ִ� ������Ʈ�� ������ �˾ƾ� �Ѵ�(�׷��� ����ٴϴϱ�)
	Vec2	 m_vOffsetPos;	// ���� ��ǥ(������ ������Ʈ�� ��ǥ)������ ������� �Ÿ�
	Vec2	 m_vFinalPos;	// FinalUpdate()�� ���� ���� ���� �ݶ��̴� ��ġ(������+��ǥ��) -> �� ������ ����ؼ� ����

	Vec2	 m_vScale;		// �浹ü�� ũ��

public:
	void SetOwner(CObject* pObj) { m_pOwner = pObj; }
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	
public:
	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }

public:
	void FinalUpdate();
	void Render(HDC hdc);	// �׽�Ʈ �Ҷ� �ѳ��ٰ�, ������ ����

public:
	CCollider();
	~CCollider();

	friend class CObject;
};