// Moisés Fernández Zárate
// A0101197049
// Date: 31/05/2020

// Mission 5
// Multithreading
// Programa en el que utilizamos threads para calcular el valor de PI.

#include <stdio.h>
#include <time.h>
#include <Windows.h>

#define AMOUNT_OF_RECTANGLES 1000000000

double deltaX;
double accum = 0.0;
CRITICAL_SECTION cs;

DWORD WINAPI threadRoutine(LPVOID p) {
	double x;
	double fdx;
	double localAccum = 0.0;
	double* initialX = (double*)p;
	double finalX = (*initialX) + deltaX * (AMOUNT_OF_RECTANGLES / 8);
	for (x = *initialX; x < finalX; x += deltaX) {
		fdx = 4.0 / (1.0 + x * x);
		localAccum = localAccum + (fdx * deltaX);
	}
	EnterCriticalSection(&cs);
	accum += localAccum;
	LeaveCriticalSection(&cs);
}

double piSingleThreaded(double deltaX) {
	double x;
	double fdx;
	double localAccum = 0.0;
	double finalX = deltaX * (AMOUNT_OF_RECTANGLES);
	for (x = 0; x < finalX; x += deltaX) {
		fdx = 4.0 / (1.0 + x * x);
		localAccum = localAccum + (fdx * deltaX);
	}

	return localAccum;
}

void main() {
	int i;
	time_t start, stop, startSingle, stopSingle;
	HANDLE t[8];
	double param[8];
	double singleAccum;
	deltaX = 1.0 / AMOUNT_OF_RECTANGLES;
	start = clock();
	InitializeCriticalSection(&cs);

	// Loop to create the threads.
	for (i = 0;i < 8;i++) {
		param[i] = (1.0 / 8) * i;
		t[i] = CreateThread(NULL, 0, &threadRoutine, &param[i], 0, NULL);
	}
	WaitForMultipleObjects(8, &t[0], TRUE, INFINITE);
	// Waits for the critical section so the threads can finish.
	DeleteCriticalSection(&cs);
	stop = clock();
	printf("Multi-threaded PI=%10.15lf Time(%ld)\n", accum, stop - start);

	// Calculates the value but only using a single threads.
	startSingle = clock();
	singleAccum = piSingleThreaded(deltaX);
	stopSingle = clock();
	printf("Single-threaded PI=%10.15lf Time(%ld)\n", singleAccum, stopSingle - startSingle);
}
