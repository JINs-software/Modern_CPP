//==================================================================
// �ǽ� ����
// pclaf�� �̿��ؼ� ���콺 Ŭ������ �����쿡 ���� �׸�
//==================================================================
#pragma once
#include "pclaf.h"

// Customized Application
class PenApp : public Application
{
	/**
	* [public]
		* ��Ű��(ĸ��ȭ�� Ŭ����) �ܺο� �������̽��� ����
	*/
public:
	// Ŭ���� �������̽� ����
	PenApp(const TCHAR*, int, int, int, int);
	void mouseDown(int, int);
	void paint();

	// �� ��ġ�� ���� ������ �ʵ�
	/* 
	* [Ŭ���� �� ��� �ʱ�ȭ(in-class member initialization)]
		* ��� �������� ������ �Լ��� �������� �ʱ�ȭ���� �ʰ�, 
		* Ŭ������ �������̽� ���ǿ��� �ٷ� �ʱ�ȭ��.
	*/
	int oldx = 0;
	int oldy = 0;
	int newx = 0;
	int newy = 0;
};