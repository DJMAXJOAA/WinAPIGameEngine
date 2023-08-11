#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);
private:

public:
	CUIMgr();
	~CUIMgr();

public:
	void Update();

private:
	// 부모 UI 내에서 실제로 타겟팅 된 UI를 찾아서 반환(자식 UI들까지 우선 검사)
	CUI* GetTargetedUI(CUI* _pParentUI);
};

