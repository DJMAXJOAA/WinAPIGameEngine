#pragma once

class CCollider;

// 객체화 할 수 없는 추상 클래스
class CObject
{
private:
	wstring		m_strName;		// 오브젝트 식별 이름

	Vec2		m_vPos;
	Vec2		m_vScale;

	CCollider*	m_pCollider;	// nullptr이라면 콜라이더가 필요 없는 오브젝트들(배경이나 ui 등)

	bool		m_bAlive;		// 활성화, 비활성화 -> 비활성화되면 다음 프레임에 삭제

public:
	CObject();
	virtual ~CObject();

	friend class CEventMgr;

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	void SetPos(Vec2 vPos) { m_vPos = vPos; }
	void SetScale(Vec2 vScale) { m_vScale = vScale; }
private:
	void SetDead() { m_bAlive = false; }	// 이벤트 매니저만 접근, 자식도 접근 불가

public:
	wstring GetName() { return m_strName; }
	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }
	CCollider* GetCollider() { return m_pCollider; }

	bool IsDead() { return !m_bAlive; }

public:
	void CreateCollider();
	virtual void OnCollision(CCollider* _pOther) {};
	virtual void OnCollisionEnter(CCollider* _pOther) {};
	virtual void OnCollisionExit(CCollider* _pOther) {};

public:
	virtual void Update() = 0; // 순수 가상 함수 -> 오브젝트들의 Update는 모두 기능이 다름 (다형성)
	virtual void FinalUpdate() final; // final 키워드를 사용해서 오버라이딩을 막아준다
	virtual void Render(HDC hdc);

	void ComponetRender(HDC hdc);
};