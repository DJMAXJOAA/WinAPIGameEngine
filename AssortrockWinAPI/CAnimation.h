#pragma once

class CAnimator;

class CAnimation
{
private:
	wstring		m_strName;
	CAnimator*	m_pAnimator;

public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;

public:
	const wstring& GetName() { return m_strName; }

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	
public:
	void Update();
	void Render(HDC hdc);
};

