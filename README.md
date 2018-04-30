/*Written by Salvador Gutierrez and Sara Chadwick 2018*/
This is an application written in C/C++ to process changes in the inventory kept in different Warehouses. It keeps track of:
[+] Underfilled orders (products that got more requests than could be filled)
[+] Well-Stocked Items (products that are currently stocked in more than 2 locations)
[+] Most Popular Items (Top 3 products with the most requests)

The format of the files to be analyzed must be in the format specified by the files under the 'TestFiles' folder. 

To compile make sure you have gnu or gcc and simiply type
make
an executable should be made, then simply feed it a file like so:
a.out nameOfFile.txt
