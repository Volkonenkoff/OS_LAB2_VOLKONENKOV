#include <iostream>
#include <limits>
#include <Windows.h>
#include <conio.h>
#include <tchar.h>
#define MAX_BUF 128

using namespace std;
TCHAR mname[] = TEXT("Local\\MyFileMapObj");
HANDLE CF()
{
	
	HANDLE NEW = INVALID_HANDLE_VALUE, hMAP=NULL;
	string b;
	
	TCHAR fname[MAX_PATH + 1] = {};
	cout << "������� ��� �����: ";
	cin >> b;

	copy(b.begin(), b.end(), fname);
	NEW = CreateFile(fname, GENERIC_READ | GENERIC_WRITE, NULL,
		NULL, CREATE_ALWAYS, NULL,NULL);
	
	if (NEW != INVALID_HANDLE_VALUE)
	{
		hMAP = CreateFileMapping(NEW, NULL, PAGE_READWRITE, 0, MAX_BUF, mname);
		if (hMAP != NULL && GetLastError() == ERROR_ALREADY_EXISTS)
		{
			CloseHandle(hMAP);
			hMAP = NULL;
		}
	}
	
	return hMAP;
}


int _tmain()
{
	HANDLE FILE=NULL;
	LPVOID ADR = NULL;
	
	system("chcp 1251");
	short k;
	do
	{
		cout << "1. ������� ������������ ����" << endl;
		cout << "2. ������������� ��������� ����� � ������" << endl;
		cout << "3. ���� ������ � ���������� � �� ������ � ������������� ����" << endl;
		cout << "4. �����" << endl;
		cout << "����>> ";
		cin >> k;
		switch (k)
		{
		case 1:
			system("cls");
			FILE=CF();
			if (FILE == NULL)
				cout << "�� ������� ������� ����: " <<GetLastError() <<endl;
			else cout << "���� ������� ������" << endl;
			break;
		case 2:
			system("cls");
			if (FILE == NULL)
				cout << "������� �������� ����" << endl;
			else
			{
				ADR =MapViewOfFile(FILE, FILE_MAP_ALL_ACCESS, 0, 0, MAX_BUF);
				if (ADR != NULL) cout << "���� ������� ������������" << endl;
				else cout << "������: " << GetLastError();
			}
			break;
		case 3:
			system("cls");
			if (ADR == NULL && FILE!=NULL)
			{
				cout << "�� ������� ������������� �������� ����� � ������: " << GetLastError() << endl;
				CloseHandle(FILE);
			}
			else if (ADR!=NULL && FILE!=NULL)
			{
				cout << "������� ������ :" << endl;
				string tmp="";
				cin >> tmp;

				
				CopyMemory((LPVOID)ADR, (CHAR*)tmp.c_str(), tmp.length()*sizeof(char));
				cout << "������ �����������, �������� ���������-�����" << endl;
				cout << "��������� � ��� ��������� �����, ��������� ������ �� ������ � ������� ����� �������" << endl;
				system("pause");
				cout << "��������� 5 ������";
				Sleep(5000);
				if (ADR != NULL && FILE != NULL)
				{
					UnmapViewOfFile(ADR);
					CloseHandle(FILE);
				}
				
				system("pause");
				
				cout << "������ ��������" << endl;
			}
			break;
		case 4:
			system("cls");
			
			
			cout << "�������.." << endl;
			break;
		default :
			system("cls");
			cout << " ������ ������ ���" << endl;
			break;
		}
	} while (k!=4);
	
	
	return 0;
}