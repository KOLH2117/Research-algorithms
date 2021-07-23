#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>
#include <stdlib.h>

#include "DataGenerator.h"

using namespace std;

template <class T>
void HoanVi(T& a, T& b)
{
	T x = a;
	a = b;
	b = x;
}

//-------------------------------------------------

// H�m ph�t sinh mang du lieu ngau nhien
void GenerateRandomData(int a[], int n)
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % n;
	}
}

// H�m ph�t sinh mang du lieu co thu tu tang dan
void GenerateSortedData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
}

// Hamg phat sinh mang du lieu co thu tu nguoc (giam dan)
void GenerateReverseData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = n - 1 - i;
	}
}

// Ham phat sinh mang du lieu gan nhu co thu tu
void GenerateNearlySortedData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 10; i++)
	{
		int r1 = rand() % n;
		int r2 = rand() % n;
		HoanVi(a[r1], a[r2]);
	}
}

void GenerateData(int a[], int n, int dataType)
{
	switch (dataType)
	{
	case 0:	// ngau nhien
		GenerateRandomData(a, n);
		break;
	case 1:	// co thu tu 
		GenerateSortedData(a, n);
		break;
	case 2:	// co thu tu nguoc
		GenerateReverseData(a, n);
		break;
	case 3:	// gan nhu co thu tu
		GenerateNearlySortedData(a, n);
		break;
	default:
		printf("Error: unknown data type!\n");
	}
}