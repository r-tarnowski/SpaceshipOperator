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
    cout << "          Multiple Ordering Criteria            " << endl;
    cout << "================================================" << endl;
    cout << endl;
}

class PersonIntVal {
public:

    explicit PersonIntVal( long int valId, const char * pFirstName, const char * pLastName )
            :  value { valId },
               firstName( pFirstName ),
               lastName( pLastName ) {
    }

    PersonIntVal() = delete;
    ~PersonIntVal() = default;

    auto operator <=> ( const PersonIntVal & rhs ) const {

        auto cmp1 = lastName <=> rhs.lastName;
        if ( cmp1 != 0 ) {
            return cmp1;
        }

        auto cmp2 = firstName <=> rhs.firstName;
        if ( cmp2 != 0 ) {
            return cmp2;
        }

        return value <=> rhs.value;
    }

private:
    long int value;
    std::string firstName;
    std::string lastName;
};

int main( int argc, char *argv[] ) {
    printHeader();

    PersonIntVal donald( 102,  "Donald", "Duck" );
    PersonIntVal johnny( 101,  "Johnny", "Walker" );

    std::cout << "( std::strong_ordering::less == donald <=> johnny ) -> " << std::boolalpha
              << ( std::strong_ordering::less == donald <=> johnny )  << std::endl;
    std::cout << "( std::strong_ordering::equal == donald <=> johnny ) -> " << std::boolalpha
              << ( std::strong_ordering::equal == donald <=> johnny )  << std::endl;
    std::cout << "( std::strong_ordering::greater == donald <=> johnny ) -> " << std::boolalpha
              << ( std::strong_ordering::greater == donald <=> johnny )  << std::endl;


    return 0;
}