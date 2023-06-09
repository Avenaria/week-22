﻿
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <cstdlib>

using namespace std;

char* Lowercase(char* str);
bool Is_leap(int year);
int DateDiff(int day, int day1, int month, int month1, int year, int year1);


//0 BLACK 1 BLUE 2 GREEN 3 CYAN 4 RED 5 MAGENTA
//6 BROWN 7 LIGHTGRAY 8 DARKGRAY 9 LIGHTBLUE 10 LIGHTGREEN 
//11 LIGHTCYAN 12 LIGHTRED 13 LIGHTMAGENTA 14 YELLOW 15 WHITE
#define BACKGROUND 0
#define FOREGROUND 7
#define ITEMSELECT 15
#define MENULEFT 20
#define MENUTOP 4

#define TH cout << " "  << gr.name << ":"  << endl << endl; \
SetConsoleOutputCP(866); \
printf("%c", 213); \
for (int i = 0; i < 4; ++i) printf("%c", 205); printf("%c", 209); \
for (int i = 0; i < 55; ++i) printf("%c", 205); printf("%c", 209); \
for (int i = 0; i < 12; ++i) printf("%c", 205); printf("%c", 209); \
for (int i = 0; i < 7; ++i) printf("%c", 205); printf("%c", 209); \
for (int i = 0; i < 22; ++i) printf("%c", 205); printf("%c\n", 184); \
printf("%c", 179); \
SetConsoleOutputCP(1251); cout << "  "; SetConsoleOutputCP(866); printf("%c", 179); \
SetConsoleOutputCP(1251); printf(" %-53s ", ""); SetConsoleOutputCP(866); printf("%c", 179); \
SetConsoleOutputCP(1251); printf(" %-10s ", " "); SetConsoleOutputCP(866); printf("%c", 179); \
SetConsoleOutputCP(1251); printf(" %s ", " "); SetConsoleOutputCP(866); printf("%c", 179); \
SetConsoleOutputCP(1251); printf(" %-20s ", " "); SetConsoleOutputCP(866); printf("%c\n", 179); \
printf("%c", 198); \
for (int i = 0; i < 4; ++i) printf("%c", 205); 	printf("%c", 216); \
for (int i = 0; i < 55; ++i) printf("%c", 205); printf("%c", 216); \
for (int i = 0; i < 12; ++i) printf("%c", 205); printf("%c", 216); \
for (int i = 0; i < 7; ++i) printf("%c", 205); printf("%c", 216); \
for (int i = 0; i < 22; ++i) printf("%c", 205); printf("%c\n", 181); \
SetConsoleOutputCP(1251);

#define TF SetConsoleOutputCP(866); \
printf("%c", 192); \
for (int i = 0; i < 4; ++i) printf("%c", 196); 	printf("%c", 193); \
for (int i = 0; i < 55; ++i) printf("%c", 196); printf("%c", 193); \
for (int i = 0; i < 12; ++i) printf("%c", 196); printf("%c", 193); \
for (int i = 0; i < 7; ++i) printf("%c", 196); printf("%c", 193); \
for (int i = 0; i < 22; ++i) printf("%c", 196); printf("%c", 217); \
SetConsoleOutputCP(1251);


void gotorc(short c, short r) {
	HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD  coord = { c, r };
	SetConsoleCursorPosition(StdOut, coord);
}
void Color(unsigned short BackC, unsigned short ForgC)
{
	HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	unsigned short c = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
	SetConsoleTextAttribute(StdOut, c);
}
void paintmenu(const char** s, int length, int a)
{
	Color(BACKGROUND, FOREGROUND);
	system("cls");
	gotorc(MENULEFT, MENUTOP);
	cout << "......MENU......\n";
	for (size_t i = 0; i < length; i++)
	{
		gotorc(MENULEFT, MENUTOP + i + 1);
		cout << (i == a ? Color(BACKGROUND, ITEMSELECT), "=>" : "  ");
		cout << s[i] << endl;
		Color(BACKGROUND, FOREGROUND);
	}
}
int menu(const char** s, int sizem, int act = 0)
{
	char c = 80;
	while (1)
	{
		if (c == 72 || c == 80) paintmenu(s, sizem, act);
		c = _getch();
		switch (c)
		{
		case 27: //Esc
			return -1;
		case 80: //down
			++act;
			if (act == sizem) act = 0;
			break;
		case 72://up
			if (act == 0) act = sizem;
			--act;
			break;
		case 13: //Enter
			return act;
		}
	}
}


struct Worker {
	char fname[50], lname[50], mname[50], position[50];
	unsigned int d : 5;
	unsigned int m : 4;
	unsigned int y : 12;
	unsigned int gender : 1;
};

struct Staff {
	char name[20];
	Worker* arr;
	int count;
};

void ShowWorker(Worker& d) {
	printf(" %-23s%-15s%-15s ", d.fname, d.lname, d.mname);
	SetConsoleOutputCP(866); cout << char(179); SetConsoleOutputCP(1251);
	printf(" %02d.%02d.%4d ", d.d, d.m, d.y);
	SetConsoleOutputCP(866); cout << char(179); SetConsoleOutputCP(1251);
	printf("   %s   ", d.gender ? "×" : "Æ");
	SetConsoleOutputCP(866); cout << char(179); SetConsoleOutputCP(1251);
	printf(" %-20s ", d.position);
}

void PrintWorker(Worker& d, FILE* fs) {
	fprintf(fs, " %-23s%-15s%-15s ¦ %02d.%02d.%4d ¦   %s   ¦ %-20s ",
		d.fname, d.lname, d.mname, d.d, d.m, d.y, d.gender ? "×" : "Æ", d.position);
}

void SetWorker(Worker& d) {
	int buf;
	char g;
	SYSTEMTIME st;
	GetSystemTime(&st);

	do {
		cout << " ";
		cin >> buf;	cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
	} while (buf < 1 || 31 < buf);
	d.d = buf;
	do {
		cout << " ";
		cin >> buf; cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
	} while (buf < 1 || 12 < buf);
	d.m = buf;
	do {
		cout << " ";
		cin >> buf; cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
	} while (buf < 1 || st.wYear < buf);
	d.y = buf;
	do {
		cout << " "; cin >> g; cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
	} while (g != '÷' && g != '×' && g != 'æ' && g != 'Æ');
	g == '÷' || g == '×' ? d.gender = 1 : d.gender = 0;
	do {
		cout << " "; cin.getline(d.position, 50);
	} while (!*d.position);
}

void ShowStaff(Worker* Gr, int n, int p = 0) {
	for (int i = p; i < n; i++) {
		SetConsoleOutputCP(866); printf("%c %2d %c", char(179), i + 1, char(179)); SetConsoleOutputCP(1251);
		ShowWorker(Gr[i]);
		SetConsoleOutputCP(866); printf("%c", char(179)); SetConsoleOutputCP(1251);
		cout << endl;
	}
}

void PrintStaff(Worker* Gr, int n, FILE* fs, int p = 0) {
	for (int i = p; i < n; i++) {
		fprintf(fs, "¦ %2d ¦", i + 1);
		PrintWorker(Gr[i], fs);
		fprintf(fs, "¦\n");
	}
}

void AddWorker(Staff& gr, Worker& st) {
	Worker* temp = new Worker[gr.count + 1];
	memcpy(temp, gr.arr, sizeof(Worker) * gr.count);
	temp[gr.count] = st;
	delete[]gr.arr;
	gr.arr = temp;
	gr.count++;
}

void ShowStaff(Staff& gr) {
	TH
		ShowStaff(gr.arr, gr.count);
	TF
}


typedef bool (*TypeFunc)(Staff&, const char*&, int);

bool ByFname(Staff& gr, const char*& key, int i) {
	return *key ? (strstr(Lowercase(gr.arr[i].fname), key)) : 0;
}

bool ByAge(Staff& gr, const char*& key, int i) {
	SYSTEMTIME st;
	GetSystemTime(&st);
	return (DateDiff(gr.arr[i].d, st.wDay, gr.arr[i].m, st.wMonth, gr.arr[i].y, st.wYear) / 365 == atoi(key));
}

bool ByChar(Staff& gr, const char*& key, int i) {
	return (*Lowercase(gr.arr[i].fname) == *key);
}

void FindStaff(Staff& gr, const char* key, TypeFunc FindFunc) {
	int j = 0;
	for (int i = 0; i < gr.count; i++) {
		if (FindFunc(gr, key, i)) {
			j = 1;
			break;
		}
	}
	if (j) {
		TH
			for (int i = 0; i < gr.count; i++) {
				if (FindFunc(gr, key, i)) {
					ShowStaff(gr.arr, i + 1, i);
				}
			}
		TF
	}
	else cout << "\n " << endl;
}

void FindAndPrintStaff(Staff& gr, const char* key, TypeFunc FindFunc, const char* fn) {
	int j = 0;
	for (int i = 0; i < gr.count; i++) {
		if (FindFunc(gr, key, i)) {
			j = 1;
			break;
		}
	}
	FILE* fs = fopen(fn, "w");
	if (!fs) {
		printf("Can't open, exiting...\n");
		exit(-1);
	}
	if (j) {
		fprintf(fs, "==========================================================================================================\n");
		fprintf(fs, "¦                                                  ¦   ¦  ¦              ¦\n");
		fprintf(fs, "=====+=======================================================+============+=======+=======================\n");
		for (int i = 0; i < gr.count; i++) {
			if (FindFunc(gr, key, i)) {
				PrintStaff(gr.arr, i + 1, fs, i);
			}
		}
		fprintf(fs, "-----+-------------------------------------------------------+------------+-------+-----------------------\n");
	}
	else fprintf(fs, "\n ");
	fclose(fs);
}

void EditWorker(Staff& gr, Worker& wrkr, int p) {
	if (p < 0 || gr.count < p) { return; }
	TH
		ShowStaff(gr.arr, p + 1, p);
	TF
		int buf;
	char g;
	SYSTEMTIME st;
	GetSystemTime(&st);
	cout << "\n: "; cin.getline(wrkr.fname, 50);
	if (*wrkr.fname) strcpy_s(gr.arr[p].fname, wrkr.fname);
	cout << ": "; cin.getline(wrkr.lname, 50);
	if (*wrkr.lname) strcpy_s(gr.arr[p].lname, wrkr.lname);
	cout << ": ";  cin.getline(wrkr.mname, 50);
	if (*wrkr.mname) strcpy_s(gr.arr[p].mname, wrkr.mname);
	do {
		cout << " ";
		cin.getline(wrkr.position, 3); cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
		if (*wrkr.position) buf = atoi(wrkr.position); else break;
	} while (buf < 1 || 31 < buf);
	if (*wrkr.position) gr.arr[p].d = buf;
	do {
		cout << " ";
		cin.getline(wrkr.position, 3); cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
		if (*wrkr.position) buf = atoi(wrkr.position); else break;
	} while (buf < 1 || 12 < buf);
	if (*wrkr.position) gr.arr[p].m = buf;
	do {
		cout << " ";
		cin.getline(wrkr.position, 5); cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
		if (*wrkr.position) buf = atoi(wrkr.position); else break;
	} while (buf < 1 || st.wYear < buf);
	if (*wrkr.position) gr.arr[p].y = buf;
	do {
		cout << " ";
		cin.getline(wrkr.position, 2); cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
		if (*wrkr.position) g = *wrkr.position; else break;
	} while (g != '÷' && g != '×' && g != 'æ' && g != 'Æ');
	if (*wrkr.position) g == '÷' || g == '×' ? gr.arr[p].gender = 1 : gr.arr[p].gender = 0;
	cout << " "; cin.getline(wrkr.position, 50);
	if (*wrkr.position) strcpy_s(gr.arr[p].position, wrkr.position);
	cout << endl;
	TH
		ShowStaff(gr.arr, p + 1, p);
	TF
}

void DeleteWorker(Staff& gr, Worker& st, int p) {
	if (p < 0 || p >= gr.count) return;
	Worker* temp = new Worker[gr.count + 1];
	if (p) memcpy(temp, gr.arr, sizeof(Worker) * p - 1);
	memcpy(temp + p, gr.arr + p + 1, sizeof(Worker) * (gr.count - p));
	delete[]gr.arr;
	gr.arr = temp;
	gr.count--;
}

void SaveToFile(Staff& gr, const char* fn) {
	FILE* fs = fopen(fn, "wb");
	if (!fs) {
		printf("Can't open, exiting...\n");
		exit(-1);
	}
	if (fwrite(gr.arr, sizeof(Worker), gr.count, fs) != gr.count)
		printf("\n");
	fclose(fs);
}

void ReadFile(Staff& gr, const char* fn) {
	FILE* fs = fopen(fn, "rb");
	if (!fs) {
		printf(".\n");
		return;
	}
	fseek(fs, 0, SEEK_END);
	int size = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	int structsize = sizeof(Worker);
	if (size % structsize != 0)
		printf(".\n");
	else {
		int count = size / structsize;
		Worker* temp = new Worker[count];
		if (fread(temp, structsize, count, fs) != count)
			printf("\n");
		delete[]gr.arr;
		gr.arr = temp;
		gr.count = count;
	}
	fclose(fs);
}

void SaveSearchResults(Staff& gr, char* key, TypeFunc FindFunc) {
	char d;
	do {
		cout << "\n ";
		cin >> d; cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
	} while (d != 'y' && d != 'Y' && d != 'n' && d != 'N');
	if (d == 'y' || d == 'Y') {
		SYSTEMTIME st;
		GetSystemTime(&st);
		char fn[19];
		sprintf(fn, "%d%02d%02d%02d%02d%02d.txt", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
		FindAndPrintStaff(gr, key, FindFunc, fn);
		cout << "\nå " << fn << endl;
	}
}

int main(void) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Color(BACKGROUND, FOREGROUND);

	Worker wrkr;
	Staff company{ "Espresso-service" };


	const char* s[]{
	 " ",
	 " ",
	 " ",
	 " ",
	 " ",
	 " ",
	 " ",
	 " ",
	 " " };
	int sizem = sizeof(s) / 4;
	int pm = 0;
	char fn[] = "File.bin";

	while (1) {
		pm = menu(s, sizem, pm);
		system("cls");
		if (pm < 0) break;
		if (pm == 0) {
			char* fn = new char[255] { 0 };
			cout << ": "; cin.getline(fn, 255);
			if (!*fn) strcpy(fn, "File.bin");
			ReadFile(company, fn);
			delete[]fn;
		};
		if (pm == 1) {
			ShowStaff(company);
		}
		if (pm == 2) {
			SetWorker(wrkr);
			AddWorker(company, wrkr);
		};
		if (pm == 3) {
			int p;
			cout << " (1 - " << company.count << "): ";
			cin >> p; cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
			if (0 < p && p <= company.count)
				EditWorker(company, wrkr, p - 1);
			else
				cout << "\n  " << p << " í" << endl;
		};
		if (pm == 4) {
			int p;
			cout << " (1 - " << company.count << "): ";
			cin >> p; cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
			if (0 < p && p <= company.count)
				DeleteWorker(company, wrkr, p - 1);
			else
				cout << "\n " << p << " í" << endl;
		};
		if (pm == 5) {
			char* key = new char[50] { 0 };
			cout << " "; cin.getline(key, 50);
			FindStaff(company, Lowercase(key), ByFname);
			SaveSearchResults(company, Lowercase(key), ByFname);
			delete[]key;
		};
		if (pm == 6) {
			char* key = new char[4] { 0 };
			cout << " "; cin.getline(key, 4); cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
			FindStaff(company, key, ByAge);
			SaveSearchResults(company, key, ByAge);
			delete[]key;
		};
		if (pm == 7) {
			char* key = new char[2] { 0 };
			cout << " "; cin.getline(key, 2); cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
			FindStaff(company, Lowercase(key), ByChar);
			SaveSearchResults(company, Lowercase(key), ByChar);
			delete[]key;
		};
		if (pm == 8) {
			char fn[] = "File.bin";
			SaveToFile(company, fn);
			cout << " " << fn << endl;
		}
		Color(BACKGROUND, 2);
		cout << "\ndone\n";
		(void)_getch();
	}
	SaveToFile(company, fn);
	cout << "  " << fn << endl;
	return 0;
}

char* Lowercase(char* str) {
	if (!str) return str;
	int len = strlen(str);
	char* temp = new char[len + 1] { 0 };
	while (*str) {
		(*str >= 65 && *str <= 90 || *str >= -64 && *str <= -33) ? *temp++ = *str + 32 : *temp++ = *str;
		str++;
	}
	return temp - len;
}

bool Is_leap(int year) {
	return ((year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0));
}

int DateDiff(int day, int day1, int month, int month1, int year, int year1) {
	int days_before_month = 30 * month + (month + 5) * 4 / 7 - 35 + 2 * (month < 3);
	int y = year - 1;
	int date = day + days_before_month + (Is_leap(year) && month > 2) + y * 365 + y / 4 - y / 100 + y / 400;

	int days_before_month1 = 30 * month1 + (month1 + 5) * 4 / 7 - 35 + 2 * (month1 < 3);
	int y1 = year1 - 1;
	int date1 = day1 + days_before_month1 + (Is_leap(year1) && month1 > 2) + y1 * 365 + y1 / 4 - y1 / 100 + y1 / 400;
	return (date1 - date);
}