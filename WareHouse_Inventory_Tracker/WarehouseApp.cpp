/* This class takes the name of a file as an argument and parses
 * the document to create a report of 
 * -Underfilled Orders
 * -Well-Stocked Products
 * -Most Popular items
 *
 * We originally coded all of these with boost unordered _map and unordered_set,
 * for the sake of their O(1) lookup time. After compiling, though, we had a 
 * runtime error that stemmed from inside the boost library initializing methods.
 * After some googling, it appears to be some kind of linking issue??? We err on
 * the side of working code rather than perfect code, and hopefully it meets the
 * requirements
 *
 * Written by Chadwick, Sara & Gutierrez, Salvador 2018
 */

#include<string>
#include<iostream>
#include<fstream>
#include<iterator>
#include<stdlib.h>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <cstring>
#include "FoodItem.h"
#include "Warehouse.h"
#include"WarehouseManager.h"
#include  <boost/unordered_map.hpp> 
#include <stdlib.h>
#include <time.h>
using namespace std;
using namespace boost::gregorian;

void warehouseParser(string line, WarehouseManager & manager)
{
  //Find name of warehouse
  string word;
  word = line.substr(3, line.find('\n'));
  //Create warehouse and add to set
  Warehouse temp(word);
  manager.insertWarehouse(temp);
}

void foodItemParser(string line, WarehouseManager & manager)
{
  string upc;
  int shelfLife;
  string name;
  char * buffer = new char[32];
  string word;
  string superTemp;
  int linePos;
  size_t pos = line.find("Name:");
  //UPC
  upc = line.substr(13,10);
  //Shelf Life
  line = line.substr(37,line.find('\n'));
  word = line.substr(0,line.find(' '));
  superTemp = word;
  strcpy(buffer,superTemp.c_str());
  shelfLife = atoi(buffer);
  delete[] buffer;
  //Name 
  line = line.substr(9,line.find('\n'));
  int i;
  for(i = 0; i < line.length(); i++)
    {
      if (line.at(i) != ' ') 
	break;
    }
  name = line.substr(i,line.length());
  //Add to set
  manager.createStockTemplate(upc, shelfLife, name);

}

void dateParser(ifstream & in, WarehouseManager & manager)
{
  string word;
  string day;
  string year;
  string month;
  in>>word;in>>word;
  month = word.substr(0,2);
  day = word.substr(3,2);
  year = word.substr(6,4);
  date d(from_undelimited_string(year+month+day));
  manager.setDate(d);
}

void reqRecParser(ifstream & in, string reqRec, WarehouseManager & manager)
{
  string upCode;
  string quantity;
  string name;
  char * buffer = new char[quantity.length()];
  in >> upCode;
  in>> quantity;
  getline(in,name);
  name = name.substr(1, name.find('\n'));
  strcpy(buffer,quantity.c_str());
  long long qty = atoll(buffer);
  delete[] buffer;
  if(reqRec == "Request:")
    {
      //Bitwise negation, cuz we are CS geeks
      manager.setPopularity(upCode, qty);
      qty = ~qty+1;
    }
  manager.updateItemQty(upCode, name, qty);
}

void nextParser(ifstream & in, WarehouseManager & manager)
{
  manager.processPending();
  manager.incrementDate();
  manager.processExpiration();
}

void endParser(WarehouseManager & manager)
{
  manager.processPending();
  cout << "Report by Salvador Gutierrez and Sara Chadwick" << endl;
  cout << endl;
  cout << "Underfilled orders:" << endl;
  manager.underfilledOrders();
  cout << endl;
  cout << "Well-Stocked Products:" << endl;
  manager.wellStockedProducts();
  cout << endl;
  cout << "Most Popular Products:" << endl;
  manager.mostPopularProducts(); 
  cout << endl;
}

//MAIN
int main(int argc, char* argv[])
{
  clock_t t1,t2;
  t1 = clock();
  WarehouseManager manager; 
    string line;
    if(argc < 2 || argc > 2)
      {
	cout<<"Only one file is accepted as argument"<<endl;
	exit(EXIT_FAILURE);
      }

    std::ifstream in(argv[1]);
    while (true)
    {
      std::string word;
      in >> word;
   
      if(word == "FoodItem")
	{
	  getline(in,line);
	  foodItemParser(line, manager);
	}
      else if(word == "Warehouse")
	{
	  getline(in,line);
	  warehouseParser(line, manager);	  
	}
      else if(word == "Start")
	{
	  dateParser(in, manager);
	}
      else if(word == "Receive:")
	{
	  reqRecParser(in, word, manager);
	}
      else if(word == "Request:")
	{
	  reqRecParser(in, word, manager);
	}
      else if(word =="Next")
	{
	  nextParser(in, manager);
	}
      else if(word =="End")
	{
	  endParser(manager);
	}

      if (in.fail()){
	break;
      }

    }
    in.close();
    t2 = clock();
    float diff((float) t2 - (float)t1);
    cout<<"Run Time: "<<diff/CLOCKS_PER_SEC<<endl;
    system("pause");
    return 0;
}
