#include "pch.h"
#include "CAnimator.h"

#include "CObject.h"
#include "CTexture.h"
#include "CAnimation.h"


CAnimator::CAnimator()
	: m_pOwner(nullptr)
	, m_pCurAnim(nullptr)
{
}

CAnimator::~CAnimator()
{
	SafeDeleteMap(m_mapAnim);
}

void CreateAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLeftTop, Vec2 _vSliceSize, Vec2 _vStep, UINT _iFrameCount)
{
	CAnimation* pAnim = new CAnimation;
	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;
	m_mapAnim.insert(make_pair(_strName, pAnim));
}

void CAnimator::FindAnimation()
{
}

void CAnimator::Play()
{
}

void CAnimator::Update()
{
	if (m_pCurAnim != nullptr)
		m_pCurAnim->Update();
}

void CAnimator::Render(HDC hdc)
{
	if (m_pCurAnim != nullptr)
		m_pCurAnim->Render(hdc);
}
