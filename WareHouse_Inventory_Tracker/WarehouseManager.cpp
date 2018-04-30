#include "WarehouseManager.h"
using namespace boost::gregorian;
using namespace std;

WarehouseManager::WarehouseManager()
{
}

void WarehouseManager::insertWarehouse(Warehouse  w)
{
  std::pair<string, Warehouse> tempPair(w.get_name(), w);
  warehouses.insert(tempPair);
}

void WarehouseManager::createStockTemplate(std::string upc, int shelfLife,std::string name)
{
  FoodItemTemplate current(upc, shelfLife, name);
  std::pair<string, FoodItemTemplate> tempPair(upc, current);
  stock.insert(tempPair);
}

void WarehouseManager::setDate(boost::gregorian::date timeStamp)
{
  this->timeStamp = timeStamp;
}

void WarehouseManager::incrementDate()
{
  date_duration duration(1);
  this->timeStamp += duration;
}

void WarehouseManager::setPopularity(std::string upc, long long qty)
{
  stock[upc].set_popularity(qty);
}

// Calls update pending method in warehouses
void WarehouseManager::updateItemQty(std::string upc, std::string name, long long qty)
{
  warehouses[name].updatePending(upc, qty);
  
}

void WarehouseManager::processPending()
{
   //Go through all warehouses and parse pending
  for(std::map<string, Warehouse>::iterator it = warehouses.begin(); it != warehouses.end(); ++it)
    {
      //Need to add method to Warehouse
      it->second.processStock(stock, underfilled, timeStamp);
    }
  
}

void  WarehouseManager::processExpiration()
{
  //Go through first el of each vector and check if expired
    for(std::map<string, Warehouse>::iterator it = warehouses.begin(); it != warehouses.end(); ++it)
      {
	it->second.processExpiration(timeStamp, &stock);
      }
}

void WarehouseManager::underfilledOrders()
{

  for(std::map<boost::gregorian::date, set<string> >::iterator it = underfilled.begin(); it != underfilled.end(); ++it)
    {
      for(set<string>::iterator iter = it->second.begin(); iter != it->second.end(); ++iter)
	{
	  date currentDate(it->first);
	  int month = currentDate.month();
	  int day = currentDate.day();
	  int year = currentDate.year();
	  cout.fill('0');
	  cout <<setw(2)<< month << "/" <<setw(2)<< day << "/" << year << " "  << *iter << " " << stock[*iter].get_name()<< endl;
	}
    }
}

void WarehouseManager::wellStockedProducts()
{
  for(std::map<string, FoodItemTemplate>::iterator it = stock.begin(); it != stock.end(); ++it)
    {
      if(it->second.get_numOfLocations() > 1)
	{
	  cout << it->first << " " << it->second.get_name() << endl;
	}
    }
}

void WarehouseManager::mostPopularProducts()
{
  pair<string, long long> first;
  pair<string, long long> second;
  pair<string, long long> third;
  std::map<string, FoodItemTemplate>::iterator it = stock.begin();
  if(stock.size() > 0)
    {
      first = make_pair("",0);
      second = make_pair("",0);
      third = make_pair("",0);
      for(std::map<string, FoodItemTemplate>::iterator it = stock.begin(); it != stock.end(); ++it)
	{
	  //Check popularity values 
	  //Is current value greater than the first, if so, trickle down
	  if(it->second.get_popularity() > first.second)
	    {
	      third = second;
	      second = first;
	      first = make_pair(it->first, it->second.get_popularity());
	      
	    }
	  else if(it->second.get_popularity() > second.second)
	    {
	      third = second;
	      second = make_pair(it->first, it->second.get_popularity());
	    }

	  else if(it->second.get_popularity() > third.second)
	    third = make_pair(it->first, it->second.get_popularity());
	}
      if(!(first.second == 0))
	cout<<first.second<< " " <<first.first<< " "<<stock[first.first].get_name()<<endl;
      if(!(second.second == 0))
	cout<<second.second<< " " <<second.first<< " "<<stock[second.first].get_name()<<endl;
      if(!(third.second == 0))
	cout<<third.second<< " " <<third.first<< " "<<stock[third.first].get_name()<<endl;
    }
}
