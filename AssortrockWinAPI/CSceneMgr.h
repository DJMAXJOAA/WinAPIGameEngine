#pragma once

class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr);

private:
	CScene* m_arrScene[(UINT)SCENE_TYPE::END];
	CScene* m_pCurScene;

private:
	CSceneMgr();
	~CSceneMgr();
	
public:
	void Init();
	void Update();
	void Render(HDC hdc);

public:
	CScene* GetcurScene() { return m_pCurScene; }
};

