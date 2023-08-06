#pragma once
class CPathMgr
{
	SINGLE(CPathMgr);
private:
	wchar_t		m_szContentPath[255];	// 윈도우 최대 글자 255자 제한

private:
	CPathMgr();
	~CPathMgr();

public:
	void Init();
	const wchar_t* GetContentPath() { return m_szContentPath; }
};

