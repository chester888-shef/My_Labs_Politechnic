#include<iostream>
#include<string>
#include <clocale>
#include<algorithm>

using namespace std;

class deposit {
protected: 
	string name;
	double sum;
public: 
	deposit(int s , string n): sum(s) , name(n) {
	}
	virtual ~deposit () {}
};

class rahunok : public deposit {
private:
	int time;
	int prc;
public:
	rahunok(int s, string n, int t, int p) : deposit(s, n), time(t), prc(p) {}

	double get_profit() {
		return (sum * prc * time) / (100.0 * 12.0);
	}

	int get_time() {
		return time; 
	}
	string get_name (){
		return name;
	}
		
};
void input(rahunok** m, int count) {
	for (int i = 0; i < count; i++) {
		string n_name;
		int s_sum, p_prc, t_time;
		cout << "\n Account " << i + 1 << endl;

		cout << "Enter depositor name: ";
		getline(cin >> ws ,  n_name);

		cout << "Enter deposit sum: ";
		cin >> s_sum;

		cout << "Enter term (months): ";
		cin >> t_time;

		cout << "Enter annual rate (%): ";
		cin >> p_prc;

		m[i] = new rahunok(s_sum, n_name, t_time, p_prc);
	}
}
void sort(rahunok** m, int count) {
	for (int i = 0; i < count - 1; i++) {
		for (int j = 0; j < count - 1 - i; j++) {
			if (m[j]->get_profit() > m[j + 1]->get_profit()) {
				rahunok* temp = m[j];
				m[j] = m[j + 1];
				m[j + 1] = temp;
			}
		}
	}
}
int main() {
	int a = 0; 
	cout << "Input how many account you want : " << endl;
	cin >> a; 
	rahunok** mass = new rahunok* [a];

	input(mass, a);
	sort(mass , a);
	
	cout << "Sorted list :" << endl;
	for (int i = 0; i < a; i++) {
		cout << i + 1 << ". Name " << mass[i]->get_name()
		<< " | Profit : " << mass[i]->get_profit() << endl;
	}

	cout << "\nTotal Profit by Terms: " << endl;
	for (int i = 0; i < a - 1; i++) {
		for (int j = 0; j < a - 1 - i; j++) {
			if (mass[j]->get_time() > mass[j + 1]->get_time()) {
				rahunok* temp = mass[j];
				mass[j] = mass[j + 1];
				mass[j + 1] = temp;
			}
		}
	}
	for (int i = 0; i < a; i++) {
		double current_sum = mass[i]->get_profit();
		int current_term = mass[i]->get_time();
		while (i + 1 < a && mass[i + 1]->get_time() == current_term) {
			i++;
			current_sum += mass[i]->get_profit();
		}

		cout << "Term " << current_term << " months: Total Profit = " << current_sum << endl;
	}

	for (int i = 0; i < a; i++) {
		delete mass[i];
	}
	delete[] mass;
	return 0;
}