#pragma once

#include <iostream>
#include <memory>
using namespace std;

struct CoinMoney {
	int c50;
	int c100;
	int c500;
};

/********************************************************
* raw_pointer
********************************************************/
inline int GetValue(const CoinMoney& cm) {
	return (50 * cm.c50 + 100 * cm.c100 + 500 * cm.c500);
}

CoinMoney* AddCoinMoney(const CoinMoney* cm1, const CoinMoney* cm2) {
	CoinMoney* psum = new CoinMoney();
	psum->c50 = cm1->c50 + cm2->c50;
	psum->c100 = cm1->c100 + cm2->c100;
	psum->c500 = cm1->c500 + cm2->c500;

	return psum;
}

void PrintCoinMoney(const CoinMoney& cm) {
	cout << "50원: " << cm.c50 << endl;
	cout << "100원: " << cm.c100 << endl;
	cout << "500원: " << cm.c500 << endl;
	cout << "total: " << GetValue(cm) << "원" << endl;
}

void Practice_RawPointer() {
	CoinMoney* pm1 = new CoinMoney();
	CoinMoney* pm2 = new CoinMoney();
	pm1->c50 = 1;
	pm1->c100 = 2;
	pm1->c500 = 3;
	PrintCoinMoney(*pm1);

	*pm2 = *pm1;
	PrintCoinMoney(*pm2);

	auto pm3 = AddCoinMoney(pm1, pm2);
	PrintCoinMoney(*pm3);

	// pm1, pm2, pm3 모두 고유한 메모리 영역에 할당된 객체를 참조하고 있음

	delete pm1;
	delete pm2;
	delete pm3;
}


/********************************************************
* smart_pointer
********************************************************/
shared_ptr<CoinMoney> AddCoinMoney_Smart(const shared_ptr<CoinMoney> cm1, const shared_ptr<CoinMoney> cm2) {
	shared_ptr<CoinMoney> psum(new CoinMoney());
	psum->c50 = cm1->c50 + cm2->c50;
	psum->c100 = cm1->c100 + cm2->c100;
	psum->c500 = cm1->c500 + cm2->c500;

	return psum;
}

void Practice_SmartPointer() {
	shared_ptr<CoinMoney> pm1(new CoinMoney());
	shared_ptr<CoinMoney> pm2(new CoinMoney());
	pm1->c50 = 1;
	pm1->c100 = 2;
	pm1->c500 = 3;
	PrintCoinMoney(*pm1);

	*pm2 = *pm1;
	PrintCoinMoney(*pm2);

	auto pm3 = AddCoinMoney_Smart(pm1, pm2);
	PrintCoinMoney(*pm3);

	// pm1, pm2, pm3 모두 고유한 메모리 영역에 할당된 객체를 참조하고 있음

	//delete pm1;
	//delete pm2;
	//delete pm3;
	// -> 불필요
}