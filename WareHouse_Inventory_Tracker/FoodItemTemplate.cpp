#include"FoodItemTemplate.h"
#include<iostream>
#include<stdio.h>
#include  <boost/unordered_map.hpp> //Only temporary for debugging setNumofLocations
using namespace std;

  //Default for boost libraries
FoodItemTemplate::FoodItemTemplate()
  {
    this->upc = "";
    this->shelfLife = 0;
    this->name = "";
    this->popularity = 0;
    this->numOfLocations = 0;
  }
  FoodItemTemplate::FoodItemTemplate(string upc, int shelfLife, string name)
  {
    this->upc = upc;
    this->shelfLife = shelfLife;
    this->name = name;
    this->popularity = 0;
    this->numOfLocations = 0;
  }
  string FoodItemTemplate::get_name()
  {
    return name;
  }
  bool FoodItemTemplate::operator<( const FoodItemTemplate& other ) const
  {
    return (upc < other.get_upc());
  }
  string FoodItemTemplate::get_upc() const
  {
    return upc;
  }
  int FoodItemTemplate::get_shelfLife()
  {
    return shelfLife;
  }
  long long FoodItemTemplate::get_popularity()
  {
    return popularity;
  }
  int FoodItemTemplate::get_numOfLocations()
  {
    return numOfLocations;
  }
  void FoodItemTemplate::set_popularity(long long pop)
  {
    //cout<<"Before = "<<this->popularity<<endl;
    this->popularity += pop;
    //cout<<"After = "<<this->popularity<<endl;
  }
void FoodItemTemplate::set_numOfLocations(int num, boost::gregorian::date & timeStamp)
  {
    this->numOfLocations += num;
    //    cout<<"Number passed: "<<num<<" Num of Locations: "<<numOfLocations<<" Date: "<<timeStamp<<endl;
    // if(numOfLocations < 0)
    //numOfLocations = 0;
    //std::cout<<"Name: "<<name<<" Num of loc "<<numOfLocations<<std::endl;
    // printf("Name: %s, Num of loc: %d",name.c_str(),numOfLocations);
  }


