#pragma once

// �̱��� ��ü �ҷ�����
#define SINGLE(type) public:\
static type* GetInstance()\
{\
static type mgr;\
return &mgr;\
}