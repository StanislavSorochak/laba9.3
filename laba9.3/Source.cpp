#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

enum measurement { ��, �, ��, ��, �� };

string t_measurement[] = { "�� ",
						   "��",
						   "��",
						   "��",
						   "��" };

struct towar
{
	string n_towar;
	int vart�st;
	int kilkist;
	measurement units;
	int masa;
};

void Create_towar(towar* s, const int kil_towar, int i);
void Print_towar(towar* s, const int kil_towar, int i);
towar* vulychenya(towar* s, int& kil_towar, int pozution);
void Sort(towar* s, const int kil_towar, const int zmina);
int BinSearch_towar(towar* s, const int kil_towar, const string nazwa_towar);
void BinSearch_vartist(towar* s, const int kil_towar, const int vartisr1, const int vartisr2, int& l1, int& l2);
void SaveToFile(towar* s, const int kil_towar, const char* filename);
void LoadFromFile(towar*& s, int& kil_towar, const char* filename);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int kil_towar;
	cout << "������ ��������� ������� ������: "; cin >> kil_towar;
	cout << endl;
	int soxr_towar = kil_towar;
	towar* s = new towar[kil_towar + 1000];

	int i, g, pos, zmina, found, index;
	int l1 = 0, l2 = 0;
	int vartisr1, vartisr2;
	string nazwa_towar;
	char filename[100];

	int menutowar;
	do {
		cout << "������� ��:" << endl << endl;

		cout << " [1] - ��������� ������ ������" << endl;
		cout << " [2] - ���� ���������� ��� �����" << endl;
		cout << " [3] - ���������� ������" << endl;
		cout << " [4] - ��������� ������" << endl;
		cout << " [5] - ����������� ���������� ��� �����" << endl;
		cout << " [6] - ���������� ������" << endl;
		cout << " [7] - ����� ������ �� ������ � ���� ���������� ��� �����" << endl;
		cout << " [8] - ���� ���������� ��� ������ �� �������� �������� �������" << endl;
		cout << " [9] - ����� ����� � ����" << endl;
		cout << " [10] - ���������� ����� �� �����" << endl << endl;

		cout << " [0] - ����� �� ���������� ������ ��������" << endl << endl;

		cout << "������ ����� ����: "; cin >> menutowar;
		switch (menutowar)
		{
		case 1:
			kil_towar = soxr_towar;
			Create_towar(s, kil_towar, 0);
			break;
		case 2:
			cout << endl;
			Print_towar(s, kil_towar, 0);
			break;
		case 3:
			cout << endl;
			cout << "������ ����� ������� ������ �� �� ������ �������� �� ������: "; cin >> g;
			cout << endl;
			kil_towar += g;
			i = kil_towar - g;
			Create_towar(s, kil_towar, i);
			break;
		case 4:
			cout << endl;
			cout << "������ ����� ������� ������ ��� ��������� ���� � ������: "; cin >> pos;
			cout << endl;
			s = vulychenya(s, kil_towar, pos);
			break;
		case 5:
			cout << endl;
			cout << "������ ����� ������� ������ ��� ����������� ���� ���������� � ������: "; cin >> pos;
			cout << endl;
			i = pos;
			Create_towar(s, i, i - 1);
			break;
		case 6:
			cout << endl;
			cout << "���������� �� ���� ������(����� 1) ��� �� ��������� �������(����� 0): " << endl;
			cout << "������� ������ �����(1 ��� 0): "; cin >> zmina;
			cout << endl;
			Sort(s, kil_towar, zmina);
			break;
		case 7:
			cout << endl;
			cin.get();
			cin.sync();
			cout << "������ ����� ������: "; getline(cin, nazwa_towar);
			cout << endl;
			found = BinSearch_towar(s, kil_towar, nazwa_towar);
			if (found != -1)
			{
				cout << "���������� ��� �����: " << endl << endl;
				Print_towar(s, found + 1, found);
			}
			else
				cout << "��������� ���� ������ � ������ �� ���������: " << endl << endl;
			break;
		case 8:
			cout << "ĳ������ �������: " << endl << endl;
			cout << "������ �������� �������: ";
			cin >> vartisr1;
			cout << "������ ����������� �������: ";
			cin >> vartisr2;
			l1 = -1;
			l2 = -2;
			BinSearch_vartist(s, kil_towar, vartisr1, vartisr2, l1, l2);
			Print_towar(s, l2 + 1, l1);
			break;
		case 9:
			cin.get();
			cin.sync();
			cout << "������ ��'� �����: "; cin.getline(filename, 99);
			SaveToFile(s, kil_towar, filename);
			break;
		case 10:
			cin.get();
			cin.sync();
			cout << "������ ��'� �����: "; cin.getline(filename, 99);
			LoadFromFile(s, kil_towar, filename);
			break;
		case 0:
			cout << "���������� ������ ��������" << endl << endl;
			break;
		default:
			cout << "�� ����� ��������� ��������! "
				"��� ������ ����� - ����� ��������� ������ ����" << endl;
		}
		cout << endl;
	} while (menutowar != 0);
	delete[] s;
}

void Create_towar(towar* s, const int kil_towar, int i)
{
	int towar;
	for (; i < kil_towar; i++)
	{
		cout << endl;
		cout << "����� � " << i + 1 << endl;

		cin.get();
		cin.sync();

		cout << "  �����: "; getline(cin, s[i].n_towar);
		cout << "  �������(� ���.): "; cin >> s[i].vart�st;
		cout << "  �������: "; cin >> s[i].kilkist;
		cout << "  ������� ����������(0 - ̳�����, 1 - ����, 2 - �������, 3 - ʳ������, 4 - �����): "; cin >> towar;
		s[i].units = (measurement)towar;
		cout << "  �������� ��: "; cin >> s[i].masa; cout << "  " << t_measurement[towar] << endl;
	}
}

void Print_towar(towar* s, const int kil_towar, int i)
{
	cout << "====================================================================="
		<< endl;
	cout << "| �  | �����        | �������(� ���.) | ʳ������ | �������� ��    |"
		<< endl;
	cout << "---------------------------------------------------------------------" << endl;

	for (; i < kil_towar; i++)
	{
		cout << "| " << setw(2) << right << i + 1 << " "
			<< "| " << setw(13) << left << s[i].n_towar
			<< "| " << setw(16) << left << s[i].vart�st << " "
			<< "| " << setw(5) << left << s[i].kilkist << "     "
			<< "| " << setw(2) << left << s[i].masa << setw(1) << left << " " << setw(11) << left << t_measurement[s[i].units] << " |" << endl;
	}
	cout << "=====================================================================" << endl;
}

towar* vulychenya(towar* s, int& kil_towar, int pozution)
{
	towar* l = new towar[kil_towar + 1000];
	int j = 0;

	for (int i = 0; i < kil_towar; i++)
	{
		if (i + 1 != pozution)
		{
			l[j++] = s[i];
		}
		else;
	}

	kil_towar = kil_towar - 1;
	return l;
}

void Sort(towar* s, const int kil_towar, const int zmina)
{
	towar tmp;
	for (int i0 = 0; i0 < kil_towar - 1; i0++)
		for (int i1 = 0; i1 < kil_towar - i0 - 1; i1++)
		{
			if (zmina)
				if (s[i1].n_towar > s[i1 + 1].n_towar)
				{
					tmp = s[i1];
					s[i1] = s[i1 + 1];
					s[i1 + 1] = tmp;
				}
				else;
			else
				if (s[i1].vart�st > s[i1 + 1].vart�st)
				{
					tmp = s[i1];
					s[i1] = s[i1 + 1];
					s[i1 + 1] = tmp;
				}
		}
}

int BinSearch_towar(towar* s, const int kil_towar, const string nazwa_towar)
{
	int L = 0, R = kil_towar - 1, m;
	do {
		m = (L + R) / 2;
		if (s[m].n_towar == nazwa_towar)
			return m;
		if (s[m].n_towar > nazwa_towar)
		{
			R = m - 1;
		}
		else
		{
			L = m + 1;
		}
	} while (L <= R);
	return -1;
}

void BinSearch_vartist(towar* s, const int kil_towar, const int vartisr1, const int vartisr2, int& l1, int& l2)
{
	int g = 0;
	for (int i = 0; i < kil_towar; i++)
	{
		if (s[i].vart�st >= vartisr1 && s[i].vart�st <= vartisr2)
		{
			l2 = i;
			g++;
		}
		if (g == 1)
			l1 = l2;
	}
}

void SaveToFile(towar* s, const int kil_towar, const char* filename)

{
	ofstream fout(filename, ios::binary);              // ������� ������� ���� ������
	fout.write((char*)&kil_towar, sizeof(kil_towar));                  // �������� ������� ��������
	for (int i = 0; i < kil_towar; i++)
		fout.write((char*)&s[i], sizeof(towar));       // �������� �������� ������
	fout.close();                                      // ������� ����
}
void LoadFromFile(towar*& s, int& kil_towar, const char* filename)
{
	delete[] s;                                         // ������� �������� ���
	ifstream fin(filename, ios::binary);                // ������� ������� ���� ����������
	fin.read((char*)&kil_towar, sizeof(kil_towar));                     // ��������� ������� ��������
	s = new towar[kil_towar];                                   // �������� ��������� �����
	for (int i = 0; i < kil_towar; i++)
		fin.read((char*)&s[i], sizeof(towar));          // ��������� �������� ������
	fin.close();                                        // ������� ����
}
