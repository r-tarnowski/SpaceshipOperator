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

class PersonWeakestCriteria {
public:

   explicit PersonWeakestCriteria( double valId, const char * pFirstName, const char * pLastName )
         :  value { valId },
            firstName( pFirstName ),
            lastName( pLastName ) {
   }

   PersonWeakestCriteria() = delete;
   ~PersonWeakestCriteria() = default;

   std::partial_ordering operator <=> ( const PersonWeakestCriteria & rhs ) const {

      auto cmp1 = lastName <=> rhs.lastName;
      if ( cmp1 != 0 ) {
         return cmp1; //strong_ordering converted to return type - partial_ordering
      }

      auto cmp2 = firstName <=> rhs.firstName;
      if ( cmp2 != 0 ) {
         return cmp2;
      }

      return value <=> rhs.value;
   }

private:
   double value;
   std::string firstName;
   std::string lastName;
};


class PersonCommonComparisonCategory {

private:
   // Must be declared before using decltype !!!
   double value;
   std::string firstName;
   std::string lastName;

public:

   explicit PersonCommonComparisonCategory( double valId, const char * pFirstName, const char * pLastName )
         :  value { valId },
            firstName( pFirstName ),
            lastName( pLastName ) {
   }

   PersonCommonComparisonCategory() = delete;
   ~PersonCommonComparisonCategory() = default;

   auto operator <=> ( const PersonCommonComparisonCategory & rhs ) const ->
      std::common_comparison_category_t< decltype( firstName <=> rhs.firstName ) , decltype( value <=> rhs.value )> {

      auto cmp1 = lastName <=> rhs.lastName;
      if ( cmp1 != 0 ) {
         return cmp1; //used as or converted to common comparison type
      }

      auto cmp2 = firstName <=> rhs.firstName;
      if ( cmp2 != 0 ) {
         return cmp2;
      }

      return value <=> rhs.value; //used as or converted to common comparison type
   }

};

// Does NOT compile with gcc version 11.3.0 (Ubuntu 11.3.0-1ubuntu1~22.04)
/*
class PersonStrongOrder {

public:

    explicit PersonStrongOrder( double valId, const char * pFirstName, const char * pLastName )
            :  value { valId },
               firstName( pFirstName ),
               lastName( pLastName ) {
    }

    PersonStrongOrder() = delete;
    ~PersonStrongOrder() = default;

    std::strong_ordering operator <=> ( const PersonStrongOrder & rhs ) const {

        auto cmp1 = lastName <=> rhs.lastName;
        if ( cmp1 != 0 ) {
            return cmp1; //return strong_ordering for std::string
        }

        auto cmp2 = firstName <=> rhs.firstName;
        if ( cmp2 != 0 ) {
            return cmp2; //return strong_ordering for std::string
        }
        // map weak/partial comparison result to strong ordering
        return std::strong_order( value, rhs.value);
    }

private:
    double value;
    std::string firstName;
    std::string lastName;

};
*/

class PersonStrongOrderFallback {

public:

    explicit PersonStrongOrderFallback( double valId, const char * pFirstName, const char * pLastName )
            :  value { valId },
               firstName( pFirstName ),
               lastName( pLastName ) {
    }

    PersonStrongOrderFallback() = delete;
    ~PersonStrongOrderFallback() = default;

    std::strong_ordering operator <=> ( const PersonStrongOrderFallback & rhs ) const {

        auto cmp1 = lastName <=> rhs.lastName;
        if ( cmp1 != 0 ) {
            return cmp1; //return strong_ordering for std::string
        }

        auto cmp2 = firstName <=> rhs.firstName;
        if ( cmp2 != 0 ) {
            return cmp2; //return strong_ordering for std::string
        }
        // map weak/partial comparison result to strong ordering
        return std::compare_strong_order_fallback( value, rhs.value);
    }

private:
    double value;
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

   cout << "---------------------------------------------------------------------------------" << endl;
   PersonWeakestCriteria donaldWeakest( 102.1,  "Donald", "Duck" );
   PersonWeakestCriteria johnnyWeakest( 101.1,  "Johnny", "Walker" );

   std::cout << "( std::partial_ordering::less == donaldWeakest <=> johnnyWeakest ) -> " << std::boolalpha
             << ( std::partial_ordering::less == donaldWeakest <=> johnnyWeakest )  << std::endl;
   std::cout << "( std::partial_ordering::equivalent == donaldWeakest <=> johnnyWeakest ) -> " << std::boolalpha
             << ( std::partial_ordering::equivalent == donaldWeakest <=> johnnyWeakest )  << std::endl;
   std::cout << "( std::partial_ordering::greater == donaldWeakest <=> johnnyWeakest ) -> " << std::boolalpha
             << ( std::partial_ordering::greater == donaldWeakest <=> johnnyWeakest )  << std::endl;

   cout << "---------------------------------------------------------------------------------" << endl;
   PersonCommonComparisonCategory donaldCCC( 102.2,  "Donald", "Duck" );
   PersonCommonComparisonCategory johnnyCCC( 101.2,  "Johnny", "Walker" );

   std::cout << "( std::partial_ordering::less == donaldCCC <=> johnnyCCC ) -> " << std::boolalpha
             << ( std::partial_ordering::less == donaldCCC <=> johnnyCCC )  << std::endl;
   std::cout << "( std::partial_ordering::equivalent == donaldCCC <=> johnnyCCC ) -> " << std::boolalpha
             << ( std::partial_ordering::equivalent == donaldCCC <=> johnnyCCC )  << std::endl;
   std::cout << "( std::partial_ordering::greater == donaldCCC <=> johnnyCCC ) -> " << std::boolalpha
             << ( std::partial_ordering::greater == donaldCCC <=> johnnyCCC )  << std::endl;

   cout << "---------------------------------------------------------------------------------" << endl;
   PersonStrongOrderFallback donaldSOF( 102.3,  "Donald", "Duck" );
   PersonStrongOrderFallback johnnySOF( 101.3,  "Johnny", "Walker" );

   std::cout << "( std::strong_ordering::less == donaldSOF <=> johnnySOF ) -> " << std::boolalpha
             << ( std::strong_ordering::less == donaldSOF <=> johnnySOF )  << std::endl;
   std::cout << "( std::strong_ordering::equal == donaldSOF <=> johnnySOF ) -> " << std::boolalpha
             << ( std::strong_ordering::equal == donaldSOF <=> johnnySOF )  << std::endl;
   std::cout << "( std::strong_ordering::greater == donaldSOF <=> johnnySOF ) -> " << std::boolalpha
             << ( std::strong_ordering::greater == donaldSOF <=> johnnySOF )  << std::endl;


    return 0;
}