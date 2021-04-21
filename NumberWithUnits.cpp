#include "NumberWithUnits.hpp"

namespace ariel{

  unordered_map<string, unordered_map<string,double>> umap;

  double check_convert(NumberWithUnits const & a, NumberWithUnits const & b){
    if((a.u==b.u) && (umap.find(a.u) !=umap.end())) { return b.amount;}
    if((umap.find(a.u) != umap.end()) && (umap[a.u].find(b.u) != umap[a.u].end())){
        return b.amount*umap[b.u][a.u];
    }else{
      string message = string("Units do not match - [") +b.u+ string("] cannot be converted to [") +a.u+ string("]");
      __throw_invalid_argument(message.c_str());
    }
    return -1;
  }

  void NumberWithUnits::read_units(ifstream& units_file){
    //1 km = 1000 m
    double amount1=0;
    string u1;
    string temp;
    double amount2=0;
    string u2;
    while (units_file >> amount1 >> u1 >> temp >> amount2 >> u2)
    {
      umap[u1][u2]=amount2;
      umap[u2][u1]=amount1/amount2;
    }
  }

  // + , - , += , -= , (+) ,(-)
   //+
  NumberWithUnits operator+( NumberWithUnits const & a, NumberWithUnits const & b){
    double ans_b=check_convert(a,b);
    return NumberWithUnits(a.amount+ans_b,a.u);
  }
  //(+)
  NumberWithUnits operator+( NumberWithUnits & value ){
    if(value.amount<0){
      double ans = value.amount*-1;
      return NumberWithUnits(ans,value.u);
    }
    return NumberWithUnits(value.amount,value.u);
  }
  // -
  NumberWithUnits operator-( NumberWithUnits const & a, NumberWithUnits const & b ){
    double ans_b=check_convert(a,b);
    return NumberWithUnits(a.amount-ans_b,a.u);
  }
  // (-)
  NumberWithUnits operator-( NumberWithUnits & value){
    if(value.amount>0){
        double ans = value.amount*-1;
        return NumberWithUnits(ans,value.u);
    }
    return NumberWithUnits(value.amount,value.u);
  }
  //  +=
  NumberWithUnits & operator+=( NumberWithUnits & a, NumberWithUnits const & b ){
    double ans_b=check_convert(a,b);
    a.amount+=ans_b;
    return a;
  }
  // -=
  NumberWithUnits & operator-=( NumberWithUnits & a, NumberWithUnits const & b ){
    double ans_b=check_convert(a,b);
    a.amount-=ans_b;
    return a;
  }


  // > >= < <= != ==
  //==
  bool operator==( NumberWithUnits const & a, NumberWithUnits const & b ){
    double ans_b=check_convert(a,b);
    const double eps=0.001;
    if( abs(a.amount-ans_b)<eps){
      return true;
    }
    return false;
  }
  //!=
  bool operator!=( NumberWithUnits const & a, NumberWithUnits const & b ){
    double ans_b=check_convert(a,b);
    if(a.amount!=ans_b){
      return true;
    }
    return false;
  }
  //<
  bool operator<( NumberWithUnits const & a, NumberWithUnits const & b ){
    double ans_b=check_convert(a,b);
    if(a.amount<ans_b){
      return true;
    }
    return false;
  }
  //<=
  bool operator<=( NumberWithUnits const & a, NumberWithUnits const & b ){
    double ans_b=check_convert(a,b);
    if(a.amount<=ans_b){
      return true;
    }
    return false;
  }
  //>
  bool operator>( NumberWithUnits const & a, NumberWithUnits const & b ){
    double ans_b=check_convert(a,b);
    if(a.amount>ans_b){
      return true;
    }
    return false;
  }
  //>=
  bool operator>=( NumberWithUnits const & a, NumberWithUnits const & b ){
    double ans_b=check_convert(a,b);
    if(a.amount>=ans_b){
      return true;
    }
    return false;
  }

  // prefix ++ --  postfix ++ ---
  //prefix
  NumberWithUnits & operator++( NumberWithUnits & value ){
    value.amount++;
    return value;
  }
  //postfix
  NumberWithUnits operator++( NumberWithUnits & value, int x){
    return NumberWithUnits(value.amount++,value.u);
  }
  //prefix
  NumberWithUnits & operator--( NumberWithUnits & value ){
    value.amount--;
    return value;
  }
  //postfix
  NumberWithUnits operator--( NumberWithUnits & value, int x){
    return NumberWithUnits(value.amount--,value.u);
  }

  //*
  NumberWithUnits operator*(NumberWithUnits const & a, double x){
    return NumberWithUnits(a.amount*x,a.u);
  }
  NumberWithUnits operator*(double x, NumberWithUnits const & a){
    return NumberWithUnits(a.amount*x,a.u);
  }

  // << >>
  ostream & operator<<(ostream& os, NumberWithUnits const & a){
    return os<<a.amount<<"["<<a.u<<"]";
    // 5.7[m]
  }
  istream & operator>>(istream& is,NumberWithUnits& a){
    string t;
    return is >> a.amount>> t >> a.u ;
  }
}