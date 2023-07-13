#pragma once
class CCore
{
private:
	static CCore* g_pInst;

public:
	static CCore* GetInstance()
	{
		// 최초 호출 ( 단 한번만 힙영역에 동적할당 )
		if (g_pInst == nullptr)
		{
			g_pInst = new CCore;
		}

		// 2번 이상 호출 (포인터만 반환)
		return g_pInst;
	}

	static void Release()
	{
		if (nullptr != g_pInst)
		{
			delete g_pInst;
			g_pInst = nullptr;
		}
	}

private:
	CCore();
	~CCore();
};
