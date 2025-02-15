#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
#include <string>


std::vector<double> output_x(int n, std::vector<double>& s){
	double p_i = - s[2*n - 1] / s[n - 1];
	double q_i = s[3*n - 2] / s[n - 1];
	std::vector<double> p;
	std::vector<double> q;
	for(int i = 1; i < n-1; i++)
		{
			p.push_back(p_i);
			q.push_back(q_i);
			p_i = - s[2*n - 1 + i] / (s[i - 1] * p_i + s[n - 1 + i]);
			q_i = (s[3*n - 2 + i] - s[i - 1] * q_i) / (s[i - 1] * p_i + s[n - 1 + i]);
		}
	p.push_back(p_i);
	q.push_back(q_i);
 	std::vector<double> x;
	double x_i = (s[4*n - 3] - s[n-2] * q[n-2]) / (s[n - 2] * p_i + s[2 * n - 2]);
	for(int i = n - 2; i >= 0; i--)
		{
			x.insert(x.begin(), x_i);
			x_i = p[i] * x[0] + q[i];
		}
	x.insert(x.begin(), x_i);
	return x;

}


void print_x(std::vector<double>& x)
{
	std::cout << "Вектор x" << std::endl;
	for (int i = 0; i < x.size(); i++)
	{
		if (x[i] != x[i])
		{
			std::cout << "Решений нет" << std::endl;
			return;
		}
		std::cout << x[i] << " ";
	}
	std::cout << "" << std::endl;
}


int main(){
	std::vector<double> s_test1 = {0, 0, 1, 1, 1, 0, 0, 1, 1, 1};
	int n_test1 = 3;
	std::vector<double> x_test1 = {1, 1, 1};
	std::vector<double> out_x = output_x(n_test1, s_test1);
	if (out_x != x_test1)
	{
		print_x(out_x);
		std::cout << "Что-то пошло не так" << std::endl;
		return 1;
	}

	std::vector<double> s_test2 = {0, 1, 1, 0, 1, 1};
	int n_test2 = 2;
	std::vector<double> x_test2 = {1, 1};
	if (output_x(n_test2, s_test2) != x_test2)
	{
		std::cout << "Что-то пошло не так" << std::endl;
		return 1;
	}

	std::vector<double> s_test3 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 ,0, 1, 1, 1, 1, 1};
	int n_test3 = 5;
	std::vector<double> x_test3 = {1, 0, 1, 0, 1};
	if (output_x(n_test3, s_test3) != x_test3)
	{
		std::cout << "Что-то пошло не так" << std::endl;
		return 1;
	}






	std::cout << "Введите последовательно через пробел в четыре строки диагонали a, b, c и вектор d" << std::endl;
	std::vector<double> s;
	std::vector<int> len;
	for(int i = 0; i < 4; i++)
	{

		std::string input;
		std::vector<double> v;

		// Считываем всю строку ввода
		std::getline(std::cin, input);

		// Используем stringstream для разделения строки на числа
		std::stringstream ss(input);
		double number;

		// Читаем числа из строки и добавляем их в вектор
		while (ss >> number) {
		v.push_back(number);
	    }

	s.insert(s.end(), v.begin(), v.end());
	len.push_back(v.size());
	}
	int n = len[1];


	std::cout << "Запрос принят" << std::endl;



	if (len[0] != len[2] or len[1] != len[3] or len[0] == len[1] or len[2] == len[3])
	{
		std::cout << "Что-то пошло не так" << std::endl;
		return 1;
	}
	std::vector<double> v_all(s.size(), 0.0);
	std::vector<double> v_none(3*n-2, 0.0);
	if (s == v_all)
	{
		std::cout << "Любой вектор - решение" << std::endl;
		return 0;
	}
	std::vector<double> slice;
	for (int i = 0; i < 3*n-2; i++)
		slice.push_back(s[i]);
	if (slice == v_none)
	{
		std::cout << "Решений нет" << std::endl;
		return 0;
	}



	std::vector<double> x = output_x(n, s);
	print_x(x);


	return 0;
}





























