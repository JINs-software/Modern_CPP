//==================================================================
// 실습 과제
// pclaf를 이용해서 마우스 클릭으로 윈도우에 선을 그림
//==================================================================
#pragma once
#include "pclaf.h"

// Customized Application
class PenApp : public Application
{
	/**
	* [public]
		* 패키지(캡슐화된 클래스) 외부에 인터페이스를 제공
	*/
public:
	// 클래스 인터페이스 정의
	PenApp(const TCHAR*, int, int, int, int);
	void mouseDown(int, int);
	void paint();

	// 펜 위치를 위한 데이터 필드
	/* 
	* [클래스 내 멤버 초기화(in-class member initialization)]
		* 멤버 변수들을 생성자 함수의 구현에서 초기화하지 않고, 
		* 클래스의 인터페이스 정의에서 바로 초기화함.
	*/
	int oldx = 0;
	int oldy = 0;
	int newx = 0;
	int newy = 0;
};