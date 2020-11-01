#include <iostream>
#include <Windows.h>

using namespace std;


void PR(DWORD Pro)
{
	switch (Pro)
	{
	case 0:
		cout << "Отсутствие доступа" << endl;
		break;
	case PAGE_EXECUTE:
		cout << "Включено выполнение доступа к зафиксированной области страниц (PAGE_EXECUTE)" << endl;
		break;
	case PAGE_EXECUTE_READ:
		cout << "\t\t\tВключен доступ только для выполнения или чтения к зафиксированной области страниц. " << endl;
		cout << "\t\t\tПопытка записи в зафиксированный регион приводит к нарушению доступа (PAGE_EXECUTE_READ)" << endl;
		break;
	case PAGE_EXECUTE_READWRITE:
		cout << "Включен доступ только для выполнения, чтения или чтения/записи к зафиксированной области страниц (PAGE_EXECUTE_READWRITE)" << endl;
		break;
	case PAGE_EXECUTE_WRITECOPY:
		cout << "Включает доступ только для выполнения, чтения или копирования при записи к сопоставленному представлению объекта сопоставления файлов (PAGE_EXECUTE_WRITECOPY)" << endl;
		break;
	case PAGE_NOACCESS:
		cout << "Отключен весь доступ к зафиксированной области страниц (PAGE_NOACCESS)" << endl;
		break;
	case PAGE_READONLY:
		cout << "Включен доступ только для чтения к зафиксированной области страниц (PAGE_READONLY)" << endl;
		break;
	case PAGE_READWRITE:
		cout << "Включает доступ только для чтения или чтения/записи к зафиксированной области страниц (PAGE_READWRITE)" << endl;
		break;
	case PAGE_WRITECOPY:
		cout << "Включает доступ только для чтения или копирования при записи к сопоставленному представлению объекта сопоставления файлов (PAGE_WRITECOPY)" << endl;
		break;
	case PAGE_TARGETS_INVALID:
		cout << "Все местоположения на страницах установлены в качестве недопустимых целевых объектов для CFG (PAGE_TARGETS_INVALID)" << endl;
		break;
	}
	if ((Pro & PAGE_GUARD) != 0)
	{
		cout << "\t\t\t\tСтраницы в регионе защищены (PAGE_GUARD)" << endl;
	}
	if ((Pro & PAGE_NOCACHE) != 0)
	{
		cout << "\t\t\t\tСтраницы не кэшируются (PAGE_NOCACHE)" << endl;
	}
	if ((Pro & PAGE_WRITECOMBINE) != 0)
	{
		cout << "\t\t\t\tСтраницы в установлены в режим комбинированной записи (PAGE_WRITECOMBINE)" << endl;
	}
	
}
void VF()
{
	LPVOID adr=NULL;
	BOOL B=FALSE;
	cout << "Введите адрес для возврата физ. памяти";
	cout << " и освобождения региона адресного пространства" << endl;
	cout << "Ввод>> 0x";
	cin >> adr;
	B = VirtualFree(adr, 0, MEM_RELEASE);
	if (B != 0)
		cout << "Регион успешно освобожден" << endl << endl;
	else cerr << "Ошибка: " << GetLastError();
	cout << endl << endl;
}
void VP()
{
	BOOL B=FALSE;
	LPVOID adr = NULL;
	DWORD NPro=0;
	DWORD OPro=0;
	cout << "Введите адрес" << endl;
	cout << "Ввод>> 0x";
	cin >> adr;
	if (adr != NULL) {
		cout << "Введите новый уровень защиты" << endl;
		cout << "Ввод>>";
		cin >> NPro;
		cout << "Новый уровень защиты: ";
		PR(NPro);
		cout << "===========================================" << endl << endl;
		B = VirtualProtect(adr, sizeof(DWORD), NPro, &OPro);
		if (B != 0)
		{
			cout << "Старый уровень защиты"<<endl;
			PR(OPro);
		}
		else cerr << "Ошибка: " << GetLastError()<<endl;

	}
	else cout << "ADR=NULL" << endl;
	cout << endl << endl;

}
void INP()
{
	LPVOID adr=NULL;
	CHAR* c_tmp = NULL;
	string tmp="";
	cout << "Введите данные для записи" << endl;
	cout << "Ввод>> ";
	cin >> tmp;
	cout << "Введите адрес, куда записать данные" << endl;
	cout << "Ввод>> 0x";
	cin >> adr;
	if (adr != NULL)
	{
		c_tmp = (CHAR*)adr;
		CopyMemory(c_tmp, tmp.c_str(), tmp.length() * sizeof(char));
		cout << "Введённая информация:\n" << endl;
		for (size_t i = 0; i < tmp.length(); i++)
			cout << c_tmp[i];
	}
	else cout << "ADR=NULL" << endl;
	cout << endl << endl;
	
}
void VA2(SYSTEM_INFO SI)
{
	
	LPVOID  Badr = NULL, Badr1 = NULL;
	cout << "Резервирование и передача в автоматическом режиме:" << endl;

	
	Badr = VirtualAlloc(NULL, SI.dwPageSize, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (Badr != NULL)
	{
			cout << "Резервирование и передача успешны! Базовый адрес региона 0x" <<Badr<< endl << endl << endl;
			cout << "Резервирование в режиме ввода адреса начала региона" << endl;
			cout << "Введите адрес" << endl;
			cout << "Ввод>> 0x";
			cin >>Badr1;
			Badr = VirtualAlloc(Badr1, SI.dwPageSize, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
			if (Badr != NULL) cout << "Резервирование и передача успешны! Базовый адрес региона 0x"<<Badr << endl << endl << endl;
			else cout << "BASE_ADR=NULL. Резервирование и передача не прошли" << endl;
	}
	else cout << "BASE_ADR=NULL. Резервирование и передача не прошли" << endl;
	
	cout << endl << endl;
}

void VA1(SYSTEM_INFO SI)
{
	LPVOID  Badr = NULL, Badr1 = NULL;
	cout << "Резервирование в автоматическом режиме:" << endl;
	Badr = VirtualAlloc(NULL, SI.dwPageSize, MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (Badr != NULL)
	{
			cout << "Резервирование успешно! Базовый адрес региона 0х"<< Badr << endl << endl << endl;
			cout << "Резервирование в режиме ввода адреса начала региона" << endl;
			cout << "Введите адрес" << endl;
			cout << "Ввод>> 0x";
			cin >> Badr1;
			Badr = VirtualAlloc(Badr1, SI.dwPageSize, MEM_RESERVE, PAGE_EXECUTE_READWRITE);
			if (Badr!=NULL) cout << "Резервирование успешно! Базовый адрес региона 0x"<<Badr << endl << endl << endl;
			else cout << "BASE_ADR=NULL. Резервирование не прошло" << endl;
	}
	else cout << "BASE_ADR=NULL. Резервирование не прошло" << endl;
	cout << endl << endl;
}

void VQ()
{
	SIZE_T S;
	MEMORY_BASIC_INFORMATION MBI;
	S = sizeof(MBI);
	LPVOID adr=NULL;
	cout << "Введите адрес памяти, для участка которого хотите узнать состояние" << endl;
	cout << "Ввод: 0x";
	cin >> adr;
	if (adr != NULL)
	{
		S = VirtualQuery(adr, &MBI, S);
		if (S != 0) {
			cout << "Состояние участка памяти для заданного адреса " << "0x" << hex << adr << ":" << endl;
			cout << "\tУказатель на базовый адрес региона страниц: " << MBI.BaseAddress << endl;
			cout << "\tУказатель на базовый адрес диапазона страниц, выделенных функцией VirtualAlloc: " << MBI.AllocationBase << endl;
			cout << "\tПараметр защиты памяти при первоначальном выделении области: ";
			PR(MBI.AllocationProtect);
			cout << "\tРазмер области, начинающейся с базового адреса, в котором все страницы имеют одинаковые атрибуты, в байтах: " <<dec <<(LONGLONG)MBI.RegionSize << endl << endl;
			cout << "\t\n\tСостояние страниц в регионе: ";
			switch (MBI.State)
			{
			case MEM_COMMIT:
				cout << "Зафиксированны страницы, для которых было выделено физическое хранилище, либо в памяти, либо в файле подкачки на диске" << endl;
				break;
			case MEM_FREE:
				cout << "Есть свободные страницы, недоступные вызывающему процессу и доступные для выделения" << endl;
				break;
			case MEM_RESERVE:
				cout << "Зарезервированны страницы, на которых зарезервирован диапазон виртуального адресного пространства процесса без выделения какого-либо физического хранилища." << endl;
				break;
			}
			cout << "\tЗащита доступа к страницам в регионе: " << MBI.Protect << endl;
			cout << "\tТип страниц в регионе: ";
			switch (MBI.Type)
			{
			case MEM_IMAGE:
				cout << "Страницы в регионе спроецированны в представление изображения раздела" << endl;
				break;
			case MEM_MAPPED:
				cout << "Странице в регионе спроецированны в представление раздела" << endl;
				break;
			case MEM_PRIVATE:
				cout << "Страницы в регионе приватны" << endl;
				break;
			}
		}
		else cerr << "Ошибка: " << GetLastError();
	}
	else cout << "ADR=NULL" << endl;
	
	cout << "=================================================" << endl << endl;
}

void GMS()
{
	MEMORYSTATUSEX MS;
	MS.dwLength = sizeof(MS);
	GlobalMemoryStatusEx(&MS);
	cout << "Информация о памяти компьютера:" << endl;
	cout << "\tПроцент используемой памяти: " << MS.dwMemoryLoad << "%"<< endl;
	cout << "\tОбщий объем физической памяти в байтах: " << MS.ullTotalPhys <<" или "<< (LONGLONG)MS.ullTotalPhys/1024.0/1024.0/1024.0<<" Гб\n"<<endl;
	cout << "\tОбъем доступной физической памяти в байтах: " << MS.ullAvailPhys << " или " << (LONGLONG)MS.ullAvailPhys / 1024.0 / 1024.0 / 1024.0 << " Гб\n" << endl;
	cout << "\tРазмер файла подкачки в байтах: " << MS.ullTotalPageFile << " или " << (LONGLONG)MS.ullTotalPageFile / 1024.0 / 1024.0 / 1024.0 << " Гб\n" << endl;
	cout << "\tДоступный объем байтов в файле подкачки: " << MS.ullAvailPageFile << " или " << (LONGLONG)MS.ullAvailPageFile / 1024.0 / 1024.0 / 1024.0 << " Гб\n" << endl;
	cout << "\tОбщий объем виртуальной памяти в байтах: " << MS.ullTotalVirtual << " или " << (LONGLONG)MS.ullTotalVirtual / 1024.0 / 1024.0 / 1024.0 << " Гб\n" << endl;
	cout << "\tОбъем доступной виртуальной памяти: " << MS.ullAvailVirtual << " или " << (LONGLONG)MS.ullAvailVirtual / 1024.0 / 1024.0 / 1024.0 << " Гб\n" << endl << endl << endl;
	cout << "=================================================" << endl << endl;
}


void SI(SYSTEM_INFO si)
{
	
	cout << "Информация о выч. системе: " << endl;
	cout << "\tАрхитектура процессора: ";
	switch (si.wProcessorArchitecture) {
	case PROCESSOR_ARCHITECTURE_AMD64:
		cout << "x64 (AMD или INTEL)" << endl;
		break;
	case PROCESSOR_ARCHITECTURE_IA64:
		cout << "Intel Itanium Processor Family (IPF)" << endl;
		break;
	case PROCESSOR_ARCHITECTURE_INTEL:
		cout << "x86" << endl;
		break;
	case PROCESSOR_ARCHITECTURE_ARM:
		cout << "ARM" << endl;
		break;
	case PROCESSOR_ARCHITECTURE_ARM64:
		cout << "ARM64" << endl;
		break;
	case PROCESSOR_ARCHITECTURE_UNKNOWN:
		cout << "Неизвестная архитектура :o" << endl;
		break;
	}
	cout << "\tРазмер страницы и гранулярность страничной защиты и обязательства: " << si.dwPageSize << endl;
	cout << "\tУказатель на младший адрес памяти, доступный приложениям и библиотекам динамической компоновки: " << si.lpMinimumApplicationAddress << endl;
	cout << "\tУказатель на старший адрес памяти, доступный приложениям и библиотекам динамической компоновки: " << si.lpMaximumApplicationAddress << endl;
	cout << "\tПроцессоры, сконфигурированных в системе:" << endl;
	for (DWORD i = 0; i < si.dwNumberOfProcessors; i++)
	{
		if (((si.dwActiveProcessorMask & i )!= 0) ^ (i==0))
			cout << "\t\tПроцессор " << i<<endl;
	}
	cout << "\tКол-во процессоров в системе: " << si.dwNumberOfProcessors << endl;
	cout << "\tГранулярность для начального адреса, в котором может быть выделена виртуальная память: " << si.dwAllocationGranularity << endl;
	cout << "\tАрхитектурно-зависимый уровень процессора: " << si.wProcessorLevel << endl;
	cout << "\tАрхитектурно-зависимая ревизия процессора: " << si.wProcessorRevision<<endl<<endl<<endl;
	cout << "=================================================" << endl << endl;
}


int main()
{
	int c;
	SYSTEM_INFO MSI;
	GetSystemInfo(&MSI);
	system("chcp 1251");
	system("cls");
	do {
		cout << "1. Получить информацию о выч. системе" << endl;
		cout << "2. Определение статуса виртуальной памяти" << endl;
		cout << "3. Определение состояния конкретного участка памяти по заданному с клавиатуры адресу" << endl;
		cout << "4. Резервирование региона в автоматическом режиме и в режиме ввода адреса начала региона" << endl;
		cout << "5. Резервирование региона и передача ему физической памяти в автоматическом режиме и в режиме ввода адреса начала региона" << endl;
		cout << "6. Запись данных в ячейки памяти по заданным с клавиатуры адресам; " << endl;
		cout << "7. Установка защиты доступа для заданного (с клавиатуры) региона памяти и ее проверка" << endl;
		cout << "8. Возврат физической памяти и освобождение региона адресного пространства заданного(с клавиатуры) региона памяти" << endl;
		cout << "\n0. Выход\n" << endl;
		cout << "Ввод>> ";
		cin >> c;
		switch (c)
		{
		case 1:
			system("cls");
			SI(MSI);
			break;
		case 2:
			system("cls");
			GMS();
			break;
		case 3:
			system("cls");
			VQ();
			break;
		case 4:
			system("cls");
			VA1(MSI);
			break;
		case 5:
			system("cls");
			VA2(MSI);
			break;
		case 6:
			system("cls");
			INP();
			break;
		case 7:
			system("cls");
			VP();
			break;
		case 8:
			system("cls");
			VF();
			break;
		case 0:
			system("cls");
			break;
		default:
			system("cls");
			cout << "Такого пункта нет " << endl;
			break;

		}
	} 
	while (c!=0);
	
	return 0;
}