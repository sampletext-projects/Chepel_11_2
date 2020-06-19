#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

int** frequencies(string& line, int& unique_size)
{
	// массив частот символов, разных символов не может быть больше чем длина строки, инициализируем в 0
	// первая строка - символы, вторая строка - количество вхождений
	int** freqs = new int*[2]{new int[line.length()]{0}, new int[line.length()]{0}};

	unique_size = 0;

	//анализируем каждый символ
	for (int i = 0; i < line.length(); i++)
	{
		char cc = line[i];
		if (ispunct(cc) || isspace(cc))
		{
			//если знак - игнорируем
			// !"#$%&'()*+,-./:;<=>?@[\]^_`{|}~
			continue;
		}
		//ищем символ в уже найденных
		int index = -1;
		for (int j = 0; j < unique_size; j++)
		{
			if (freqs[0][j] == cc)
			{
				index = j;
				break;
			}
		}
		//если нашли
		if (index != -1)
		{
			freqs[1][index]++;
		}
		else // если не нашли
		{
			freqs[0][unique_size] = cc;
			freqs[1][unique_size] = 1;
			unique_size++;
		}
	}
	return freqs;
}

//сортировка частот символов
void sort(int** frequencies, int size)
{
	bool sorted;
	do
	{
		sorted = true;
		for (int i = 1; i < size; ++i)
		{
			if (frequencies[1][i] > frequencies[1][i - 1])
			{
				// меняем пару местами
				char t_c = frequencies[0][i];
				int f_c = frequencies[1][i];

				frequencies[0][i] = frequencies[0][i - 1];
				frequencies[1][i] = frequencies[1][i - 1];

				frequencies[0][i - 1] = t_c;
				frequencies[1][i - 1] = f_c;
				sorted = false;
			}
		}
	}
	while (!sorted);
}

int main()
{
	setlocale(LC_ALL, "russian");

	cout << "Автор: Чепель Егор Максимович" << endl;
	cout << "Программа для построения частотного алфавита строки" << endl;

	string file = "f.txt"; //файл текущих соревнований

	ifstream f(file);
	f.peek();
	if (!f.good())
	{
		cout << "Ошибка при открытии файла.\nПроверьте наличие и заполненность файла f.txt\n";
	}
	else
	{
		while (!f.eof()) //открываем файл
		{
			string v;
			getline(f, v); //считываем строку
			int size;
			int** freqs = frequencies(v, size);
			sort(freqs, size);
			for (int i = 0; i < size; i++)
			{
				char c = (char)freqs[0][i];
				cout << c << ": " << freqs[1][i] << "\n";
			}
		}
	}
	f.close();

	system("pause");

	return 0;
}
