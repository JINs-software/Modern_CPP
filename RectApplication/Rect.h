// RECTANGLE CLASS
#pragma once

/* [���� ����(forward declaration)]
	* 'pclaf.h'�� ���ǵ� 'Application' Ŭ������ ���� ����(����) ����
	* ���� ��� ���Ͽ��� Application Ŭ������ �Լ��� �Ķ���� Ÿ�����θ� ���Ǿ��⿡,
	* pclaf.h�� �����ϱ� ����, ���� ������ ���� �����Ϸ��� Ŭ������ ���縸�� �˸����� �ϴ� ���̴�.
	* ���� ������ ����� �Ǵ� Rect.cpp���� pclaf.h�� ���ԵǾ�� �Ѵ�.
*/
class Application;	// ����(����) ����

class Rect
{
public:
	// constructor
	Rect(int, int, int, int);
	~Rect();

	// operations
	void moveTo(int, int);
	bool includes(int, int);
	virtual void draw(Application&);

	// data fields
	int upperLeftX;
	int upperLeftY;
	int lowerRightX;
	int lowerRightY;
};