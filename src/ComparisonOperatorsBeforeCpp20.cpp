#include <iostream>

#include <vector>
#include <set>
#include <ranges>
#include <map>
#include <list>


using std::cout;
using std::endl;

void printHeader() {
    cout << endl;
    cout << "================================================" << endl;
    cout << "  C++20 The Complete Guide by Nicolai Josuttis  " << endl;
    cout << "              Spaceship Operator                " << endl;
    cout << "   Defining Comparison Operators Before C++20   " << endl;
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

    bool operator != ( const Value & rhs ) const {
        std::cout <<name << "::bool operator != called" << std::endl;
        return !( *this == rhs );
    }

    bool operator < ( const Value & rhs ) const {
        std::cout << name << "::bool operator < called" << std::endl;
        return id < rhs.id;
    }

    bool operator <= ( const Value & rhs ) const {
        std::cout << name << "::bool operator <= called" << std::endl;
        return ! ( rhs < * this );
    }

    bool operator > ( const Value & rhs ) const {
        std::cout << name << "::bool operator > called" << std::endl;
        return rhs < * this;
    }

    bool operator >= ( const Value & rhs ) const {
        std::cout << name << "::bool operator >= called" << std::endl;
        return ! ( * this < rhs );
    }

private:
   long int id;
   std::string name;
};

class WellImplementedValue {
public:

    explicit WellImplementedValue( long int valId, const char * pName ) noexcept
            :  id {valId},
               name {pName} {
    }

    WellImplementedValue() = delete;
    ~WellImplementedValue() = default;

    [[ nodiscard ]] friend bool operator == ( const WellImplementedValue & lhs,
                                                        const WellImplementedValue & rhs ) noexcept {
        std::cout << lhs.name << "::bool operator == called" << std::endl;
        return lhs.id == rhs.id;
    }

    [[ nodiscard ]] friend bool operator != ( const WellImplementedValue & lhs,
                                                        const WellImplementedValue & rhs ) noexcept {
        std::cout << lhs.name << "::bool operator != called" << std::endl;
        return !( lhs == rhs );
    }

    [[ nodiscard ]] friend bool operator < ( const WellImplementedValue & lhs,
                                                       const WellImplementedValue & rhs ) noexcept {
        std::cout << lhs.name << "::bool operator < called" << std::endl;
        return lhs.id < rhs.id;
    }

    [[ nodiscard ]] friend bool operator <= ( const WellImplementedValue & lhs,
                                                        const WellImplementedValue & rhs ) noexcept {
        std::cout << lhs.name << "::bool operator <= called" << std::endl;
        return ! ( rhs < lhs );
    }

    [[ nodiscard ]] friend bool operator > ( const WellImplementedValue & lhs,
                                                       const WellImplementedValue & rhs ) noexcept {
        std::cout << lhs.name << "::bool operator > called" << std::endl;
        return rhs < lhs;
    }

    [[ nodiscard ]] friend bool operator >= ( const WellImplementedValue & lhs,
                                                        const WellImplementedValue & rhs ) noexcept {
        std::cout << lhs.name << "::bool operator >= called" << std::endl;
        return ! ( lhs < rhs );
    }

private:
    long int id;
    std::string name;
};

class OnlyEqualOperatorValue {
public:

    explicit OnlyEqualOperatorValue( long int valId, const char * pName ) noexcept
            :  id {valId},
               name {pName} {
    }

    OnlyEqualOperatorValue() = delete;
    ~OnlyEqualOperatorValue() = default;

    [[ nodiscard ]] friend bool operator == ( const OnlyEqualOperatorValue & lhs,
                                              const OnlyEqualOperatorValue & rhs ) noexcept {
        std::cout << lhs.name << "::bool operator == called" << std::endl;
        return lhs.id == rhs.id;
    }


private:
    long int id;
    std::string name;
};



#define IS_WELL_IMPLEMENTED

int main(int argc, char *argv[]) {
    printHeader();
#ifdef IS_WELL_IMPLEMENTED
   WellImplementedValue v1{1, "well_implemented_v1"};
   WellImplementedValue v2{2, "well_implemented_v2"};
   WellImplementedValue v3{1, "well_implemented_v3"};
#else
   Value v1{1, "v1"};
   Value v2{2, "v2"};
   Value v3{1, "v3"};
#endif

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


    OnlyEqualOperatorValue ve1{ 1, "only_equal_operator_ve1"};
    OnlyEqualOperatorValue ve2{ 2, "only_equal_operator_ve2"};
    OnlyEqualOperatorValue ve3{ 1, "only_equal_operator_ve3"};

    std::cout << "( ve1 == ve2 ) -> " << ( ve1 == ve2 ) << std::endl << std::endl;
    std::cout << "( ve2 == ve1 ) -> " << ( ve2 == ve1 ) << std::endl << std::endl;
    std::cout << "( ve1 == ve3 ) -> " << ( ve1 == ve3 ) << std::endl << std::endl;
    std::cout << "( ve3 == ve1 ) -> " << ( ve3 == ve1 ) << std::endl << std::endl;
    std::cout << "( ve1 != ve2 ) -> " << ( ve1 != ve2 ) << std::endl << std::endl;
    std::cout << "( ve2 != ve1 ) -> " << ( ve2 != ve1 ) << std::endl << std::endl;
    std::cout << "( ve1 != ve3 ) -> " << ( ve1 != ve3 ) << std::endl << std::endl;
    std::cout << "( ve3 != ve1 ) -> " << ( ve3 != ve1 ) << std::endl << std::endl;


    return 0;
}

