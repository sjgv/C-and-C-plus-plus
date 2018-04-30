tester:	FoodItem.o Warehouse.o FoodItemTemplate.o WarehouseManager.o WarehouseApp.o
	g++ -o a.out FoodItem.o Warehouse.o FoodItemTemplate.o WarehouseManager.o WarehouseApp.o

FoodItem.o:	FoodItem.cpp FoodItem.h
	g++ -c FoodItem.cpp

Warehouse.o:	Warehouse.cpp Warehouse.h
	g++ -c Warehouse.cpp

FoodItemTemplate.o:	FoodItemTemplate.cpp FoodItemTemplate.h
	g++ -c FoodItemTemplate.cpp

WarehouseManager.o:	WarehouseManager.cpp WarehouseManager.h
	g++ -c WarehouseManager.cpp

WarehouseApp.o:	WarehouseApp.cpp 
	g++ -c WarehouseApp.cpp

clean:
	rm -f tester *.o
