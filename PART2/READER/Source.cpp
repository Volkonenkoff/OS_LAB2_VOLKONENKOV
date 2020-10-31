#include <iostream>
#include <Windows.h>
#define MAX_BUF 128
using namespace std;
TCHAR mname[] = TEXT("Local\\MyFileMapObj");
HANDLE OF()
{
	HANDLE OLD_MAP = NULL;
	
	OLD_MAP = OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE, mname);
	return OLD_MAP;
}
int main()
{
	HANDLE HMAP = NULL;
	LPVOID ADR = NULL;
	TCHAR MSG[MAX_BUF + 1] = {};
	system("chcp 1251");
	char k;
	do
	{
		cout << "1. �������� ���������������� �����" << endl;
		cout << "2. ����� ������, ������� � ����������" << endl;
		cout << "3. �����" << endl;
		cout << "����>> ";
		cin >> k;
		switch (k)
		{
		case '1':
			system("cls");
			HMAP = OF();
			if (HMAP == NULL)
			{
				cout << "�� ������� ������� ��������������� ����: " << GetLastError()<< endl;
			}
			else
			{
				ADR = MapViewOfFile(HMAP, FILE_MAP_ALL_ACCESS, 0, 0, MAX_BUF);
				if (ADR == NULL) cout << "�� ������� ������� ����, ���������� �����: "<< GetLastError()<< endl;
				else cout << "������ �� ���������������� ����� �������� �������" << endl;
				
			}
			break;
		case '2':
			system("cls");
			if (ADR != NULL)
			{
				cout << "��������� ������:" << endl;
				CHAR* c_tmp = (CHAR*)ADR;
				for (size_t i = 0; i < strlen(c_tmp); i++)
					cout << c_tmp[i];
				cout << endl;
				UnmapViewOfFile(ADR);
				cout << "������ ���������, �� ������ ����� �� ���� ��������� � ��������� � ����������" << endl;
			
			}
			else cout << "�� ������� ������� ������, ���������� ����� ������� ����" << endl;
			break;
		case '3':
			system("cls");
			cout << "�������.." << endl;
			break;
		default:
			system("cls");
			cout << " ������ ������ ���" << endl;
			break;
		}
	} while (k != '3');


	return 0;
}