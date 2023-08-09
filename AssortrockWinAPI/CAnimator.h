#pragma once

class CObject;
class CTexture;
class CAnimation;

class CAnimator
{
private:
	map<wstring, CAnimation*>	m_mapAnim;		// 모든 애니메이션 목록
	CAnimation*					m_pCurAnim;		// 현재 재생중인 애니메이션
	CObject*					m_pOwner;		// 애니메이션 소유 오브젝트

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

