#pragma once
#include "stdafx.h"

class MyRect
{
public:
	MyRect(UINT x1, UINT y1, UINT x2, UINT y2);
	~MyRect();

public:
	//���ο�ĵ�ǰֵ
	UINT uValue;//���ζ�������
	UINT x1;
	UINT y1;
	UINT x2;
	UINT y2;
};