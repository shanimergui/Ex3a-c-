#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
using namespace std;
namespace ariel{
  class NumberWithUnits {
    private:
      double amount;
      string u;
      friend double check_convert(NumberWithUnits const & a, NumberWithUnits const & b);
    public:
      NumberWithUnits(double amount ,string u) {
        this->amount=amount;
        this->u=u;
      }

      static void read_units(ifstream& units_file);

      // + , - , += , -= , (+) ,(-)
       //+
      friend NumberWithUnits operator+( NumberWithUnits const & a, NumberWithUnits const & b);
      //(+)
      friend NumberWithUnits operator+( NumberWithUnits & value );
      // -
      friend NumberWithUnits operator-( NumberWithUnits const & a, NumberWithUnits const & b );
      // (-)
      friend NumberWithUnits operator-( NumberWithUnits & value );
      //  +=
      friend NumberWithUnits & operator+=( NumberWithUnits & a, NumberWithUnits const & b );
      // -=
      friend NumberWithUnits & operator-=( NumberWithUnits & a, NumberWithUnits const & b );


      // > >= < <= != ==
      //==
      friend bool operator==( NumberWithUnits const & a, NumberWithUnits const & b );
      //!=
      friend bool operator!=( NumberWithUnits const & a, NumberWithUnits const & b );
      //<
      friend bool operator<( NumberWithUnits const & a, NumberWithUnits const & b );
      //<=
      friend bool operator<=( NumberWithUnits const & a, NumberWithUnits const & b );
      //>
      friend bool operator>( NumberWithUnits const & a, NumberWithUnits const & b );
      //>=
      friend bool operator>=( NumberWithUnits const & a, NumberWithUnits const & b );

      // prefix ++ --  postfix ++ ---
      //prefix
      friend NumberWithUnits & operator++( NumberWithUnits & value );
      //postfix
      friend NumberWithUnits operator++( NumberWithUnits & value, int x);
      //prefix
      friend NumberWithUnits & operator--( NumberWithUnits & value );
      //postfix
      friend NumberWithUnits operator--( NumberWithUnits & value, int x);

      //*
      friend NumberWithUnits operator*(NumberWithUnits const & a, double x);
      friend NumberWithUnits operator*(double x, NumberWithUnits const & a);

      // << >>
      friend ostream & operator<<(ostream& os, NumberWithUnits const & a);
      friend istream & operator>>(istream& is,NumberWithUnits& a);
  };
}
