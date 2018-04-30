#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<string>
#include "FoodItem.h"
#include "FoodItemTemplate.h"
#include  <boost/unordered_map.hpp> 

#ifndef WAREHOUSE_H
#define WAREHOUSE_H

class Warehouse
{
 private:
  std::map<std::string,std::vector<FoodItem> > inventory;
  std::string name;   
  std::map<std::string, long long> pending;   
  std::map<std::string, long long> totalStock;    
 public:
  Warehouse(std::string name);
  Warehouse();
  ~Warehouse();
  void receiveStock(std::string upc, FoodItem item);
  bool operator<( const Warehouse& other ) const;
  std::string get_name() const;
  void updatePending(std::string upc, long long qty);
  void processStock(std::map<std::string, FoodItemTemplate> & stock, std::map<boost::gregorian::date, std::set<std::string> > & underfilled, boost::gregorian::date & timeStamp);
  void processExpiration(boost::gregorian::date & timeStamp, std::map<std::string, FoodItemTemplate> * stock);
};
#endif
