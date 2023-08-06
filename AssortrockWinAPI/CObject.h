#pragma once

class CCollider;

// ��üȭ �� �� ���� �߻� Ŭ����
class CObject
{
private:
	Vec2 m_vPos;
	Vec2 m_vScale;

	CCollider* m_pCollider;	// nullptr�̶�� �ݶ��̴��� �ʿ� ���� ������Ʈ��(����̳� ui ��)

public:
	CObject();
	virtual ~CObject();

public:
	void SetPos(Vec2 vPos) { m_vPos = vPos; }
	void SetScale(Vec2 vScale) { m_vScale = vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }
	CCollider* GetCollider() { return m_pCollider; }

	void CreateCollider();

public:
	virtual void Update() = 0; // ���� ���� �Լ� -> ������Ʈ���� Update�� ��� ����� �ٸ� (������)
	virtual void FinalUpdate() final; // final Ű���带 ����ؼ� �������̵��� �����ش�
	virtual void Render(HDC hdc);

	void ComponetRender(HDC hdc);
};