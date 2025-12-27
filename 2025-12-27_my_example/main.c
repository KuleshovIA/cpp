#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

char setmassptr (char (*a)[10]) {
	for (int i=0; i<10; i++) {
		for (int j=0; j<10; j++) {
			*(*(a+i)+j) = '#';
		}
	}
	**a = '*';
}

char setmass (char a[10][10]){
	for (int i=0; i<10; i++) {
		for (int j=0; j<10; j++) {
			a[i][j] = '#';
		}
	}
	a[0][0] = '*';
	return a[10][10];
}

void outptr (char (*a)[10]) {
	for (int i=0; i<10; i++) {
		for (int j=0; j<10; j++) {
			printf ("%c", *(*(a+i)+j));
		}
		printf ("\n");
	}
}


void out (char a[10][10]) {
	for (int i=0; i<10; i++) {
		for (int j=0; j<10; j++) {
			printf ("%c", a[i][j]);
		}
		printf ("\n");
	}
}

char replaceptr (char (*a)[10]) {
	for (int i=0; i<10; i++) {
		for (int j=0; j<10; j++) {
			if (*(*(a+i)+j) == '*') {
				*(*(a+i)+j) = '#';
				if (j == 9 && i != 9) {
					*(*(a+i+1)) = '*';
					i++;
				}
				else if (j == 9 && i == 9) {
					*(*(a)) = '*';
				}
				else {
					*(*(a+i)+j+1) = '*';
					j++;
				}
			}
		}
	}
}

char replace (char a[10][10]) {
	for (int i=0; i<10; i++) {
		for (int j=0; j<10; j++) {
			if (a[i][j] == '*') {
				a[i][j] = '#';
				if (j == 9 && i != 9) {
					a[i+1][0] = '*';
					i++;
				}
				else if (j == 9 && i == 9) {
					a[0][0] = '*';
				}
				else {
					a[i][j+1] = '*';
					j++;
				}
			}
		}
	}
	return a[10][10];
}

void clear () {
	system ("cls");
}

void wait () {
	Sleep (50);
}



int main () {
	char a[10][10];
	setmassptr (a);
	
	clear ();
	
	for (int q=0; q<2; q++) {
		for (int p=0; p<100; p++) {
			outptr (a);
			replaceptr (a);
			wait ();
			clear ();
		}
	}
	
	return 0;
}