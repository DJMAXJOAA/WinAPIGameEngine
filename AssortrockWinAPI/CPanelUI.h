#pragma once

#include "CUI.h"
class CPanelUI :
    public CUI
{
private:
    Vec2        m_vDragStart;

public:
    CPanelUI();
    ~CPanelUI();

public:
    virtual void MouseOn();
    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();
}; 

