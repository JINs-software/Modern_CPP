#pragma once
#include <iostream>
#include <memory>
using namespace std;

class A {
public:
	void x() {	
		cout << "A::x" << endl;
	}
	virtual void y() {
		cout << "A::y" << endl;
	}
};

class B : public A {
public:
	void z() {
		cout << "B::z" << endl;
	}
};

class C : public A {
public:
	void x() {
		cout << "C::x" << endl;
	}
	virtual void z() {
		cout << "C::z" << endl;
	}
};

class D : public C {
public:
	virtual void z() {
		cout << "D::z" << endl;
	}
};

class E : public C {
public:
	void m() {
		cout << "E::m" << endl;
	}
};

/* [정적 바인딩 vs 동적 바인딩]: 멤버 함수의 호출에 대해 해당 멤버 함수를 찾아 결합하는 두 가지 방법
	* 정적 바인딩(컴파일 시 바인딩): 컴파일 시 멤버 함수 결합(바인딩)
	* 동적 바인딩(실행 시점 시 바인딩): 실행 시점에 결합
		* 'virtaul' 키워드 키워드가 붙을 시 동적 바인딩 사용
*/

void Example_Binding_Casting() {
	D d1;
	d1.y();				// -> "A::y" (정적 바인딩, 조상 클래스로부터 상속받은 y() 함수 호출)
	D d2;	
	d2.z();				// -> "D::z" (정적 바인딩)

	// 업-캐스팅(D->C)
	shared_ptr<C> cptr1 = make_shared<D>();
	C& cref = d1;
	cptr1->z();			// -> "D::z" (동적 바인딩)
	cref.z();			// -> "D::z" (동적 바인딩)

	// 업-캐스팅(D->C): 슬라이싱 발생(메모리 축소)
	C c1 = d1;			// c1의 원본 객체는 C이다.
						// d1 객체를 통해 복사 생성된 것일 뿐
	c1.z();				// -> "C::z"

	// 다운 캐스팅(C->D)
	shared_ptr<C> cptr2 = make_shared<C>();
	//shared_ptr<D> dptr = cptr2;	// compile error..
	shared_ptr<D> dptr = static_pointer_cast<D>(cptr2);
	dptr->z();			// -> "C::z" 
						// 원본 객체는 C 인스턴스이므로 C의 z 함수 호출

	// 다운 캐스팅(C->D): 컴파일 에러 발생
	C c2;
	//d2 = static_cast<D>(c2);		// compile error..

}

