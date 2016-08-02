#include <stdio.h>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <string.h>

//using std::string;
using namespace std;
long intarraysize=3000000000;
long chararraysize=12000000000;
chrono::milliseconds duration(5000);

void writetofile(int* array, long size){
FILE* file = fopen( "myfile.bin", "wb" );
fwrite(array, sizeof(int), size, file);
fclose(file);
}

void intheaparray(){
  long  array_size = intarraysize;
  int *array = new int[array_size]();
  writetofile(array,array_size);
  delete array;
}

int* intheaparray(long array_size){
  int *array = new int[array_size]();
  return array;
}

void intheaparray(int* arrayp, long array_size){
  arrayp = new int[array_size]();
}

void charheaparray(){
  long  array_size = chararraysize;
  char *array = new char[array_size]();
  delete array;
}


void charstackarray(){
  long  array_size = 1200000;
  char array[array_size];
  memset(array,0,sizeof(array));
}

void sleep(chrono::milliseconds dur){
  cout << "Before sleep_for" << endl;
  this_thread::sleep_for(dur);
  cout << "Sleep for 1000ms" << endl;
}

int main() {
  //intheaparray();
  chrono::high_resolution_clock::time_point t1, t2;
  chrono::duration<double> time_span;

  cout << "Start step1" << endl;
  t1 = chrono::high_resolution_clock::now();
  int* array=intheaparray(intarraysize);
  t2 = chrono::high_resolution_clock::now();
  time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
  cout << "Stop step1. " ;
  cout << "It took me " << time_span.count() << " seconds." << endl;

  cout << "Start step2" << endl;
  t1 = chrono::high_resolution_clock::now();
  writetofile(array,intarraysize);
  t2 = chrono::high_resolution_clock::now();
  time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
  cout << "Stop step2. " ;
  cout << "It took me " << time_span.count() << " seconds." << endl;
  delete array;
  //sleep(duration);
  //charheaparray();
  //charstackarray();
  //int stack[1000];
  //delete array;
  //for (int i=0; i<array_size; i++)  array[i] = 0;
  //for (int i=0; i<array_size; i++)  array[i] = 0;
  //cout << "Before sleep_for" << endl;
  //this_thread::sleep_for(duration);
  //cout << "Sleep for 1000ms" << endl;
  return 0;
}

