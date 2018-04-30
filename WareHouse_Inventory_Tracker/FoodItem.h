#include <boost/date_time/gregorian/gregorian.hpp>
#include <iostream>
#include<string>
#ifndef FOOD_ITEM
#define FOOD_ITEM
class FoodItem
{
 public:
  FoodItem(std::string upc, boost::gregorian::date expiration, long long quanity);
  ~FoodItem();
  boost::gregorian::date get_expiration();
  void set_quantity(long long newQuant);
  long long get_quantity();
  std::string get_upc();

 private:
  std::string upc;
  boost::gregorian::date expiration;
  long long quantity;

};
#endif
