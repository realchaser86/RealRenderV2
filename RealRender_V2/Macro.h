#pragma once
#include "stdafx.h"

#define ALIGNED16(OBJECT)\
public:\
	void* operator new(size_t size){ return (OBJECT*)_aligned_malloc(sizeof(OBJECT), 16); } \
	void operator delete(void* ptr) { _aligned_free(ptr); }

#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))

#define	GET_INSTANCE(p)		p::GetInstance()