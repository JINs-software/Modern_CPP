#pragma once

template<typename RetType, typename... ArgTypes>
class JLambdaInterface {
public:
	// 호출 인터페이스
	RetType Call(ArgTypes... args) {
		// D-4
		return vCall(args...);	// 내부 가상 함수 호출
	}

	virtual RetType vCall(ArgTypes... args) = 0;
};

/**
* [JLambda]
* 람다를 실제로 저장하는 클래스이기에 템플릿 인자에 'LAMBDA' 타입이 반드시 필요
* LAMBDA 포인터 타입의 멤버를 갖고 있으며, 복사 생성자를 통해 람다를 복사한다.
* 
* 스택에 존재하는 람다가 JLambda 객체에 대입되면서 힙(heap)에 똑같은 람다를 생성하여 보관하는 것이다.
*/
template<typename LAMBDA, typename RetType, typename... ArgTypes>
class JLambda : public JLambdaInterface<RetType, ArgTypes...> {
public:
	/// [람다 복사 생성]
	// 람다는 명시적으로는 클래스가 아니기에 기본 생성자가 없다. 대신 '암시적 복사 생성자'를 사용한다.
	JLambda(const LAMBDA& lambda) {
		// 전달된 람다는 어떤 함수 안에서 정의되고, 스택 내 생성된 '임시 객체'이다. 
		// 따라서 동적 할당(new)를 통한 복사 생성을 통해 힙에 새롭게 저장할 람다를 생성한다.
		m_LambdaPtr = new LAMBDA(lambda);	
	}
	~JLambda()
	{
		if (m_LambdaPtr) { delete m_LambdaPtr; }
	}

	// D-5
	// 인터페이스 단 호출 함수 재정의
	virtual RetType vCall(ArgTypes... args) override {
		// D-6
		return (*m_LambdaPtr)(args...);
	}

	// B-2
	LAMBDA* m_LambdaPtr;
};

/**
* [JFunction<T> 전방 선언]
* 람다 시그니처<RetType(ArgTypes...)>가 템플릿 인자로 대입되는 
* 'JFunction<RetType(ArgTypes...)>' 클래스 정의하기 위해 JFunction<T> 전방 선언이 필요하다
*/
template<typename T>		
class JFunction;

template<typename RetType, typename... ArgTypes>
class JFunction<RetType(ArgTypes...)> {
public:
	JFunction() : m_LambdaInterface(NULL) {}

	/// [복사 생성자/대입 연산자 with 'LAMBDA 템플릿']
	// 람다의 타입이 알려지는 순간 복사 생성자/대입 연산자를 통해 JFunction 객체에 람다가 대입된다.
	// 이 복사 생성자/대입 연산자를 통해 비로소 LAMBDA는 타입을 의미하게 되며 JLambda 객체를 생성하고,
	template<typename LAMBDA>	
	JFunction(const LAMBDA& lambda) {
		// 생성된 포인터를 부모 클래스 포인터(인터페이스)로 멤버에 저장
		m_LambdaInterface = new JLambda<LAMBDA, RetType, ArgTypes...>(lambda);
	}
	template<typename LAMBDA>	
	JFunction<RetType(ArgTypes...)>& operator=(const LAMBDA& lambda) {
		if (m_LambdaInterface) { delete m_LambdaInterface; }

		//							" "
		m_LambdaInterface = new JLambda<LAMBDA, RetType, ArgTypes...>(lambda);
		return *this;
	}

	/// [함수 객체 -> 'operator()' 재정의!]
	// JFunction는 사용자 인터페이스 형태의 함수 객체로서 작동된다.
	// 따라서 operator()을 재정의하여 함수 객체의 요건을 갖춘다.
	// 인터페이스 함수를 거쳐 내부적으로 람다 함수 호출까지 수행한다.
	RetType operator()(ArgTypes... args) {
		return m_LambdaInterface->Call(args...);
	}

	/// [JLambdaInterface 포인터 멤버]
	// 람다를 직접 저장하기 위해서는 람다 타입을 알고 있어야 한다.
	// 하지만 JFunction을 정의하는 시점에는 전달 가능 템플릿 인자는 오직 함수 시그니처 뿐이다.
	// 따라서 실제 람다를 저장할 클래스(JLambda)의 상위 인터페이스 클래스의 포인터 형을 멤버로 둔다.
	// 'Call' 인터페이스 함수 호출 시 내부적으로 람다 객체의 함수 호출이 가상 함수 방식으로 호출된다.
	JLambdaInterface<RetType, ArgTypes...>* m_LambdaInterface;
};