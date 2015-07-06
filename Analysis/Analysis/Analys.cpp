// Analys.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	char filename [128];
	data arr[2048];
	data res[1024];
	double a, b, time, amplitude;
	int k(0),c(0),t(0);
    cout << "ENTER INPUT FILENAME" << endl;
	cin >> filename;
	fstream file (filename);
	if (!file)
	{
		cout << "INVALID FILENAME. PLEASE RESTART." << endl;
		system("PAUSE");
		return 0;
	}
	while (!file.eof()) //цикл, вытягивающий данные из файла в массив структур типа data под названием arr.
	{                   //в каждом элементе массива хранится время измерения и значение амлитуды, соответствующее времени
		if (file.get() == ':')
		{
			file.get();
			char sign = file.get();
			if (sign != '-')
			{
				file.seekg(int(file.tellg()) - 1);
			}
			file >> a;
			file.seekg(int(file.tellg()) + 1);
			file >> b;
			if (k++ % 2 == 0)
			{
				time = a + b / 1000;
				arr[t].time = time;
			}
			else
			{
				if (sign != '-')
				{
					amplitude = a + b / 10;
				}
				else
				{
					amplitude = -a - b / 10;
				}
				arr[t++].amp = amplitude;
			}
		}
	}
	for (int i = 0; i < t-2;i++) //цикл, вытягивающий точки максимума из массива значений в массив res
	{
		if (arr[i].amp < arr[i+2].amp && arr[i+1].amp <= arr[i+2].amp //условие экстремума (проверяем окрестность в два измерения)
			&&arr[i+3].amp <= arr[i+2].amp && arr[i+4].amp < arr[i+2].amp)
		{
			res[c++] = arr[i+2];
			if (arr[i + 3].amp == arr[i + 2].amp)
			{
				i += 2; //перекидываем индекс вперед на два значения, в случае, если экстремум дублируется в соседней от него точке
			}
		}
	}
	file.close();

	cout << "DATA ACQUIRED" << endl;
	cout << "ENTER OUTPUT FILENAME" << endl;
	cin >> filename;
	ofstream out(filename);
	if (!out)
	{
		cout << "INVALID FILENAME. PLEASE RESTART." << endl;
		system("PAUSE");
		return 0;
	}

	for (int i = 0; i < c; i++) //выводим данные в файл и на экран 
	{
		cout << res[i].time << " " << res[i].amp<<endl;
		out << res[i].time << " " << res[i].amp << endl;
	}

	//критерий апериодичности (почти на глаз, проверкой превышения тангенса угла наклона некой контрольной величины
	//(угла наклона прямой между 1 и 2 точками))
	double decRaw = log(res[0].amp / res[1].amp);
	double endPoint;
	for (int i = 0; i < c - 4; i++)
	{
		if (abs(decRaw / (res[1].time - res[0].time) - log(res[i].amp / res[i + 4].amp) / (res[i + 4].time - res[i].time))>0.1)
		{
			endPoint = i;
		}
	}

	///Продолжаем вывод
	cout << "DEADPOINT NUMBER (WARNING, FLUCTUATION MAY OCCUR) :" << endPoint << endl; //òî÷êà, â êîòîðîé íà÷èíàåòñÿ àïåðèîäè÷íîñòü

	cout << "FOUND " << c << " MAXIMUMS" << endl;
	out << "FOUND " << c << " MAXIMUMS" << endl;

	cout << "LOGARYTHMIC DECREMENT CALCULATED WITH FIRST TWO AMPLITUDES: " << decRaw << endl;
	out << "LOGARYTHMIC DECREMENT CALCULATED WITH FIRST TWO AMPLITUDES: " << decRaw << endl;

	cout << "NON-LOGARYTHMIC DECREMENT CALCULATED WITH FIRST TWO AMPLITUDES: " << -decRaw / (res[1].time - res[0].time) << endl;
	out << "NON-LOGARYTHMIC DECREMENT CALCULATED WITH FIRST TWO AMPLITUDES: " << -decRaw / (res[1].time - res[0].time) << endl;
	out.close();
	system("PAUSE");
	return 0;
}

