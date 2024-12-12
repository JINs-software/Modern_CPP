#pragma once
#include <iostream>
#include <string>
#include <memory>	// smart_pointer header

using namespace std;

/*****************************************************************
* shared_ptr, weak_ptr 예제
*****************************************************************/
void Example_SmaprtPointer() {
	shared_ptr<string> sp1(new string("HurJin"));
	shared_ptr<string> sp2 = sp1;
	weak_ptr<string> wp1 = sp2;
	{
		// wp1을 통해 sp2를 sp3로 복사
		shared_ptr<string> sp3 = wp1.lock();
		if (sp3) {
			cout << "wp1을 통해 sp3 복사 완료" << endl;
		}

		weak_ptr<string> wp2(sp1);

		// [shared pointer 참조 정보(카운터)]
		//  string("HurJin") 객체의 참조 정보(카운터)
		//	- shared count: 3 (sp1, sp2, sp3)
		//	- weak count: 2 (wp1, wp2)

		// [make_shared]
		// new 연산자를 사용하는 것보다 성능적으로 최적화되어 있다. 
		// shared_ptr를 정의할 때 이 함수를 사용하는 것이 바람직.
		shared_ptr<int> sp4 = make_shared<int>(10);
	}	
	// -> sp3(문자열 객체), sp4(정수형 객체), wp2 자동 소멸
	// sp4의 경우 참조 카운터의 shared count 값이 0이 되어(weak count도 0),
	//								정수 객체 및 참조 정보 객체 모두 자동 소멸

	// [reset 호출 또는 nullptr 대입]
	// (1) reset 멤버 함수 호출 또는 (2) nullptr의 대입을 통해 참조 연결을 끊는다.
	sp1.reset();	// (1)
	sp2 = nullptr;	// (2)
	// -> shared count: 0
	// 문자열 원복 객체 자동 소멸
	// 단, wp1의 연결로 인해 weak count: 1 이므로 참조 정보 객체는 소멸되지 않은 상태

	// 이미 모든 shared_ptr 변수들이 소멸되거나 연결이 끊겨서 shared count: 0이 된 상태이다.
	// 따라서 sp5에는 nullptr로 초기화된다.
	shared_ptr<string> sp5 = wp1.lock();
	if (sp5) {
		cout << "조건 충족 구문 ..." << endl;
	}

	wp1.reset();
	// 마지막으로 wp1의 연결 또한 끊기기에 weak count 또한 0이 되기에,
	// 참조 정보 객체까지 자동으로 소멸된다.
}


/*****************************************************************
* shared_ptr로 인한 순환 참조 문제
*****************************************************************/
namespace smp {
	class B;

	class A {
	public:
		shared_ptr<B> b_ptr;
		~A() { cout << "A destroyed" << endl; }
	};

	class B {
	public:
		shared_ptr<A> a_ptr;
		~B() { cout << "B destroyed" << endl; }
	};
}
void Example_CircularReferenceProblem() {
	weak_ptr<smp::A> wpA;
	weak_ptr<smp::B> wpB;
	{
		shared_ptr<smp::A> ap = make_shared<smp::A>();
		shared_ptr<smp::B> bp = make_shared<smp::B>();
		ap->b_ptr = bp;
		bp->a_ptr = ap;

		wpA = ap;
		wpB = bp;
	}
	// -> ap의 소멸이 있지만, bp 객체 내부에서 ap가 가리키는 객체를 공유하여 참조하기에 소멸되지 않는다.
	// -> bp의 소멸이 있지만, ""

	shared_ptr<smp::A> ap = wpA.lock();
	if (ap) {
		cout << "A 객체 여전히 존재" << endl;
	}
	shared_ptr<smp::B> bp = wpB.lock();
	if (bp) {
		cout << "B 객체 여전히 존재" << endl;
	}
}


/*****************************************************************
* shared_ptr로 인한 순환 참조 문제 해결 with 'weak_ptr'
*****************************************************************/
namespace smp_solve {
	class B;

	class A {
	public:
		shared_ptr<B> b_ptr;
		~A() { cout << "A destroyed" << endl; }
	};

	class B {
	public:
		weak_ptr<A> a_ptr;
		~B() { cout << "B destroyed" << endl; }
	};
}
void Example_CircularReferenceProblem_Solve() {
	weak_ptr<smp_solve::A> wpA;
	weak_ptr<smp_solve::B> wpB;
	{
		shared_ptr<smp_solve::A> ap = make_shared<smp_solve::A>();
		shared_ptr<smp_solve::B> bp = make_shared<smp_solve::B>();
		ap->b_ptr = bp;
		bp->a_ptr = ap;

		wpA = ap;
		wpB = bp;
	}

	shared_ptr<smp_solve::A> ap = wpA.lock();
	if (ap) {
		// 출력 x
		cout << "A 객체 여전히 존재" << endl;
	}
	shared_ptr<smp_solve::B> bp = wpB.lock();
	if (bp) {
		// 출력 x
		cout << "B 객체 여전히 존재" << endl;
	}
}


/*****************************************************************
* unique_ptr 예시
*****************************************************************/
void Example_Unique_Ptr() {
	unique_ptr<int> p1(new int(5));
	
	// [소유권 이전]
	unique_ptr<int> p2;
	// p2 = p1;					// compile error..
	
	//unique_ptr<int> p3 = p1;	// compile error..
	// p1은 독점 포인터이므로 복사를 허용하지 않기에 컴파일 오류가 발생한다.

	unique_ptr<int> p3 = move(p1);
	// -> p3가 정수 객체(5)를 독점 소유하게 되고, p1변수에는 nullptr이 대입된다(소유권을 잃음).
	/** (unique_ptr 이동 생성자/대입연산자 pseudo)
	* unique_ptr(unique_ptr&& other) noexept 
	*	: ptr(other.ptr)
	* {
	*	other.ptr = nullptr;			// 다른 독점 포인터의 참조를 잃게 만든다.
	* }
	* 
	* unique_ptr& operator=(unique_ptr&& other) noexcept {
	*	if(this != &other) {	// 자기 자긴과의 대입 방지
	*		delete this->ptr;
	*		this->ptr = other.ptr;
	*		other.ptr = nullptr;		// 다른 독점 포인터의 참조를 잃게 만든다.
	*	}
	*	return *this;
	* }
	*/
	
	cout << p1.get() << endl;	// -> 0000000000000000	(p1은 소유권을 잃음)
	cout << p3.get() << endl;	// -> 0000027A5D076540	(p2가 현재 독점 중)
	cout << *p3 << endl;		// -> 5

	auto a = *p3;
	cout << a << endl;			// -> 5 

	// [unique_ptr 레퍼런스]
	// 복사가 수행되는 것은 아니므로, unique_ptr의 레퍼런스 정의 가능
	auto& a2 = p3;
	cout << *a2 << endl;		// -> 5

	// [make_unique]
	// make_shared와 마찬가지로 new 연산자보다 성능이 우수하다.
	unique_ptr<int> p4(make_unique<int>(10));
	cout << *p4 << endl;	// -> 10
	// [reset]
	// unique_ptr 객체에 nullptr을 대입하는 것과 마찬가지
	p4.reset();
}