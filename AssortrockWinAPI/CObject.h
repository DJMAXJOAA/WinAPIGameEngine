#pragma once

class CCollider;

// 객체화 할 수 없는 추상 클래스
class CObject
{
private:
	Vec2 m_vPos;
	Vec2 m_vScale;

	CCollider* m_pCollider;	// nullptr이라면 콜라이더가 필요 없는 오브젝트들(배경이나 ui 등)

public:
	CObject();
	virtual ~CObject();

public:
	void SetPos(Vec2 vPos) { m_vPos = vPos; }
	void SetScale(Vec2 vScale) { m_vScale = vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }
	CCollider* GetCollider() { return m_pCollider; }

	void CreateCollider();

public:
	virtual void Update() = 0; // 순수 가상 함수 -> 오브젝트들의 Update는 모두 기능이 다름 (다형성)
	virtual void FinalUpdate() final; // final 키워드를 사용해서 오버라이딩을 막아준다
	virtual void Render(HDC hdc);

	void ComponetRender(HDC hdc);
};