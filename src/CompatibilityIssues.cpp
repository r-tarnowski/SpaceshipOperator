#include <iostream>

using std::cout;
using std::endl;

void printHeader() {
   cout << endl;
   cout << "================================================" << endl;
   cout << "  C++20 The Complete Guide by Nicolai Josuttis  " << endl;
   cout << "              Spaceship Operator                " << endl;
   cout << "             Compatibility Issues               " << endl;
   cout << "================================================" << endl;
   cout << endl;
}

class MyType {
private:
   int value;

public:
   MyType( int i )
      : value( i ) {
      std::cout << "MyType( int i ) called, i: " << i << std::endl;
   }

   bool operator == (const MyType & rhs) const {
      std::cout << "operator == (const MyType & rhs) called, value: " << value
                << ", rhs.value: " << rhs.value << std::endl;
      return value == rhs.value;
   }

};

bool operator == ( int i, MyType & t )  {
   std::cout << "operator == ( int i, MyType & t ) called" << std::endl;
   //return t == i; - warning: in C++20 this comparison calls the current function recursively with reversed arguments
   return t == MyType{ i };
}

int main(int argc, char *argv[]) {
    printHeader();

    MyType x = 42;
    MyType y = 24;
   std::cout << "----------------------------------------------------------------" << std::endl;

    std::cout<< " if ( x == y ):" << std::endl;
    if ( x == y ) {
       cout << "x == y" << std::endl;
    }
    else {
       cout << "x != y" << std::endl;
    }
    std::cout << "----------------------------------------------------------------" << std::endl;

   std::cout<< " if ( x == 0 ):" << std::endl;
   if ( x == 0 ) {
      cout << "x == 0" << std::endl;
   }
   else {
      cout << "x != 0" << std::endl;
   }
   std::cout << "----------------------------------------------------------------" << std::endl;

   std::cout<< " if ( 1 == y ):" << std::endl;
   if ( 1 == y ) {
      cout << "1 == y" << std::endl;
   }
   else {
      cout << "1 != y" << std::endl;
   }
   std::cout << "----------------------------------------------------------------" << std::endl;

   std::cout<< " if ( y == 24 ):" << std::endl;
   if ( y == 24 ) {
      cout << "y == 24" << std::endl;
   }
   else {
      cout << "y != 24" << std::endl;
   }
   std::cout << "----------------------------------------------------------------" << std::endl;

}