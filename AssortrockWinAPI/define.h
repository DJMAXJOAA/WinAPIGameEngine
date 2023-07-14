#pragma once

// ½Ì±ÛÅæ °´Ã¼ ºÒ·¯¿À±â
#define SINGLE(type) public:\
static type* GetInstance()\
{\
static type mgr;\
return &mgr;\
}