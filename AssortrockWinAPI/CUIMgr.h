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
	// �θ� UI ������ ������ Ÿ���� �� UI�� ã�Ƽ� ��ȯ(�ڽ� UI����� �켱 �˻�)
	CUI* GetTargetedUI(CUI* _pParentUI);
};

