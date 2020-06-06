#include <stdio.h>
#include <time.h>
#include <Windows.h>

#define AMOUNT_OF_RECTANGLES 100000000

double deltaX;
double accum = 0.0;
CRITICAL_SECTION cs;

//Funcion single thread
void single(){
    time_t start;
    time_t stop;
    int iRec = AMOUNT_OF_RECTANGLES;
    start = clock();
    double width = 1.0 / iRec;
    double x;
    double height;
    double area = 0.0;
    double pi;
    int i;
    for (i = 0; i < iRec; i++){
        x = i * width;
        height = sqrt(1.0 - x * x);
        area += width * height;
    }
    pi = 4.0 * area;
    stop = clock();
    double elapsed = 0.0;
    elapsed += (double)(stop-start)/CLOCKS_PER_SEC;
    printf("%.8g\n", pi);
    printf("Time: %f seconds", elapsed);
    return;
}


DWORD WINAPI threadRoutine(LPVOID p) {
	double x;
	double fdx;
	double localAccum=0.0;
	double *initialX = (double *)p;
	double finalX=(*initialX)+deltaX*(AMOUNT_OF_RECTANGLES/8);
	//printf("x=%lf\n",*initialX);
	for (x=*initialX; x<finalX; x+=deltaX) {
		fdx=4.0/(1.0 + x*x);
		localAccum = localAccum + (fdx*deltaX);
	}
	EnterCriticalSection(&cs);
	accum+=localAccum;
	LeaveCriticalSection(&cs);
}

void main() {
	int i;
	time_t start, stop;
	HANDLE t[8];
	double param[8];
	deltaX=1.0/AMOUNT_OF_RECTANGLES;
	start = clock();

	InitializeCriticalSection(&cs);
// Create the threads
	for (i=0;i<8;i++) {
		param[i]=(1.0/8)*i;
		t[i]=CreateThread(NULL,0,&threadRoutine,&param[i],0,NULL);
	}
	WaitForMultipleObjects(8,&t[0],TRUE,INFINITE);
// Wait for the threads to finish
	DeleteCriticalSection(&cs);
	stop = clock();

	printf("PI=%10.7lf (%ld)\n",accum,(stop-start)/CLOCKS_PER_SEC);

   single();

}