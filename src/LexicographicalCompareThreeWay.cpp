#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;

void printHeader() {
    cout << endl;
    cout << "================================================" << endl;
    cout << "  C++20 The Complete Guide by Nicolai Josuttis  " << endl;
    cout << "              Spaceship Operator                " << endl;
    cout << "       Lexicographical Compare Three Way        " << endl;
    cout << "================================================" << endl;
    cout << endl;
}

std::ostream & operator << ( std::ostream & strm, std::strong_ordering val ) {
   if ( val < 0 ) {
      return strm << "less";
   }

   if ( val > 0 ) {
      return strm << "greater";
   }

   return strm << "equal";
}

int main(int argc, char *argv[]) {
   printHeader();

   std::vector v1{ 0, 8, 15, 47, 11 };
   std::vector v2{ 0, 15, 8};

   auto r1 = std::lexicographical_compare( v1.begin(), v1.end(), v2.begin(), v2.end() );
   auto r2 = std::lexicographical_compare_three_way( v1.begin(), v1.end(), v2.begin(), v2.end() );

   std::cout << "r1: " << r1 << std::endl;
   std::cout << "r2: " << r2 << std::endl;

}