#pragma once
#include <iostream>
#include <string>
#include <memory>	// smart_pointer header

using namespace std;

/*****************************************************************
* shared_ptr, weak_ptr ����
*****************************************************************/
void Example_SmaprtPointer() {
	shared_ptr<string> sp1(new string("HurJin"));
	shared_ptr<string> sp2 = sp1;
	weak_ptr<string> wp1 = sp2;
	{
		// wp1�� ���� sp2�� sp3�� ����
		shared_ptr<string> sp3 = wp1.lock();
		if (sp3) {
			cout << "wp1�� ���� sp3 ���� �Ϸ�" << endl;
		}

		weak_ptr<string> wp2(sp1);

		// [shared pointer ���� ����(ī����)]
		//  string("HurJin") ��ü�� ���� ����(ī����)
		//	- shared count: 3 (sp1, sp2, sp3)
		//	- weak count: 2 (wp1, wp2)

		// [make_shared]
		// new �����ڸ� ����ϴ� �ͺ��� ���������� ����ȭ�Ǿ� �ִ�. 
		// shared_ptr�� ������ �� �� �Լ��� ����ϴ� ���� �ٶ���.
		shared_ptr<int> sp4 = make_shared<int>(10);
	}	
	// -> sp3(���ڿ� ��ü), sp4(������ ��ü), wp2 �ڵ� �Ҹ�
	// sp4�� ��� ���� ī������ shared count ���� 0�� �Ǿ�(weak count�� 0),
	//								���� ��ü �� ���� ���� ��ü ��� �ڵ� �Ҹ�

	// [reset ȣ�� �Ǵ� nullptr ����]
	// (1) reset ��� �Լ� ȣ�� �Ǵ� (2) nullptr�� ������ ���� ���� ������ ���´�.
	sp1.reset();	// (1)
	sp2 = nullptr;	// (2)
	// -> shared count: 0
	// ���ڿ� ���� ��ü �ڵ� �Ҹ�
	// ��, wp1�� ����� ���� weak count: 1 �̹Ƿ� ���� ���� ��ü�� �Ҹ���� ���� ����

	// �̹� ��� shared_ptr �������� �Ҹ�ǰų� ������ ���ܼ� shared count: 0�� �� �����̴�.
	// ���� sp5���� nullptr�� �ʱ�ȭ�ȴ�.
	shared_ptr<string> sp5 = wp1.lock();
	if (sp5) {
		cout << "���� ���� ���� ..." << endl;
	}

	wp1.reset();
	// ���������� wp1�� ���� ���� ����⿡ weak count ���� 0�� �Ǳ⿡,
	// ���� ���� ��ü���� �ڵ����� �Ҹ�ȴ�.
}


/*****************************************************************
* shared_ptr�� ���� ��ȯ ���� ����
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
	// -> ap�� �Ҹ��� ������, bp ��ü ���ο��� ap�� ����Ű�� ��ü�� �����Ͽ� �����ϱ⿡ �Ҹ���� �ʴ´�.
	// -> bp�� �Ҹ��� ������, ""

	shared_ptr<smp::A> ap = wpA.lock();
	if (ap) {
		cout << "A ��ü ������ ����" << endl;
	}
	shared_ptr<smp::B> bp = wpB.lock();
	if (bp) {
		cout << "B ��ü ������ ����" << endl;
	}
}


/*****************************************************************
* shared_ptr�� ���� ��ȯ ���� ���� �ذ� with 'weak_ptr'
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
		// ��� x
		cout << "A ��ü ������ ����" << endl;
	}
	shared_ptr<smp_solve::B> bp = wpB.lock();
	if (bp) {
		// ��� x
		cout << "B ��ü ������ ����" << endl;
	}
}


/*****************************************************************
* unique_ptr ����
*****************************************************************/
void Example_Unique_Ptr() {
	unique_ptr<int> p1(new int(5));
	
	// [������ ����]
	unique_ptr<int> p2;
	// p2 = p1;					// compile error..
	
	//unique_ptr<int> p3 = p1;	// compile error..
	// p1�� ���� �������̹Ƿ� ���縦 ������� �ʱ⿡ ������ ������ �߻��Ѵ�.

	unique_ptr<int> p3 = move(p1);
	// -> p3�� ���� ��ü(5)�� ���� �����ϰ� �ǰ�, p1�������� nullptr�� ���Եȴ�(�������� ����).
	/** (unique_ptr �̵� ������/���Կ����� pseudo)
	* unique_ptr(unique_ptr&& other) noexept 
	*	: ptr(other.ptr)
	* {
	*	other.ptr = nullptr;			// �ٸ� ���� �������� ������ �Ұ� �����.
	* }
	* 
	* unique_ptr& operator=(unique_ptr&& other) noexcept {
	*	if(this != &other) {	// �ڱ� �ڱ���� ���� ����
	*		delete this->ptr;
	*		this->ptr = other.ptr;
	*		other.ptr = nullptr;		// �ٸ� ���� �������� ������ �Ұ� �����.
	*	}
	*	return *this;
	* }
	*/
	
	cout << p1.get() << endl;	// -> 0000000000000000	(p1�� �������� ����)
	cout << p3.get() << endl;	// -> 0000027A5D076540	(p2�� ���� ���� ��)
	cout << *p3 << endl;		// -> 5

	auto a = *p3;
	cout << a << endl;			// -> 5 

	// [unique_ptr ���۷���]
	// ���簡 ����Ǵ� ���� �ƴϹǷ�, unique_ptr�� ���۷��� ���� ����
	auto& a2 = p3;
	cout << *a2 << endl;		// -> 5

	// [make_unique]
	// make_shared�� ���������� new �����ں��� ������ ����ϴ�.
	unique_ptr<int> p4(make_unique<int>(10));
	cout << *p4 << endl;	// -> 10
	// [reset]
	// unique_ptr ��ü�� nullptr�� �����ϴ� �Ͱ� ��������
	p4.reset();
}