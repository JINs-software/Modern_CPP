#pragma once

template<typename RetType, typename... ArgTypes>
class JLambdaInterface {
public:
	// ȣ�� �������̽�
	RetType Call(ArgTypes... args) {
		// D-4
		return vCall(args...);	// ���� ���� �Լ� ȣ��
	}

	virtual RetType vCall(ArgTypes... args) = 0;
};

/**
* [JLambda]
* ���ٸ� ������ �����ϴ� Ŭ�����̱⿡ ���ø� ���ڿ� 'LAMBDA' Ÿ���� �ݵ�� �ʿ�
* LAMBDA ������ Ÿ���� ����� ���� ������, ���� �����ڸ� ���� ���ٸ� �����Ѵ�.
* 
* ���ÿ� �����ϴ� ���ٰ� JLambda ��ü�� ���ԵǸ鼭 ��(heap)�� �Ȱ��� ���ٸ� �����Ͽ� �����ϴ� ���̴�.
*/
template<typename LAMBDA, typename RetType, typename... ArgTypes>
class JLambda : public JLambdaInterface<RetType, ArgTypes...> {
public:
	/// [���� ���� ����]
	// ���ٴ� ��������δ� Ŭ������ �ƴϱ⿡ �⺻ �����ڰ� ����. ��� '�Ͻ��� ���� ������'�� ����Ѵ�.
	JLambda(const LAMBDA& lambda) {
		// ���޵� ���ٴ� � �Լ� �ȿ��� ���ǵǰ�, ���� �� ������ '�ӽ� ��ü'�̴�. 
		// ���� ���� �Ҵ�(new)�� ���� ���� ������ ���� ���� ���Ӱ� ������ ���ٸ� �����Ѵ�.
		m_LambdaPtr = new LAMBDA(lambda);	
	}
	~JLambda()
	{
		if (m_LambdaPtr) { delete m_LambdaPtr; }
	}

	// D-5
	// �������̽� �� ȣ�� �Լ� ������
	virtual RetType vCall(ArgTypes... args) override {
		// D-6
		return (*m_LambdaPtr)(args...);
	}

	// B-2
	LAMBDA* m_LambdaPtr;
};

/**
* [JFunction<T> ���� ����]
* ���� �ñ״�ó<RetType(ArgTypes...)>�� ���ø� ���ڷ� ���ԵǴ� 
* 'JFunction<RetType(ArgTypes...)>' Ŭ���� �����ϱ� ���� JFunction<T> ���� ������ �ʿ��ϴ�
*/
template<typename T>		
class JFunction;

template<typename RetType, typename... ArgTypes>
class JFunction<RetType(ArgTypes...)> {
public:
	JFunction() : m_LambdaInterface(NULL) {}

	/// [���� ������/���� ������ with 'LAMBDA ���ø�']
	// ������ Ÿ���� �˷����� ���� ���� ������/���� �����ڸ� ���� JFunction ��ü�� ���ٰ� ���Եȴ�.
	// �� ���� ������/���� �����ڸ� ���� ��μ� LAMBDA�� Ÿ���� �ǹ��ϰ� �Ǹ� JLambda ��ü�� �����ϰ�,
	template<typename LAMBDA>	
	JFunction(const LAMBDA& lambda) {
		// ������ �����͸� �θ� Ŭ���� ������(�������̽�)�� ����� ����
		m_LambdaInterface = new JLambda<LAMBDA, RetType, ArgTypes...>(lambda);
	}
	template<typename LAMBDA>	
	JFunction<RetType(ArgTypes...)>& operator=(const LAMBDA& lambda) {
		if (m_LambdaInterface) { delete m_LambdaInterface; }

		//							" "
		m_LambdaInterface = new JLambda<LAMBDA, RetType, ArgTypes...>(lambda);
		return *this;
	}

	/// [�Լ� ��ü -> 'operator()' ������!]
	// JFunction�� ����� �������̽� ������ �Լ� ��ü�μ� �۵��ȴ�.
	// ���� operator()�� �������Ͽ� �Լ� ��ü�� ����� �����.
	// �������̽� �Լ��� ���� ���������� ���� �Լ� ȣ����� �����Ѵ�.
	RetType operator()(ArgTypes... args) {
		return m_LambdaInterface->Call(args...);
	}

	/// [JLambdaInterface ������ ���]
	// ���ٸ� ���� �����ϱ� ���ؼ��� ���� Ÿ���� �˰� �־�� �Ѵ�.
	// ������ JFunction�� �����ϴ� �������� ���� ���� ���ø� ���ڴ� ���� �Լ� �ñ״�ó ���̴�.
	// ���� ���� ���ٸ� ������ Ŭ����(JLambda)�� ���� �������̽� Ŭ������ ������ ���� ����� �д�.
	// 'Call' �������̽� �Լ� ȣ�� �� ���������� ���� ��ü�� �Լ� ȣ���� ���� �Լ� ������� ȣ��ȴ�.
	JLambdaInterface<RetType, ArgTypes...>* m_LambdaInterface;
};