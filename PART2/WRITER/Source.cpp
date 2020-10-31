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
	cout << "Введите имя файла: ";
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
		cout << "1. Создать проецируемый файл" << endl;
		cout << "2. Проецирование фрагмента файла в память" << endl;
		cout << "3. Ввод данных с клавиатуры и их запись в спроецриуемый файл" << endl;
		cout << "4. Выход" << endl;
		cout << "Ввод>> ";
		cin >> k;
		switch (k)
		{
		case 1:
			system("cls");
			FILE=CF();
			if (FILE == NULL)
				cout << "Не удалось создать файл: " <<GetLastError() <<endl;
			else cout << "Файл успешно создан" << endl;
			break;
		case 2:
			system("cls");
			if (FILE == NULL)
				cout << "Сначала создайте файл" << endl;
			else
			{
				ADR =MapViewOfFile(FILE, FILE_MAP_ALL_ACCESS, 0, 0, MAX_BUF);
				if (ADR != NULL) cout << "Файл успешно спроецирован" << endl;
				else cout << "Ошибка: " << GetLastError();
			}
			break;
		case 3:
			system("cls");
			if (ADR == NULL && FILE!=NULL)
			{
				cout << "Не удалось спроецировать фрагмент файла в память: " << GetLastError() << endl;
				CloseHandle(FILE);
			}
			else if (ADR!=NULL && FILE!=NULL)
			{
				cout << "Введите данные :" << endl;
				string tmp="";
				cin >> tmp;

				
				CopyMemory((LPVOID)ADR, (CHAR*)tmp.c_str(), tmp.length()*sizeof(char));
				cout << "Запись произведена, откройте программу-чтеца" << endl;
				cout << "Вернитесь в эту программу после, окончания работы со второй и нажмите любую клавишу" << endl;
				system("pause");
				cout << "Подождите 5 секунд";
				Sleep(5000);
				if (ADR != NULL && FILE != NULL)
				{
					UnmapViewOfFile(ADR);
					CloseHandle(FILE);
				}
				
				system("pause");
				
				cout << "Данные записаны" << endl;
			}
			break;
		case 4:
			system("cls");
			
			
			cout << "Выходим.." << endl;
			break;
		default :
			system("cls");
			cout << " Такого пункта нет" << endl;
			break;
		}
	} while (k!=4);
	
	
	return 0;
}