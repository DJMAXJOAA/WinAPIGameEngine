#include "pch.h"
#include "CResMgr.h"

#include "CPathMgr.h"
#include "CTexture.h"

CResMgr::CResMgr()
{
}

CResMgr::~CResMgr()
{
    // ���� ��� �ؽ��� �Ҵ��� ���������ش�
    for (auto iter = m_mapTex.begin(); iter != m_mapTex.end(); iter++)
    {
        delete iter->second;
    }
}

// Ű����, ����θ� ���ڷ� �ִ´�
CTexture* CResMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
    // �ߺ��� Ű ���� ������, ���� ���� ����ϴ°� �ƴ϶�, ���� �˻� �� ������ ���� �ִ��� ��ȯ
    CTexture* pTex = FindTexture(_strKey);
    if (pTex != nullptr)
    {
        return pTex;
    }

    // Ű���� �˻� �غôµ� ��Ʈ�� ������ �ʿ� ������, �׶� ���� �ҷ��ͼ� ����� ���
    wstring strFilePath = CPathMgr::GetInstance()->GetContentPath();
    strFilePath += _strRelativePath;

    pTex = new CTexture;
    pTex->Load(strFilePath);
    pTex->SetRelativePath(_strRelativePath); // ������ �Բ� �־��ش�

    m_mapTex.insert(make_pair(_strKey, pTex));

    return pTex;
}

CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
    map<wstring, CTexture*>::iterator iter = m_mapTex.find(_strKey); // ���ͷ����� ������ ��ȯ
    if (iter == m_mapTex.end())
    {
        return nullptr; // ���� ������ ��
    }

    return iter->second; // �߰߰��� �ι�° ��, �� �̹��� ������ ����ִ� cTexture ��ü�� ��ȯ
}
