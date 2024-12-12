#pragma once
#include <iostream>
#include <vector>
using namespace std;

/* [functor(함수 객체)]
	* 객체를 문법적으로 마치 함수처럼 사용할 수 있다.
	* 함수 객체는 표준 템플릿 라이브러리의 컨테이너와 알고리즘에 매우 유용하게 사용됨
	* (표준 템플릿 라이브러리의 알고리즘에서 함수 객체는 '콜백(call-back)'으로 활용된다.)
	
	* 'operator()'를 오버로딩하여 functor 클래스를 정의할 수 있다.
	* 즉, 클래스의 정의에서 함수 호출 연산자만 오버로딩해 주면 함수 객체를 생성하는 클래스로서의 조건은 만족
	
	* functor의 장점: 객체로서 존재하기에 고유한 문맥을 유지할 수 있음
*/

class Functor {
public:
	void operator()(int k) const {
		cout << "Functor: passed parameter = " << k << endl;
	}
};

void Example_Functor() {
	Functor functor;
	functor(4);
}

/* [콜백(call-back)]
	* 표준 템플릿 라이브러리의 알고리즘 중 find_if 함수는 '조건자(predicate)'를 사용한다.
	* 클래스 타입의 객체를 담은 컨테이너를 find_if 알고리즘에서 사용하기 위해서 원소를
	* 어떤 방식으로 찾을 지 정의한 함수를 파라미터로 넘겨준다.
	* 이러한 함수를 '조건자'나 '콜백 함수'라고 부른다.
	* -> 함수 객체나 람다 표현식을 사용하는 것이 일반적이다.
*/
struct Rect {
	int lx, rx, uy, dy;
	Rect(int x1, int y1, int x2, int y2) {
		if (x1 < x2) { lx = x1; rx = x2; }
		else { lx = x2; rx = x1; }

		if (y1 < y2) { dy = y1; uy = y2; }
		else { dy = y2; uy = y1; }
	}

	int area() const {
		return (rx - lx) * (uy - dy);
	}

	friend std::ostream& operator<<(std::ostream& os, const Rect& r) {
		os << r.area();
		return os; // ostream 객체를 반환하여 연쇄 호출 가능
	}
};

// 콜백으로 활용될 functor 클래스 
class FindAreaRectFunctor {
public:
	FindAreaRectFunctor(int cmpArea) : compareArea(cmpArea) {}
	bool operator()(Rect& r) {
		return (r.area() >= compareArea ? true : false);
	}

private:
	int compareArea;
};

void Example_STL_Algorithm_CallBack() {
	vector<Rect> Rects;
	Rects.push_back({ 30, 40, 70, 70 });
	Rects.push_back({ 100, 90, 130, 150 });
	Rects.push_back({ 20, 30, 50, 50 });
	Rects.push_back({ 100, 100, 150, 150 });

	FindAreaRectFunctor cmpFunctor(1500);
	// => find_if에 함수 객체 형태의 콜백 전달, 'cmpFunctor'
	auto iter = find_if(Rects.begin(), Rects.end(), cmpFunctor);
									
	if (iter != Rects.end()) {
		cout << "면적이 1500 이상인 첫 번째 사각형: " << *iter << endl;
	}
	else {
		cout << "없음" << endl;
	}
}