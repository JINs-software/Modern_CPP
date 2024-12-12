#include "HDR.h"

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

	/********************************
	* initialization_list.h
	********************************/
	{
		Example_Initialization_List();
	}

	/********************************
	* uniform_initializer.h
	********************************/
	{
		Example_Uniform_Initializer();
	}


	/********************************
	* binding_and_casting.h
	********************************/
	{
		Example_Binding_Casting();
	}

	/********************************
	* lambda.h
	********************************/
	{
		cout << "Example_Labmda_with_Algorithm()" << endl;
		Example_Labmda_with_Algorithm();

		cout << "Example_Lambda_Capture()" << endl;
		Example_Lambda_Capture();
	}
}