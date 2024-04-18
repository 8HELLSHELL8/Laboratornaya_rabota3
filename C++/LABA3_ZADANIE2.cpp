#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;


void resheto() {
	int n;
	cout << "Input amount of prime number ";
	cin >> n;
	vector<int> prostchisla;
	for (int i = 0; i < n + 1; i++)
		prostchisla.push_back(i);
	for (int p = 2; p < n + 1; p++)
	{
		if (prostchisla[p] != 0)
		{
			for (int j = p * p; j < n + 1; j += p)
				prostchisla[j] = 0;
		}
	}
	int linecount = 0;
	for (int al : prostchisla) {
		if (al != 0) {
			if (linecount == 10) {
				cout << "\n";
				linecount = 0;
			}
			cout << al << " ";
			linecount += 1;
		}
	}
}

unsigned long long mod(unsigned long long number, unsigned long long power, unsigned long long n) {
	unsigned long long res = 1;
	while (power) {
		if (power % 2) res = (res * number) % n;
		number = (number * number) % n;
		power /= 2;
	}
	return res;
}

void tableprost(vector<int>& pch) {//Функция заполнения вектора простыми числами из файла (Используем готовую таблицу)
	ifstream file("chisla.txt");
	if (file.is_open()) {
		while (true) {
			string stroka;
			getline(file, stroka, ' ');
			if (stroka == "@") break;
			pch.push_back(stoi(stroka));
		}
	}
}

bool TestMillerasver(int t, int N, set<int> q, int& K) {//Тест Миллера на простоту
	int countT = 0;
	int countF = 0;
	for (int j = 0; j < 50; j++) {

		vector<int> aj;//Создание случайных чисел
		for (int i = 0; i < t; i++) {
			int rand1 = rand() % N;
			if (rand1 == 0) {
				rand1 = 2 + 1;
			}
			aj.push_back(rand1);
		}

		int iscomposite = 0;

		for (int aj1 : aj) {
			if (mod(aj1, N - 1, N) != 1) {
				iscomposite = 1;
				break;
			}
		}

		if (iscomposite == 1) {
			countF = countF + 1;
			continue;
		}

		for (int aj1 : aj) {
			for (int qi : q) {
				if (mod(aj1, (N - 1) / qi, N) != 1) {
					iscomposite = 1;
					continue;
				}
			}
		}

		if (iscomposite == 0) {
			countT = countT + 1;
			continue;
		}
		countT = countT + 1;
	}
	if (countT > countF) return true;
	else {
		K += 1;
		return false;
	}
}

bool TestPoklingtona(int t, int N, set<int> q, int& K, vector<int> prostch) {//Проверка чисел на простоту. Тест Поклингтона
	int countT = 0;
	int countF = 0;
	for (int j = 0; j < 100; j++) {

		vector<int> aj;//Создание случайных чисел
		for (int i = 0; i < t; i++) {
			int rand1 = rand() % N;
			if (rand1 == 0) {
				continue;
			}
			aj.push_back(rand1);
		}

		int iscomposite = 0;

		for (int aj1 : aj) {
			if (mod(aj1, N - 1, N) != 1) {
				iscomposite = 1;
				break;
			}
		}

		if (iscomposite == 1) {
			countF += 1;
			continue;
		}

		for (int aj1 : aj) {
			for (int qj : q) {
				if (mod(aj1, (N - 1) / qj, N) == 1) {
					iscomposite = 1;
					break;
				}
			}
			if (iscomposite == 1) break;
		}

		if (iscomposite == 1) {
			countF += 1;
			continue;
		}

		if (iscomposite == 0) {
			countT += 1;
		}
	}
	if (countT > countF) {
		return true;
	}
	K += 1;
	return false;
}

void GenMillera(int size, vector<int> pch, vector<int>& pchM, vector<int>& KM) {//Процедура получения простых чисел на основе теста Миллера
	set<int> similar;
	int K = 0;
	for (int countcikl = 0; countcikl != 10;) {
		set<int> q;
		for (int i = 0; i < 2; i++) {
			q.insert(pch[rand() % 93]);
		}
		int m = 1;
		for (int chislo : q) {
			m = m * chislo;
		}
		int n = 2 * m + 1;
		int n1 = n;
		int countn1 = 0;
		while (n1 > 0) {
			countn1 += 1;
			n1 = n1 / 10;
		}
		for (int sim : similar) {
			if (n == sim) countn1 = -1;
		}
		if (countn1 != size) continue;

		if (TestMillerasver(1, n, q, K)) {
			pchM.push_back(n);
			similar.insert(n);
			countcikl += 1;
			KM.push_back(K);
			K = 0;
		}
	}
}

void GenPoklingtona(int size, vector<int> pch, vector<int>& pchP, vector<int>& KP) {//Процедура получения простых чисел на основе теста Поклингтона
	set<int> similar;
	int K = 0;
	for (int countcikl = 0; countcikl != 10;) {
		set<int> q;
		for (int i = 0; i < 2; i++) {
			q.insert(pch[rand() % 93]);
		}
		int f = 1;
		for (int chislo : q) {
			f = f * chislo;
		}
		int r = rand() % ((3 * f) / 4);
		if (r % 2 != 0) r = r + 1;
		int n = r * f + 1;
		int n1 = n;
		int countn1 = 0;
		while (n1 > 0) {
			countn1 += 1;
			n1 = n1 / 10;
		}
		for (int sim : similar) {
			if (n == sim) countn1 = -1;
		}
		if (countn1 != size) continue;
		bool a = TestPoklingtona(1, n, q, K, pch);
		if (TestPoklingtona(1, n, q, K, pch) == true) {
			KP.push_back(K);
			pchP.push_back(n);
			similar.insert(n);
			countcikl += 1;
			K = 0;
		}
	}
}

void GenGOST(int size, vector<int> pch, vector<int>& pchG, vector<int>& KG) {//Процедура получения простых чисел
	set<int> similar;
	int K = 0;
	for (int countcikl = 0; countcikl != 10;) {
		int q = pch[rand() % 93];
		K = 0;
		for (int u = 0; true; u = u + 2) {
			int N = ceil(pow(2, size - 1) / q);
			if (N % 2 != 0) N = N + 1;
			int p = (N + u) * q + 1;
			if (mod(2, p - 1, p) == 1 and mod(2, N + u, p) != 1) {
				int n1 = p;
				int countn1 = 0;
				while (n1 > 0) {
					countn1 += 1;
					n1 = n1 / 10;
				}
				for (int sim : similar) {
					if (p == sim) countn1 = -1;
				}
				if (countn1 == size) {
					KG.push_back(K);
					pchG.push_back(p);
					countcikl += 1;
					similar.insert(p);
				}
				break;
			}
			K += 1;
		}
	}
}

int main() {
	int size = 3;//Размер простых чисел
	vector<int> prostch;//Вектор простых чисел до 500
	vector<int> pchM;
	vector<int> pchP;
	vector<int> pchG;
	vector<int> KM;
	vector<int> KP;
	vector<int> KG;
	tableprost(prostch);//Заполняем вектор простых чисел

	cout << "Test Milera" << endl;
	GenMillera(size, prostch, pchM, KM);
	cout << "Num ";
	for (int i = 1; i <= 10; i++) cout << i << "   ";
	cout << "\n";
	cout << " p  ";
	for (int prch : pchM) {
		cout << prch << " ";
	}
	cout << "\n";
	for (int i = 0; i < 10; i++) {
		if (i == 0) cout << "    +";
		else cout << "   +";
	}
	cout << "\n";
	cout << " K  ";
	for (int K : KM) {
		cout << K << "   ";
	}

	cout << "\n" << "Test Poklingtona" << endl;
	GenPoklingtona(size, prostch, pchP, KP);
	cout << "Num ";
	for (int i = 1; i <= 10; i++) cout << i << "   ";
	cout << "\n";
	cout << " p  ";
	for (int prch : pchP) {
		cout << prch << " ";
	}
	cout << "\n";
	for (int i = 0; i < 10; i++) {
		if (i == 0) cout << "    +";
		else cout << "   +";
	}
	cout << "\n";
	cout << " K  ";
	for (int K : KP) {
		cout << K << "   ";
	}

	cout << "\n" << "GOST" << endl;
	GenGOST(size, prostch, pchG, KG);
	cout << "Num ";
	for (int i = 1; i <= 10; i++) cout << i << "   ";
	cout << "\n";
	cout << " p  ";
	for (int prch : pchG) {
		cout << prch << " ";
	}
	cout << "\n";
	for (int i = 0; i < 10; i++) {
		if (i == 0) cout << "    +";
		else cout << "   +";
	}
	cout << "\n";
	cout << " K  ";
	for (int K : KG) {
		cout << K << "   ";
	}
	cout << "\n";
	resheto();
}