#pragma once
#include <iostream>
#include <vector>
using namespace std;

/* [functor(�Լ� ��ü)]
	* ��ü�� ���������� ��ġ �Լ�ó�� ����� �� �ִ�.
	* �Լ� ��ü�� ǥ�� ���ø� ���̺귯���� �����̳ʿ� �˰��� �ſ� �����ϰ� ����
	* (ǥ�� ���ø� ���̺귯���� �˰��򿡼� �Լ� ��ü�� '�ݹ�(call-back)'���� Ȱ��ȴ�.)
	
	* 'operator()'�� �����ε��Ͽ� functor Ŭ������ ������ �� �ִ�.
	* ��, Ŭ������ ���ǿ��� �Լ� ȣ�� �����ڸ� �����ε��� �ָ� �Լ� ��ü�� �����ϴ� Ŭ�����μ��� ������ ����
	
	* functor�� ����: ��ü�μ� �����ϱ⿡ ������ ������ ������ �� ����
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

/* [�ݹ�(call-back)]
	* ǥ�� ���ø� ���̺귯���� �˰��� �� find_if �Լ��� '������(predicate)'�� ����Ѵ�.
	* Ŭ���� Ÿ���� ��ü�� ���� �����̳ʸ� find_if �˰��򿡼� ����ϱ� ���ؼ� ���Ҹ�
	* � ������� ã�� �� ������ �Լ��� �Ķ���ͷ� �Ѱ��ش�.
	* �̷��� �Լ��� '������'�� '�ݹ� �Լ�'��� �θ���.
	* -> �Լ� ��ü�� ���� ǥ������ ����ϴ� ���� �Ϲ����̴�.
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
		return os; // ostream ��ü�� ��ȯ�Ͽ� ���� ȣ�� ����
	}
};

// �ݹ����� Ȱ��� functor Ŭ���� 
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
	// => find_if�� �Լ� ��ü ������ �ݹ� ����, 'cmpFunctor'
	auto iter = find_if(Rects.begin(), Rects.end(), cmpFunctor);
									
	if (iter != Rects.end()) {
		cout << "������ 1500 �̻��� ù ��° �簢��: " << *iter << endl;
	}
	else {
		cout << "����" << endl;
	}
}