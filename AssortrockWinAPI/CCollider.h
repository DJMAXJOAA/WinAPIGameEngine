#pragma once

class CObject;

class CCollider
{
private:
	CObject* m_pOwner;		// 콜라이더가 붙어있는 오브젝트의 정보를 알아야 한다(그래야 따라다니니깐)
	Vec2	 m_vOffsetPos;	// 기준 좌표(부착된 오브젝트의 좌표)부터의 상대적인 거리
	Vec2	 m_vFinalPos;	// FinalUpdate()를 통해 계산된 최종 콜라이더 위치(오프셋+좌표값) -> 매 프레임 계산해서 갱신

	Vec2	 m_vScale;		// 충돌체의 크기

public:
	void SetOwner(CObject* pObj) { m_pOwner = pObj; }
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	
public:
	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }

public:
	void FinalUpdate();
	void Render(HDC hdc);	// 테스트 할땐 켜놨다가, 배포때 끄기

public:
	CCollider();
	~CCollider();

	friend class CObject;
};