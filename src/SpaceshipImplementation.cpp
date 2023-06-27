#include <iostream>
#include <ranges>
#include <compare>

using std::cout;
using std::endl;

void printHeader() {
    cout << endl;
    cout << "================================================" << endl;
    cout << "  C++20 The Complete Guide by Nicolai Josuttis  " << endl;
    cout << "              Spaceship Operator                " << endl;
    cout << "           Implementing operator <=>            " << endl;
    cout << "================================================" << endl;
    cout << endl;
}

class Value {
public:

    explicit Value( long int valId, const char * pName )
            :  id {valId},
               name( pName ) {
    }

    Value() = delete;
    ~Value() = default;

    bool operator == ( const Value & rhs ) const {
        std::cout << name << "::bool operator == called" << std::endl;
        return id == rhs.id;
    }

    auto operator <=> ( const Value & rhs ) const {
        std::cout <<name << "::bool operator <=> called" << std::endl;
        return id <=> rhs.id;
    }



private:
    long int id;
    std::string name;
};



int main(int argc, char *argv[]) {
    printHeader();

   Value v1{1, "v1"};
   Value v2{2, "v2"};
   Value v3{1, "v3"};


    std::cout << "( v1 == v2 ) -> " << ( v1 == v2 ) << std::endl << std::endl;
    std::cout << "( v2 == v1 ) -> " << ( v2 == v1 ) << std::endl << std::endl;

    std::cout << "( v1 == v3 ) -> " << ( v1 == v3 ) << std::endl << std::endl;
    std::cout << "( v3 == v1 ) -> " << ( v3 == v1 ) << std::endl << std::endl;

    std::cout << "( v1 != v2 ) -> " << ( v1 != v2 ) << std::endl << std::endl;
    std::cout << "( v2 != v1 ) -> " << ( v2 != v1 ) << std::endl << std::endl;

    std::cout << "( v1 != v3 ) -> " << ( v1 != v3 ) << std::endl << std::endl;
    std::cout << "( v3 != v1 ) -> " << ( v3 != v1 ) << std::endl << std::endl;

    std::cout << "( v1 > v2 ) -> " << ( v1 > v2 ) << std::endl << std::endl;
    std::cout << "( v2 > v1 ) -> " << ( v2 > v1 ) << std::endl << std::endl;

    std::cout << "( v1 > v3 ) -> " << ( v1 > v3 ) << std::endl << std::endl;
    std::cout << "( v3 > v1 ) -> " << ( v3 > v1 ) << std::endl << std::endl;

    std::cout << "( v1 < v2 ) -> " << ( v1 < v2 ) << std::endl << std::endl;
    std::cout << "( v2 < v1 ) -> " << ( v2 < v1 ) << std::endl << std::endl;

    std::cout << "( v1 < v3 ) -> " << ( v1 < v3 ) << std::endl << std::endl;
    std::cout << "( v3 < v1 ) -> " << ( v3 < v1 ) << std::endl << std::endl;

    std::cout << "( v1 <= v2 ) -> " << ( v1 <= v2 ) << std::endl << std::endl;
    std::cout << "( v2 <= v1 ) -> " << ( v2 <= v1 ) << std::endl << std::endl;

    std::cout << "( v1 <= v3 ) -> " << ( v1 <= v3 ) << std::endl << std::endl;
    std::cout << "( v3 <= v1 ) -> " << ( v3 <= v1 ) << std::endl << std::endl;

    std::cout << "( v1 >= v2 ) -> " << ( v1 >= v2 ) << std::endl << std::endl;
    std::cout << "( v2 >= v1 ) -> " << ( v2 >= v1 ) << std::endl << std::endl;

    std::cout << "( v1 >= v3 ) -> " << ( v1 >= v3 ) << std::endl << std::endl;
    std::cout << "( v3 >= v1 ) -> " << ( v3 >= v1 ) << std::endl << std::endl;

    std::cout << "( 0 > 1 <=> 2 ) -> " << ( 0 > 1 <=> 2 )  << std::endl << std::endl;
    std::cout << "( 0 == 2 <=> 2 ) -> " << ( 0 == 2 <=> 2 )  << std::endl << std::endl;
    std::cout << "( 0 < 3 <=> 2 ) -> " << ( 0 < 3 <=> 2 )  << std::endl << std::endl;

    return 0;
}
