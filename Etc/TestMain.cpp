#include "nullptr.h"
#include "smart_pointer.h"
#include "constexpr.h"
#include "smart_pointer_practice.h"
#include "functor.h"

int main() {

	/********************************
	* nullptr.h
	********************************/
	{
		func(NULL);							// -> func(int) ȣ��
		// NULL ��ũ�δ� '�� ������'�� �ǹ��ϹǷ�, func(double*)�� ȣ���� ���
		// ������ �����Ϸ��� ���� '0'���� ���ߵǱ⿡ func(int)�� ȣ��ȴ�.

		// �ذ� ���
		// (1) double* Ÿ������ ���� ĳ���� ����
		func(static_cast<double*>(NULL));		// -> func(double*) ȣ��
		// (2) NULL ��ũ�� ��� 'nullptr'�� ���
		func(nullptr);							// -> func(double*) ȣ��
	}

	/********************************
	* smart_pointer.h
	********************************/
	{
		// [shared_ptr, weak_ptr]
		Example_SmaprtPointer();

		// [��ȯ ���� ����]
		Example_CircularReferenceProblem();
		// -> "A ��ü ������ ����"
		// -> "B ��ü ������ ����"

		// [��ȯ ���� ���� �ذ�]
		Example_CircularReferenceProblem_Solve();
		// -> "A destroyed"
		// -> "B destroyed"

		// [unique_ptr]
		Example_Unique_Ptr();
	}

	/********************************
	* constexpr.h
	********************************/
	{
		Example_ConstExpr();
	}

	/********************************
	* smart_pointer_practice.h
	********************************/
	{
		cout << "Practice_RawPointer();" << endl;
		Practice_RawPointer();

		cout << "Practice_SmartPointer();" << endl;
		Practice_SmartPointer();
	}

	/********************************
	* functor.h
	********************************/
	{
		Example_Functor();

		Example_STL_Algorithm_CallBack();
	}
}