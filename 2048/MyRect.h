#pragma once
#include "stdafx.h"

class MyRect
{
public:
	MyRect(UINT x1, UINT y1, UINT x2, UINT y2);
	~MyRect();

public:
	//矩形框的当前值
	UINT uValue;//矩形顶点坐标
	UINT x1;
	UINT y1;
	UINT x2;
	UINT y2;
};