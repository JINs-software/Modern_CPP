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

/* [���� ���ε� vs ���� ���ε�]: ��� �Լ��� ȣ�⿡ ���� �ش� ��� �Լ��� ã�� �����ϴ� �� ���� ���
	* ���� ���ε�(������ �� ���ε�): ������ �� ��� �Լ� ����(���ε�)
	* ���� ���ε�(���� ���� �� ���ε�): ���� ������ ����
		* 'virtaul' Ű���� Ű���尡 ���� �� ���� ���ε� ���
*/

void Example_Binding_Casting() {
	D d1;
	d1.y();				// -> "A::y" (���� ���ε�, ���� Ŭ�����κ��� ��ӹ��� y() �Լ� ȣ��)
	D d2;	
	d2.z();				// -> "D::z" (���� ���ε�)

	// ��-ĳ����(D->C)
	shared_ptr<C> cptr1 = make_shared<D>();
	C& cref = d1;
	cptr1->z();			// -> "D::z" (���� ���ε�)
	cref.z();			// -> "D::z" (���� ���ε�)

	// ��-ĳ����(D->C): �����̽� �߻�(�޸� ���)
	C c1 = d1;			// c1�� ���� ��ü�� C�̴�.
						// d1 ��ü�� ���� ���� ������ ���� ��
	c1.z();				// -> "C::z"

	// �ٿ� ĳ����(C->D)
	shared_ptr<C> cptr2 = make_shared<C>();
	//shared_ptr<D> dptr = cptr2;	// compile error..
	shared_ptr<D> dptr = static_pointer_cast<D>(cptr2);
	dptr->z();			// -> "C::z" 
						// ���� ��ü�� C �ν��Ͻ��̹Ƿ� C�� z �Լ� ȣ��

	// �ٿ� ĳ����(C->D): ������ ���� �߻�
	C c2;
	//d2 = static_cast<D>(c2);		// compile error..

}

