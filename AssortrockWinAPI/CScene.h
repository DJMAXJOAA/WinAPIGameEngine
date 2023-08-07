#pragma once

class CObject;

class CScene
{
private:
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END];
	wstring m_strName;

public:
	CScene();
	virtual ~CScene();

public:
	void AddObject(CObject* pObj, GROUP_TYPE eType) { m_arrObj[(UINT)eType].push_back(pObj); }

public:
	const wstring& GetName() { return m_strName; }
	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) { return m_arrObj[(UINT)_eType]; } // ���۷����� �ֵ�, ������ �Ұ����ϰ� const

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }

	// ���� �����Լ� -> ���� ��ü ������ �Ұ����ϴ� (�߻�ȭ Ŭ����)
	virtual void Enter() = 0; // Scene�� ����
	virtual void Exit() = 0; // Scene�� Ż��

public:
	void Update();
	void FinalUpdate(); // ������ �۾�(��� ������Ʈ ������, Ȯ�� �� render)
	void Render(HDC hdc);
};

