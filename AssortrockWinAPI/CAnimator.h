#pragma once

class CObject;
class CTexture;
class CAnimation;

class CAnimator
{
private:
	map<wstring, CAnimation*>	m_mapAnim;		// ��� �ִϸ��̼� ���
	CAnimation*					m_pCurAnim;		// ���� ������� �ִϸ��̼�
	CObject*					m_pOwner;		// �ִϸ��̼� ���� ������Ʈ

public:
	CAnimator();
	~CAnimator();

	friend class CObject;

public:
	void CreateAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLeftTop, Vec2 _vSliceSize, Vec2 _vStep, UINT _iFrameCount);
	void FindAnimation();
	void Play();

public:
	void Update();
	void Render(HDC hdc);
};

