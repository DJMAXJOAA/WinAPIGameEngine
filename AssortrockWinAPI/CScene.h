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

	// ���� �����Լ� -> ���� ��ü ������ �Ұ����ϴ� (�߻�ȭ Ŭ����)
	virtual void Enter() = 0; // Scene�� ����
	virtual void Exit() = 0; // Scene�� Ż��

public:
	void Update();
	void Render(HDC hdc);

public:
	CScene();
	virtual ~CScene();
};

