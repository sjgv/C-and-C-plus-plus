
#ifndef WAREHOUSEMANAGER_H
#define WAREHOUSEMANAGER_H
#include<set>
#include<map>
#include<string>
#include<iostream>
#include"Warehouse.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/unordered_map.hpp>
#include"FoodItemTemplate.h"

class WarehouseManager
{
 private:
  //All maps go here
  //Date
  boost::gregorian::date timeStamp;
  std::map<std::string, FoodItemTemplate> stock;
  std::map<std::string, Warehouse> warehouses;
  std::map<boost::gregorian::date, std::set<std::string> > underfilled;
 public:
  WarehouseManager();
  void insertWarehouse(Warehouse w);
  void createStockTemplate(std::string upc, int shelfLife,std::string name);
  void setDate(boost::gregorian::date timeStamp);
  void incrementDate();
  void setPopularity(std::string upc, long long qty);
  void updateItemQty(std::string upc, std::string name, long long qty);  
  void processPending();
  void processExpiration();
  void underfilledOrders();
  void wellStockedProducts();
  void mostPopularProducts(); 
};
#endif
