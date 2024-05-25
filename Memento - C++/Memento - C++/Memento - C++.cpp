#include <iostream>
#include <string>
#include <stack>
using namespace std;

class IMemento {
public:
	virtual int GetDollars() = 0;
	virtual int GetEuro() = 0;
	virtual ~IMemento() {}
};

class ExchangeMemento : public IMemento {
private:
	int dollars;
	int euro;
public:
	ExchangeMemento(int d, int e) : dollars(d), euro(e){}
	int GetDollars() override {
		return dollars;
	}
	int GetEuro() override {
		return euro;
	}
};

class Exchange {
private:
	int dollars;
	int euro;
public:
	Exchange(int d, int e) : dollars(d), euro(e){}
	void GetDollars() {
		cout << "Dollars: " << dollars << "\n";
	}
	void GetEuro() {
		cout << "Euro: " << euro << "\n";
	}
	void Sell() {
		dollars ? --dollars : 0;
	}
	void Buy() {
		euro++;
	}
	ExchangeMemento* Save() {
		return new ExchangeMemento(dollars, euro);
	}
	void Restore(IMemento* ex) {
		dollars = ex->GetDollars();
		euro = ex->GetEuro();
		delete ex;
	}
};

class Memory {
private:
	stack<IMemento*> history;
	Exchange* exchange;
public:
	Memory(Exchange* ex) : exchange(ex) {}
	void BackUp() {
		history.push(exchange->Save());
	}
	void Undo() {
		if (history.empty()) return;

		exchange->Restore(history.top());
		history.pop();
	}

};

int main() {
	Exchange* exchange = new Exchange(10, 10);
	Memory* memory = new Memory(exchange);
	exchange->GetDollars();
	exchange->GetEuro();
	cout << "---- Dollar sale euro purchase ----\n";
	exchange->Sell();
	exchange->Buy();
	exchange->GetDollars();
	exchange->GetEuro();
	cout << "---- State preservation -----\n";
	memory->BackUp();
	cout << "\n---- Dollar sale euro purchase ----\n";
	exchange->Sell();
	exchange->Buy();
	exchange->GetDollars();
	exchange->GetEuro();
	cout << "---- State recovery ----\n";
	memory->Undo();
	exchange->GetDollars();
	exchange->GetEuro();
}