#include"Warehouse.h" 
using namespace std;

Warehouse::Warehouse (string name)
{
  this->name = name;
}

Warehouse::Warehouse()
{
  this->name = "default";
}

Warehouse::~Warehouse()
{
}

string Warehouse::get_name()const
{
  return name;
}

bool Warehouse::operator<( const Warehouse& other ) const
{
  return (name < other.get_name());
}

void Warehouse::updatePending(string upc, long long qty)
{
  pending[upc] += qty;
}

//Need to pass datastructure multimap we're bulding on WarehouseManager
void Warehouse::processStock(std::map<string, FoodItemTemplate> & stock, map<boost::gregorian::date, std::set<string> > & underfilled, boost::gregorian::date & timeStamp)
{
 
  string upc;
  int shelfLife;
  long long oldQty;
  long long newQty;
  set<string> underfilledToday = underfilled[timeStamp]; 
  vector<FoodItem> vecTor;
  FoodItemTemplate current;
  boost::gregorian::date expiration;

  for(std::map<string, long long>::iterator it = pending.begin(); it != pending.end(); ++it)
    {
      int elementsToDelete = 0;
      upc = it->first;
      current = stock[upc];
      vecTor = inventory[upc];
      //Keeping track of well stocked 
      if(totalStock[upc] == 0 && pending[upc] > 0)
      	{
	  //Do stuff
	  stock[upc].set_numOfLocations(1, timeStamp);
      	}
      else if(totalStock[upc] > 0 && pending[upc] + totalStock[upc] <= 0)
	{
	  stock[upc].set_numOfLocations(-1, timeStamp);
	}
      if(pending[upc] + totalStock[upc] >= 0)
	{
	  totalStock[upc] += pending[upc];
	}
      else
	{
	  totalStock[upc] = 0;
	}
      if(pending[upc] > 0)
	{
	  //derefernce from template the qty
	  shelfLife = stock[upc].get_shelfLife();
	  boost::gregorian::date_duration dd(shelfLife);
	  expiration = timeStamp + dd;
	  FoodItem temp(upc, expiration, pending[upc]);
	  vecTor.push_back(temp);
	}
      else if (pending[upc] < 0)
	{
	  int i;
	  for( i = 0; i < vecTor.size(); i++)
	    {
	      //if pending qty + elements qty < 0 move to next
	      if(pending[upc] + vecTor[i].get_quantity() <= 0)
		{
		  //If we use up all the elements with a given expiration, then we need
		  //to update the amount of items we still need, and make a flag to delete
		  //this element
		  pending[upc] += vecTor[i].get_quantity();
		  elementsToDelete = i+1;
		} 
	      else 
		{
		  //If we use up some of the items for a given expiration date but not
		  //all, update the number of elements in that specific "bin"
		  vecTor[i].set_quantity(pending[upc] + vecTor[i].get_quantity());
		  pending[upc] = 0;
		}
	    }
	    if(pending[upc] < 0)
	      {
		//TAKE THESE oFF
		underfilledToday.insert(upc);
		//cout<<"ABCDEFGHIJKLMNOPItem: "<<" Warehouse:"<<this->name<<"DATE:"<<timeStamp<<endl;
	      }
	    //cout<<"El to del: "<<elementsToDelete<<endl;
	    // if(!(elementsToDelete > vecTor.size()))
	      vecTor.erase(vecTor.begin(), vecTor.begin() + elementsToDelete);

	}
      //Put vector back in pending
      //Insert underfilledToday in Underfilled data structure
	    inventory[upc] = vecTor; 
	    underfilled[timeStamp] = underfilledToday;
      }
  pending.clear();  
}
void Warehouse::processExpiration(boost::gregorian::date & timeStamp,map<std::string,FoodItemTemplate> * stock )
{
  //currentDay++;
  //int counter = 0;
  vector<FoodItem> vecTor;
  for(std::map<string, vector<FoodItem> >::iterator it = inventory.begin(); it != inventory.end(); ++it)  
    {
      vecTor = it->second;
      if(!vecTor.empty())
	{
      if(vecTor[0].get_expiration() == timeStamp)
	{
	  vecTor.erase(vecTor.begin());
	  if(vecTor.empty())
	    {
	      stock->at(it->first).set_numOfLocations(-1, timeStamp);
	      totalStock[it->first] -= vecTor.front().get_quantity();
	    }
	}
	}
      inventory[it->first] = vecTor;
    }
}


