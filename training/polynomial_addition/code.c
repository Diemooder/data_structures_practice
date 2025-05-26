#include <stdio.h>
#define MAX_NUMBER 100

typedef struct{
	int degree;
	int coef[MAX_NUMBER];
}Polynomial;

int max_number(int a, int b) { return a > b ? a : b; }

Polynomial add_polynomial(Polynomial a, Polynomial b){
	Polynomial c;

	int posA = 0, posB = 0, posC = 0;
	int degreeA = a.degree;
	int degreeB = b.degree;
	c.degree = max_number(degreeA, degreeB);

	while(posA <= a.degree && posB <= b.degree){
		if(degreeA > degreeB){
			c.coef[posC++] = a.coef[posA++];
			degreeA--;
		}else if(degreeA == degreeB){
			c.coef[posC++] = a.coef[posA++] + b.coef[posB++];
			degreeA--;
			degreeB--;
		}else{
			c.coef[posC++] = b.coef[posB++];
			degreeB--;
		}
	}
	return c;
}

int main(){

	return 0;
}
