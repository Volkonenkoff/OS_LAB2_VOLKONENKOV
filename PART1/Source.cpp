#include <iostream>
#include <Windows.h>

using namespace std;


void PR(DWORD Pro)
{
	switch (Pro)
	{
	case 0:
		cout << "���������� �������" << endl;
		break;
	case PAGE_EXECUTE:
		cout << "�������� ���������� ������� � ��������������� ������� ������� (PAGE_EXECUTE)" << endl;
		break;
	case PAGE_EXECUTE_READ:
		cout << "\t\t\t������� ������ ������ ��� ���������� ��� ������ � ��������������� ������� �������. " << endl;
		cout << "\t\t\t������� ������ � ��������������� ������ �������� � ��������� ������� (PAGE_EXECUTE_READ)" << endl;
		break;
	case PAGE_EXECUTE_READWRITE:
		cout << "������� ������ ������ ��� ����������, ������ ��� ������/������ � ��������������� ������� ������� (PAGE_EXECUTE_READWRITE)" << endl;
		break;
	case PAGE_EXECUTE_WRITECOPY:
		cout << "�������� ������ ������ ��� ����������, ������ ��� ����������� ��� ������ � ��������������� ������������� ������� ������������� ������ (PAGE_EXECUTE_WRITECOPY)" << endl;
		break;
	case PAGE_NOACCESS:
		cout << "�������� ���� ������ � ��������������� ������� ������� (PAGE_NOACCESS)" << endl;
		break;
	case PAGE_READONLY:
		cout << "������� ������ ������ ��� ������ � ��������������� ������� ������� (PAGE_READONLY)" << endl;
		break;
	case PAGE_READWRITE:
		cout << "�������� ������ ������ ��� ������ ��� ������/������ � ��������������� ������� ������� (PAGE_READWRITE)" << endl;
		break;
	case PAGE_WRITECOPY:
		cout << "�������� ������ ������ ��� ������ ��� ����������� ��� ������ � ��������������� ������������� ������� ������������� ������ (PAGE_WRITECOPY)" << endl;
		break;
	case PAGE_TARGETS_INVALID:
		cout << "��� �������������� �� ��������� ����������� � �������� ������������ ������� �������� ��� CFG (PAGE_TARGETS_INVALID)" << endl;
		break;
	}
	if ((Pro & PAGE_GUARD) != 0)
	{
		cout << "\t\t\t\t�������� � ������� �������� (PAGE_GUARD)" << endl;
	}
	if ((Pro & PAGE_NOCACHE) != 0)
	{
		cout << "\t\t\t\t�������� �� ���������� (PAGE_NOCACHE)" << endl;
	}
	if ((Pro & PAGE_WRITECOMBINE) != 0)
	{
		cout << "\t\t\t\t�������� � ����������� � ����� ��������������� ������ (PAGE_WRITECOMBINE)" << endl;
	}
	
}
void VF()
{
	LPVOID adr=NULL;
	BOOL B=FALSE;
	cout << "������� ����� ��� �������� ���. ������";
	cout << " � ������������ ������� ��������� ������������" << endl;
	cout << "����>> 0x";
	cin >> adr;
	B = VirtualFree(adr, 0, MEM_RELEASE);
	if (B != 0)
		cout << "������ ������� ����������" << endl << endl;
	else cerr << "������: " << GetLastError();
	cout << endl << endl;
}
void VP()
{
	BOOL B=FALSE;
	LPVOID adr = NULL;
	DWORD NPro=0;
	DWORD OPro=0;
	cout << "������� �����" << endl;
	cout << "����>> 0x";
	cin >> adr;
	if (adr != NULL) {
		cout << "������� ����� ������� ������" << endl;
		cout << "����>>";
		cin >> NPro;
		cout << "����� ������� ������: ";
		PR(NPro);
		cout << "===========================================" << endl << endl;
		B = VirtualProtect(adr, sizeof(DWORD), NPro, &OPro);
		if (B != 0)
		{
			cout << "������ ������� ������"<<endl;
			PR(OPro);
		}
		else cerr << "������: " << GetLastError()<<endl;

	}
	else cout << "ADR=NULL" << endl;
	cout << endl << endl;

}
void INP()
{
	LPVOID adr=NULL;
	CHAR* c_tmp = NULL;
	string tmp="";
	cout << "������� ������ ��� ������" << endl;
	cout << "����>> ";
	cin >> tmp;
	cout << "������� �����, ���� �������� ������" << endl;
	cout << "����>> 0x";
	cin >> adr;
	if (adr != NULL)
	{
		c_tmp = (CHAR*)adr;
		CopyMemory(c_tmp, tmp.c_str(), tmp.length() * sizeof(char));
		cout << "�������� ����������:\n" << endl;
		for (size_t i = 0; i < tmp.length(); i++)
			cout << c_tmp[i];
	}
	else cout << "ADR=NULL" << endl;
	cout << endl << endl;
	
}
void VA2(SYSTEM_INFO SI)
{
	
	LPVOID  Badr = NULL, Badr1 = NULL;
	cout << "�������������� � �������� � �������������� ������:" << endl;

	
	Badr = VirtualAlloc(NULL, SI.dwPageSize, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (Badr != NULL)
	{
			cout << "�������������� � �������� �������! ������� ����� ������� 0x" <<Badr<< endl << endl << endl;
			cout << "�������������� � ������ ����� ������ ������ �������" << endl;
			cout << "������� �����" << endl;
			cout << "����>> 0x";
			cin >>Badr1;
			Badr = VirtualAlloc(Badr1, SI.dwPageSize, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
			if (Badr != NULL) cout << "�������������� � �������� �������! ������� ����� ������� 0x"<<Badr << endl << endl << endl;
			else cout << "BASE_ADR=NULL. �������������� � �������� �� ������" << endl;
	}
	else cout << "BASE_ADR=NULL. �������������� � �������� �� ������" << endl;
	
	cout << endl << endl;
}

void VA1(SYSTEM_INFO SI)
{
	LPVOID  Badr = NULL, Badr1 = NULL;
	cout << "�������������� � �������������� ������:" << endl;
	Badr = VirtualAlloc(NULL, SI.dwPageSize, MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (Badr != NULL)
	{
			cout << "�������������� �������! ������� ����� ������� 0�"<< Badr << endl << endl << endl;
			cout << "�������������� � ������ ����� ������ ������ �������" << endl;
			cout << "������� �����" << endl;
			cout << "����>> 0x";
			cin >> Badr1;
			Badr = VirtualAlloc(Badr1, SI.dwPageSize, MEM_RESERVE, PAGE_EXECUTE_READWRITE);
			if (Badr!=NULL) cout << "�������������� �������! ������� ����� ������� 0x"<<Badr << endl << endl << endl;
			else cout << "BASE_ADR=NULL. �������������� �� ������" << endl;
	}
	else cout << "BASE_ADR=NULL. �������������� �� ������" << endl;
	cout << endl << endl;
}

void VQ()
{
	SIZE_T S;
	MEMORY_BASIC_INFORMATION MBI;
	S = sizeof(MBI);
	LPVOID adr=NULL;
	cout << "������� ����� ������, ��� ������� �������� ������ ������ ���������" << endl;
	cout << "����: 0x";
	cin >> adr;
	if (adr != NULL)
	{
		S = VirtualQuery(adr, &MBI, S);
		if (S != 0) {
			cout << "��������� ������� ������ ��� ��������� ������ " << "0x" << hex << adr << ":" << endl;
			cout << "\t��������� �� ������� ����� ������� �������: " << MBI.BaseAddress << endl;
			cout << "\t��������� �� ������� ����� ��������� �������, ���������� �������� VirtualAlloc: " << MBI.AllocationBase << endl;
			cout << "\t�������� ������ ������ ��� �������������� ��������� �������: ";
			PR(MBI.AllocationProtect);
			cout << "\t������ �������, ������������ � �������� ������, � ������� ��� �������� ����� ���������� ��������, � ������: " <<dec <<(LONGLONG)MBI.RegionSize << endl << endl;
			cout << "\t\n\t��������� ������� � �������: ";
			switch (MBI.State)
			{
			case MEM_COMMIT:
				cout << "�������������� ��������, ��� ������� ���� �������� ���������� ���������, ���� � ������, ���� � ����� �������� �� �����" << endl;
				break;
			case MEM_FREE:
				cout << "���� ��������� ��������, ����������� ����������� �������� � ��������� ��� ���������" << endl;
				break;
			case MEM_RESERVE:
				cout << "���������������� ��������, �� ������� �������������� �������� ������������ ��������� ������������ �������� ��� ��������� ������-���� ����������� ���������." << endl;
				break;
			}
			cout << "\t������ ������� � ��������� � �������: " << MBI.Protect << endl;
			cout << "\t��� ������� � �������: ";
			switch (MBI.Type)
			{
			case MEM_IMAGE:
				cout << "�������� � ������� �������������� � ������������� ����������� �������" << endl;
				break;
			case MEM_MAPPED:
				cout << "�������� � ������� �������������� � ������������� �������" << endl;
				break;
			case MEM_PRIVATE:
				cout << "�������� � ������� ��������" << endl;
				break;
			}
		}
		else cerr << "������: " << GetLastError();
	}
	else cout << "ADR=NULL" << endl;
	
	cout << "=================================================" << endl << endl;
}

void GMS()
{
	MEMORYSTATUSEX MS;
	MS.dwLength = sizeof(MS);
	GlobalMemoryStatusEx(&MS);
	cout << "���������� � ������ ����������:" << endl;
	cout << "\t������� ������������ ������: " << MS.dwMemoryLoad << "%"<< endl;
	cout << "\t����� ����� ���������� ������ � ������: " << MS.ullTotalPhys <<" ��� "<< (LONGLONG)MS.ullTotalPhys/1024.0/1024.0/1024.0<<" ��\n"<<endl;
	cout << "\t����� ��������� ���������� ������ � ������: " << MS.ullAvailPhys << " ��� " << (LONGLONG)MS.ullAvailPhys / 1024.0 / 1024.0 / 1024.0 << " ��\n" << endl;
	cout << "\t������ ����� �������� � ������: " << MS.ullTotalPageFile << " ��� " << (LONGLONG)MS.ullTotalPageFile / 1024.0 / 1024.0 / 1024.0 << " ��\n" << endl;
	cout << "\t��������� ����� ������ � ����� ��������: " << MS.ullAvailPageFile << " ��� " << (LONGLONG)MS.ullAvailPageFile / 1024.0 / 1024.0 / 1024.0 << " ��\n" << endl;
	cout << "\t����� ����� ����������� ������ � ������: " << MS.ullTotalVirtual << " ��� " << (LONGLONG)MS.ullTotalVirtual / 1024.0 / 1024.0 / 1024.0 << " ��\n" << endl;
	cout << "\t����� ��������� ����������� ������: " << MS.ullAvailVirtual << " ��� " << (LONGLONG)MS.ullAvailVirtual / 1024.0 / 1024.0 / 1024.0 << " ��\n" << endl << endl << endl;
	cout << "=================================================" << endl << endl;
}


void SI(SYSTEM_INFO si)
{
	
	cout << "���������� � ���. �������: " << endl;
	cout << "\t����������� ����������: ";
	switch (si.wProcessorArchitecture) {
	case PROCESSOR_ARCHITECTURE_AMD64:
		cout << "x64 (AMD ��� INTEL)" << endl;
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
		cout << "����������� ����������� :o" << endl;
		break;
	}
	cout << "\t������ �������� � ������������� ���������� ������ � �������������: " << si.dwPageSize << endl;
	cout << "\t��������� �� ������� ����� ������, ��������� ����������� � ����������� ������������ ����������: " << si.lpMinimumApplicationAddress << endl;
	cout << "\t��������� �� ������� ����� ������, ��������� ����������� � ����������� ������������ ����������: " << si.lpMaximumApplicationAddress << endl;
	cout << "\t����������, ������������������ � �������:" << endl;
	for (DWORD i = 0; i < si.dwNumberOfProcessors; i++)
	{
		if (((si.dwActiveProcessorMask & i )!= 0) ^ (i==0))
			cout << "\t\t��������� " << i<<endl;
	}
	cout << "\t���-�� ����������� � �������: " << si.dwNumberOfProcessors << endl;
	cout << "\t������������� ��� ���������� ������, � ������� ����� ���� �������� ����������� ������: " << si.dwAllocationGranularity << endl;
	cout << "\t������������-��������� ������� ����������: " << si.wProcessorLevel << endl;
	cout << "\t������������-��������� ������� ����������: " << si.wProcessorRevision<<endl<<endl<<endl;
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
		cout << "1. �������� ���������� � ���. �������" << endl;
		cout << "2. ����������� ������� ����������� ������" << endl;
		cout << "3. ����������� ��������� ����������� ������� ������ �� ��������� � ���������� ������" << endl;
		cout << "4. �������������� ������� � �������������� ������ � � ������ ����� ������ ������ �������" << endl;
		cout << "5. �������������� ������� � �������� ��� ���������� ������ � �������������� ������ � � ������ ����� ������ ������ �������" << endl;
		cout << "6. ������ ������ � ������ ������ �� �������� � ���������� �������; " << endl;
		cout << "7. ��������� ������ ������� ��� ��������� (� ����������) ������� ������ � �� ��������" << endl;
		cout << "8. ������� ���������� ������ � ������������ ������� ��������� ������������ ���������(� ����������) ������� ������" << endl;
		cout << "\n0. �����\n" << endl;
		cout << "����>> ";
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
			cout << "������ ������ ��� " << endl;
			break;

		}
	} 
	while (c!=0);
	
	return 0;
}