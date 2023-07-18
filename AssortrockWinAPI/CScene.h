#pragma once

class CObject;

class CScene
{
private:
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END];
	wstring m_strName;

protected:
	void AddObject(CObject* pObj, GROUP_TYPE eType) { m_arrObj[(UINT)eType].push_back(pObj); }

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	// 순수 가상함수 -> 직접 객체 생성이 불가능하다 (추상화 클래스)
	virtual void Enter() = 0; // Scene의 진입
	virtual void Exit() = 0; // Scene의 탈출

public:
	void Update();
	void Render(HDC hdc);

public:
	CScene();
	virtual ~CScene();
};

