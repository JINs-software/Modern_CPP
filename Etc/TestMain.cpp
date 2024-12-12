#include "HDR.h"

int main() {

	/********************************
	* nullptr.h
	********************************/
	{
		func(NULL);							// -> func(int) 호출
		// NULL 매크로는 '널 포인터'를 의미하므로, func(double*)의 호출을 기대
		// 하지만 컴파일러에 의해 '0'으로 유추되기에 func(int)가 호출된다.

		// 해결 방법
		// (1) double* 타입으로 정적 캐스팅 수행
		func(static_cast<double*>(NULL));		// -> func(double*) 호출
		// (2) NULL 매크로 대신 'nullptr'을 사용
		func(nullptr);							// -> func(double*) 호출
	}

	/********************************
	* smart_pointer.h
	********************************/
	{
		// [shared_ptr, weak_ptr]
		Example_SmaprtPointer();

		// [순환 참조 문제]
		Example_CircularReferenceProblem();
		// -> "A 객체 여전히 존재"
		// -> "B 객체 여전히 존재"

		// [순환 참조 문제 해결]
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