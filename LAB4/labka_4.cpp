#include <iostream>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;

class Deposit {
protected:
	string name;
	double sum;
public:
	Deposit(string n, double s) {
		name = n;
		sum = s;
	}
	virtual double getprofit() = 0; 
	virtual ~Deposit() {};
	string getname() { return name; }
};

class SimpleDeposit : public Deposit {
private :
	int month;
	double rate;
public :
	SimpleDeposit(string n, double s, int m, double r) : Deposit(n, s) {
		month = m;
		rate = r;
	}
	double getprofit () {
		if (month > 0 || rate > 0 || sum > 0) {
			return (month * rate * sum) / (1200.0);
		}
		else {
			cout << "data is nit valid ):" << endl;
			return 0.0;
		}
	}
};

class ProgressiveDeposit : public Deposit {
private:
	int month;
	vector<double> rate;
public:
	ProgressiveDeposit(int m, vector<double> r, double s , string n ) : Deposit(n, s) {
		month = m;
		rate = r;
	}
	double getprofit() {
		int allmonth = month;
		double total = 0;
		for (int i = 0; i < rate.size(); i++) {
			if (allmonth >= 3) {
				double currentsum = (sum * 3 * rate[i]) / (1200.0);
				allmonth -= 3;
				total += currentsum;
			}
			else {
				int currentmonth = allmonth;
				double cursum = (sum * currentmonth * rate[i]) / (1200.0);
				total += cursum;
				allmonth -= currentmonth;
			}
			if (allmonth <= 0) {
				break;
			}
		}
		return total;
	}
};
void SimpleDepf(vector<Deposit*>& acc) {
	double  s;
	string n;
	int m;
	double r;
	cout << "Enter your name: " << endl;
	cin >> n;
	cout << "Enter your deposit:" << endl;
	cin >> s;
	cout << "Enter your termin in month:" << endl;
	cin >> m;
	cout << "Enter your rate: " << endl;
	cin >> r;
	acc.push_back(new SimpleDeposit(n, s, m, r));
	cout << "Deposit created for " << n << " with sum " << fixed << setprecision(2) << s << endl;
}

void ProgDepf (vector<Deposit*>& acc) {
	double  s;
	string n;
	int m;
	vector <double> r;
	int q;
	double a;
	cout << "Enter your name: " << endl;
	cin >> n;
	cout << "Enter your deposit:" << endl;
	cin >> s;
	cout << "Enter your termin in month:" << endl;
	cin >> m;
	cout << "How many quarter: " << endl;
	cin >> q;
	for (int i = 0; i < q; i++) {
		cout << "Enter rate for quarter number " << i + 1 << " :" << endl;
		cin >> a;
		r.push_back(a);
	}
	acc.push_back(new ProgressiveDeposit(m, r, s, n));
	cout << "Deposit created for " << n << " with sum " << fixed << setprecision(2) << s << endl;
}
	void statistic(vector<Deposit*>& acc) {
		map<string, double > totalprofit;
		map<string, int > countdep;
		for (auto a : acc) {
			string name = a->getname();
			double profit = a->getprofit();

			totalprofit[name] += profit;
			countdep[name]++;
		}
			cout << "Statistic:" << endl;
			for (auto const& [ name, profit] : totalprofit) {
				double average = profit / countdep[name];
				cout << "Name of depositor: " << name
					<< "  Average profit: " << fixed << setprecision(2) << average << endl;
			}
		
	}
	int main() {
		vector<Deposit*> acc;
		int choice;
		while (true) {
			cout << "1-SimpleDeposit , 2-ProgerssiveDeposit, 3- Statistac, 0-Exit " << endl;
			cout << "Your choice:" << endl;
			cin >> choice;
			if (choice == 0) break;
			switch (choice) {
			case 1: SimpleDepf(acc); break;
			case 2: ProgDepf(acc); break;
			case 3: statistic(acc); break;
			default: cout << "Errorrrrrrrrrrrrrrrrrrrrrr ):"; break;
			}
		}
		for (auto a : acc) {
			delete a;
		}
		acc.clear();
	return 0;
}