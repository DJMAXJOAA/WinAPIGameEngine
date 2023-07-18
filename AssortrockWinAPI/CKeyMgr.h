#pragma once

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	A,
	S,
	D,
	F,
	G,
	Z,
	X,
	C,
	V,
	B,
	ALT,
	LSHIFT,
	SPACE,
	CTRL,
	ENTER,
	ESC,

	LAST // ��
};

enum class KEY_STATE
{
	TAP,		// �� ���� ����
	HOLD,		// ������ �ִ� ��
	AWAY,		// �� �� ����
	NONE,		// ������ ����, �������� ������ ���� ����
};

struct tKeyInfo
{
	KEY_STATE	eState;		// Ű�� ���°�(enum)
	bool		bPrevPush;	// ���� �����ӿ� ����?
};

class CKeyMgr
{
	SINGLE(CKeyMgr);
private:
	vector<tKeyInfo> m_vecKey;

public:
	void Init();
	void Update();

public:
	KEY_STATE GetKeyState(KEY _eKey) { return m_vecKey[(int)_eKey].eState; }

private:
	CKeyMgr();
	~CKeyMgr();
};