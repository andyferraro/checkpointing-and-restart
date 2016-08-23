#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

long size1=1000000;
long size2=5000000000;

chrono::high_resolution_clock::time_point t01, t02;
chrono::duration<double> dt1;

void printarray1(char *p1){
 for(int i=0; i<10; i++)
  cout<<p1[i]<<endl;
}

void initializearray1(char *p1, long size){
 for(long i=0; i<size; i++)
  p1[i]='a';
}

template<typename T> void printarray3(vector<T> p3){
for (T p:p3)
 cout << p << endl;
}

int main() {

t01 = chrono::high_resolution_clock::now();
char array1[size1];
initializearray1(array1, size1);
t02 = chrono::high_resolution_clock::now();
dt1 = chrono::duration_cast<chrono::duration<double>>(t02 - t01);
cout << "dt01: " << dt1.count() << endl;

t01 = chrono::high_resolution_clock::now();
char *array2 = new char[size2];
initializearray1(array2,size2);
t02 = chrono::high_resolution_clock::now();
dt1 = chrono::duration_cast<chrono::duration<double>>(t02 - t01);
cout << "dt01: " << dt1.count() << endl;

this_thread::sleep_for(std::chrono::milliseconds(10000));

t01 = chrono::high_resolution_clock::now();
vector<char> array3(size2,'a');
t02 = chrono::high_resolution_clock::now();
dt1 = chrono::duration_cast<chrono::duration<double>>(t02 - t01);
cout << "dt01: " << dt1.count() << endl;

this_thread::sleep_for(std::chrono::milliseconds(10000));



return 0;
}

