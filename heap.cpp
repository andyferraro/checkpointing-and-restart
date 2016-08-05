#include <stdio.h>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <string.h>
#include "tclap/CmdLine.h"

#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

//#include <fstream>

//using std::string;
using namespace std;
using namespace TCLAP;
long defaultintarraysize=3000000000, intarraysize;
long chararraysize=12000000000;
chrono::milliseconds duration(5000);
string defaultfilename="myfile.bin",filename;

void writetofile(string myfilename, int* array, long size, bool sync){
 chrono::high_resolution_clock::time_point t01, t02, t03, t04;
 chrono::duration<double> dt1,dt2,dt3;
 //chrono::duration<double> dt01, dt02, dt03, dt04; 

 char *fn = const_cast<char*>(myfilename.c_str());
 FILE* file = fopen( fn, "wb" );
 t01 = chrono::high_resolution_clock::now();
 fwrite(array, sizeof(int), size, file);
 t02 = chrono::high_resolution_clock::now();
 if(sync) {
  cout << "flushing" << endl;
  fflush(file);
  //fsync(fileno(file));
  cout << "flushed" << endl;
 }
 t03 = chrono::high_resolution_clock::now();
 fclose(file);
 t04 = chrono::high_resolution_clock::now();
 //auto nt01=chrono::duration_cast<chrono::nanoseconds>(t01.time_since_epoch()).count();
 //auto nt02=chrono::duration_cast<chrono::nanoseconds>(t02.time_since_epoch()).count();
 //auto nt03=chrono::duration_cast<chrono::nanoseconds>(t03.time_since_epoch()).count();
 //auto nt04=chrono::duration_cast<chrono::nanoseconds>(t04.time_since_epoch()).count();
 dt1 = chrono::duration_cast<chrono::duration<double>>(t02 - t01);
 dt2 = chrono::duration_cast<chrono::duration<double>>(t03 - t01);
 dt3 = chrono::duration_cast<chrono::duration<double>>(t04 - t01);
 //dt01= duration_cast<nanoseconds>(now.time_since_epoch()).count();
 //auto dt001= chrono::duration_cast<nanoseconds>(t01.time_since_epoch()).count();
 cout << "dt01: " << dt1.count() << endl;
 cout << "dt02: " << dt2.count() << endl;
 cout << "dt03: " << dt3.count() << endl;
}

void writetofile2(string myfilename, int* array, long size, bool sync){
 chrono::high_resolution_clock::time_point t01, t02, t03, t04;
 chrono::duration<double> dt1,dt2,dt3;
 int input_fd, output_fd;   
 ssize_t ret_in, ret_out;  
 //char buffer[BUF_SIZE];   
 string myfilename2=myfilename+"2";
 char *fn = const_cast<char*>(myfilename2.c_str());
 output_fd = open(fn, O_WRONLY | O_CREAT, 0644);
 //ret_out = write (output_fd, array, (ssize_t) );
 t01 = chrono::high_resolution_clock::now();
 ret_out = write (output_fd, array, size );
 t02 = chrono::high_resolution_clock::now();
 if(sync) {
  cout << "syncing" << endl;
  fsync(output_fd);
  //fsync(fileno(file));
  cout << "synced" << endl;
 }
 t03 = chrono::high_resolution_clock::now();
 close(output_fd);
 t04 = chrono::high_resolution_clock::now();
 dt1 = chrono::duration_cast<chrono::duration<double>>(t02 - t01);
 dt2 = chrono::duration_cast<chrono::duration<double>>(t03 - t01);
 dt3 = chrono::duration_cast<chrono::duration<double>>(t04 - t01);
 cout << "dt01: " << dt1.count() << endl;
 cout << "dt02: " << dt2.count() << endl;
 cout << "dt03: " << dt3.count() << endl;
}


void readfromfile(int* array, long size){
char *fn = const_cast<char*>(filename.c_str());
FILE* file = fopen( fn, "rb" );
fread(array, sizeof(int), size, file);
fclose(file);
}

/*
void intheaparray(){
  long  array_size = intarraysize;
  int *array = new int[array_size]();
  writetofile(array,array_size);
  delete array;
}
*/

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

int main(int argc, char** argv) {
try{
  //intheaparray();
  CmdLine cmd("By A.Ferraro", ' ', "0.1");
  ValueArg<long> intarraysizeArg("s","s","Size of the array",false,defaultintarraysize,"long");
  cmd.add(intarraysizeArg);

  ValueArg<string> filenameArg("n","name","Name of the file",false,defaultfilename,"string");
  cmd.add(filenameArg);

  SwitchArg writeSwitch("w","write","Write the array to disk", false);
  cmd.add( writeSwitch );

  SwitchArg readSwitch("r","read","Read the array from disk", false);
  cmd.add( readSwitch );

  SwitchArg syncSwitch("f","fsync","Write and sync the array to disk", false);
  cmd.add( syncSwitch );

  cmd.parse( argc, argv );
  intarraysize = intarraysizeArg.getValue();
  filename=filenameArg.getValue();
  bool write=writeSwitch.getValue();
  bool read=readSwitch.getValue();
  bool sync=syncSwitch.getValue();

  chrono::high_resolution_clock::time_point t1, t2;
  chrono::duration<double> time_span;
  
  cout << endl;;
  cout << "Start creating array" << endl;
  t1 = chrono::high_resolution_clock::now();
  int* array=intheaparray(intarraysize);
  t2 = chrono::high_resolution_clock::now();
  time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
  cout << "Stop creating array. " ;
  cout << "It took me " << time_span.count() << " seconds." << endl;

  if (write){
  cout << endl;;
  cout << "Start writing to disk (fopen,fwrite,fclose glibc)" << endl;
  t1 = chrono::high_resolution_clock::now();
  writetofile(filename, array, intarraysize, sync);
  t2 = chrono::high_resolution_clock::now();
  time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
  cout << "Stop writing. " ;
  cout << "It took me " << time_span.count() << " seconds." << endl;

  cout << endl;;
  cout << "Start writing to disk (open,write,close system calls)" << endl;
  t1 = chrono::high_resolution_clock::now();
  writetofile2(filename, array, intarraysize, sync);
  t2 = chrono::high_resolution_clock::now();
  time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
  cout << "Stop writing. " ;
  cout << "It took me " << time_span.count() << " seconds." << endl;
  //delete array;
  }
  
  if (read){
  cout << "Start step3" << endl;
  t1 = chrono::high_resolution_clock::now();
  readfromfile(array,intarraysize);
  t2 = chrono::high_resolution_clock::now();
  time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
  cout << "Stop step3. " ;
  cout << "It took me " << time_span.count() << " seconds." << endl;
  }

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
} catch (ArgException &e)  // catch any exceptions
        { cerr << "error: " << e.error() << " for arg " << e.argId() << endl; }
  return 0;
}

