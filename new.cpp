#include<bits/stdc++.h>
using namespace std;

int fib(int n){
 	if(n==1 or n==0){
 		return n;
 	}

 	return fib(n-1) + fib(n-2);
 }
int main(){
	int t;
    while(1){
	clock_t start_time = clock();
	t = start_time/CLOCKS_PER_SEC;
	t = t - 1;
    cout << t << endl;
	t = t - 1;
    }
	fib(44);
	return 0;
}