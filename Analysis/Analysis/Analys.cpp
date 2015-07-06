// Analys.cpp: ���������� ����� ����� ��� ����������� ����������.
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
	while (!file.eof()) //����, ������������ ������ �� ����� � ������ �������� ���� data ��� ��������� arr.
	{                   //� ������ �������� ������� �������� ����� ��������� � �������� ��������, ��������������� �������
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
	for (int i = 0; i < t-2;i++) //����, ������������ ����� ��������� �� ������� �������� � ������ res
	{
		if (arr[i].amp < arr[i+2].amp && arr[i+1].amp <= arr[i+2].amp //������� ���������� (��������� ����������� � ��� ���������)
			&&arr[i+3].amp <= arr[i+2].amp && arr[i+4].amp < arr[i+2].amp)
		{
			res[c++] = arr[i+2];
			if (arr[i + 3].amp == arr[i + 2].amp)
			{
				i += 2; //������������ ������ ������ �� ��� ��������, � ������, ���� ��������� ����������� � �������� �� ���� �����
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

	for (int i = 0; i < c; i++) //������� ������ � ���� � �� ����� 
	{
		cout << res[i].time << " " << res[i].amp<<endl;
		out << res[i].time << " " << res[i].amp << endl;
	}

	//�������� �������������� (����� �� ����, ��������� ���������� �������� ���� ������� ����� ����������� ��������
	//(���� ������� ������ ����� 1 � 2 �������))
	double decRaw = log(res[0].amp / res[1].amp);
	double endPoint;
	for (int i = 0; i < c - 4; i++)
	{
		if (abs(decRaw / (res[1].time - res[0].time) - log(res[i].amp / res[i + 4].amp) / (res[i + 4].time - res[i].time))>0.1)
		{
			endPoint = i;
		}
	}
	//������������ �������� � ���������� ������ ��������� ��� ���
	double shiftTime = res[0].time;
	double shiftAmp = log(res[0].amp);
	for (int i = 0; i < endPoint; i++)
	{
		res[i].time -= shiftTime;
		res[i].amp = log(res[i].amp)-shiftAmp;
	}
	//����������, ���
	double MHKresult;
	double tempChisl(0);
	double tempZnam(0);
	for (int i = 0; i < endPoint; i++)
	{
		tempChisl += res[i].amp*res[i].time;
		tempZnam += res[i].time*res[i].time;
	}
	MHKresult = tempChisl / tempZnam;

	//���������� �����
	cout << "DEADPOINT NUMBER (WARNING, FLUCTUATION MAY OCCUR) :" << endPoint << endl; //�����, � ������� ���������� ��������������

	cout << "FOUND " << c << " MAXIMUMS" << endl;
	out << "FOUND " << c << " MAXIMUMS" << endl;

	cout << "LOGARYTHMIC DECREMENT CALCULATED WITH FIRST TWO AMPLITUDES: " << decRaw << endl;
	out << "LOGARYTHMIC DECREMENT CALCULATED WITH FIRST TWO AMPLITUDES: " << decRaw << endl;

	cout << "NON-LOGARYTHMIC DECREMENT CALCULATED WITH MHK " << MHKresult << endl;
	out << "NON-LOGARYTHMIC DECREMENT CALCULATED WITH MHK " << MHKresult << endl;

	cout << "NON-LOGARYTHMIC DECREMENT CALCULATED WITH FIRST TWO AMPLITUDES: " << -decRaw / (res[1].time - res[0].time) << endl;
	out << "NON-LOGARYTHMIC DECREMENT CALCULATED WITH FIRST TWO AMPLITUDES: " << -decRaw / (res[1].time - res[0].time) << endl;
	out.close();
	system("PAUSE");
	return 0;
}

