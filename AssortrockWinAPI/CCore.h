#pragma once
class CCore
{
private:
	static CCore* g_pInst;

public:
	static CCore* GetInstance()
	{
		// ���� ȣ�� ( �� �ѹ��� �������� �����Ҵ� )
		if (g_pInst == nullptr)
		{
			g_pInst = new CCore;
		}

		// 2�� �̻� ȣ�� (�����͸� ��ȯ)
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
