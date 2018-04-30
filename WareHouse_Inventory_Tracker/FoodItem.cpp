#include "FoodItem.h"


using namespace std;
using namespace boost::gregorian;
FoodItem::FoodItem(string upc, boost::gregorian::date expiration, long long quantity)
  {
    this->upc = upc;
    this-> expiration = expiration;
    this->quantity = quantity;
    //cout<<this->upc<<endl;
  }
FoodItem::~FoodItem()
{
}
date FoodItem::get_expiration()
{
  return this->expiration;
}

void FoodItem::set_quantity(long long newQuant)
{
  this->quantity = newQuant;
}

long long FoodItem::get_quantity()
{
  return this->quantity;
}

string FoodItem::get_upc()
{
  return this->upc;
}
