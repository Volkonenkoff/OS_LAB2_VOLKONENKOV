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
		cout << "1. Открытие спроецированного файла" << endl;
		cout << "2. Вывод данных, введёных с клавиатуры" << endl;
		cout << "3. Выход" << endl;
		cout << "Ввод>> ";
		cin >> k;
		switch (k)
		{
		case '1':
			system("cls");
			HMAP = OF();
			if (HMAP == NULL)
			{
				cout << "Не удалось открыть спроецированный файл: " << GetLastError()<< endl;
			}
			else
			{
				ADR = MapViewOfFile(HMAP, FILE_MAP_ALL_ACCESS, 0, 0, MAX_BUF);
				if (ADR == NULL) cout << "Не удалось открыть файл, попробуйте снова: "<< GetLastError()<< endl;
				else cout << "Данные из спроецриованного файла получены успешно" << endl;
				
			}
			break;
		case '2':
			system("cls");
			if (ADR != NULL)
			{
				cout << "Введенные данные:" << endl;
				CHAR* c_tmp = (CHAR*)ADR;
				for (size_t i = 0; i < strlen(c_tmp); i++)
					cout << c_tmp[i];
				cout << endl;
				UnmapViewOfFile(ADR);
				cout << "Работа завершена, вы можете выйти из этой программы и вернуться в предыдущую" << endl;
			
			}
			else cout << "Не удается вывести данные, попробуйте снова открыть файл" << endl;
			break;
		case '3':
			system("cls");
			cout << "Выходим.." << endl;
			break;
		default:
			system("cls");
			cout << " Такого пункта нет" << endl;
			break;
		}
	} while (k != '3');


	return 0;
}