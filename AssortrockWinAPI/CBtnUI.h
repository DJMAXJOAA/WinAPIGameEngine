#pragma once
#include "CUI.h"

class CBtnUI :
    public CUI
{
private:

public:
    CBtnUI();
    ~CBtnUI();

public:
    virtual void MouseOn();
    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();
};
