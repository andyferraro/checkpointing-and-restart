#include <iostream>
#include <assert.h>

void foo(int p)
{
++p;
}

void foo2(int const& p)
{
++p;
}

void foo3(int const* p)
{
++(*p);
}


int main()
{
  int j1 = 1234; foo(j1); //assert(j1 == 1234);
  int j2 = 1234; foo2(j2); //assert(j2 == 1234);
  int j3 = 1234; foo3(&j3); //assert(j3 == 1234);
  std::cout << "Hello World!";
}
