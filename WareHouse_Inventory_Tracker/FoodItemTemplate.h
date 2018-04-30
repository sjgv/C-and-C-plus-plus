#include<string>
#include  <boost/date_time.hpp>
#ifndef FOODITEMTEMPLATE_H
#define FOODITEMTEMPLATE_H
class FoodItemTemplate
{
  private :
  std::string upc;
  std::string name;
  int shelfLife;
  long long popularity;
  int numOfLocations;
  //  bool usedUp = false;

  public:
  //Default for boost libraries
  FoodItemTemplate();
  FoodItemTemplate(std::string upc, int shelfLife, std::string name);
  std::string get_name();
  bool operator<( const FoodItemTemplate& other ) const;
  std::string get_upc() const;
  int get_shelfLife();
  long long get_popularity();
  int get_numOfLocations();
  void set_popularity(long long pop);
  void set_numOfLocations(int num, boost::gregorian::date & timeStamp);
};


#endif
