#include<stdio.h> 
#define N 100
double uniform(double,double,long int *); 
 int main() 
 { 
	 double a,b,x,avg_1,avg_n,V_X_N_ba,E_X_N_ba,k[N];
     int i,j,n; 
     long int s; 
     a = 0.0; b = 1.0; s = 13579; 
	 avg_n = 0.0; V_X_N_ba = 0.0;
	 scanf("%d",&n);
	 for(j = 0;j < N;j++)
	 {
		 avg_1 = 0.0;
		 for(i = 0;i < n;i++) 
		 { 
			 avg_1 += uniform(a,b,&s);
		 }
		avg_n += avg_1 / n;
		k[j] = avg_1 / n;
	 }
	 E_X_N_ba = avg_n / N;//¾ùÖµ
	 //·½²î
	 for(i = 0;i < n;i++)
	 {
		V_X_N_ba += (k[i] - E_X_N_ba) * (k[i] - E_X_N_ba);
	 }
	 V_X_N_ba /= 100;

	 printf("%.7f %.7f",E_X_N_ba,V_X_N_ba);
	 return 0;
} 
double uniform(double a,double b ,long int *seed) 
{ 
	double t; 
	*seed = 2045 * (*seed) + 1; 
    *seed = *seed - (*seed / 1048576) * 1048576; 
    t = (*seed) / 1048576.0; 
    t = a + (b - a)*t; 
    return t; 
} 