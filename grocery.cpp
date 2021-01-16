/*
 * Author: Travis Gopaul
 * Date: 9/17/20
 * Name: grocery.cpp
 * Purpose: Program to read a database of grocery items, take user input for items purchased and write
 *          a reciept to a text file.
 */

#include "Link.h"
#include "receipt.h"

using namespace std;

int main()
{
	//initial node pointer to list address
	Node *list = NULL;
	
	//variables to read data from file, collect  user input, and calculate prices
	int itemNum, userInput_item, userInput_weight;
	char itemName[40];
	char menu_selection, taxable, sellType;
	double unitPrice, total, subtotal, tax, quantity;

	//file input stream
	ifstream readFile;
	readFile.open("item.txt", ios::in);
	
	//check if data file is available
	if(!readFile)
	{
		cerr <<  "Error reading file." << endl;
		exit(1);
	}

	//file output stream
	ofstream writeFile;
	writeFile.open("Gopaul_Travis.txt", ios::out);

	do
	{
	
        //text for user interface
	cout << "Grocery System Menu " << endl;
        cout << setfill('-') << setw(20) << '-' <<  endl;
        cout << "1. Insert new item."  << endl;
	cout << "2. Print current items." << endl;
	cout << "3. Delete item from list." << endl;
        cout << "4. Print receipt and exit." << endl;
	cout << setfill(' ');

	//get menu selection from user
	cin >> menu_selection;

	 //asks user to make valid selection if invalid input
	 while (menu_selection < '1' &&  menu_selection >  '4')
	 {
	 	cout << "Please make valid selection." << endl;
		cin >> menu_selection;
	 }//end while

	//if user enters 1
	if(menu_selection == '1')
	{
		system("clear");
		cout << "Enter item number: ";
		//get item #
		cin >> userInput_item;

		//checks if item is not found
		do
	       	{
			readFile >> itemNum >> itemName >> taxable >> sellType >> unitPrice;
			if(readFile.eof())
			{
				cout << "Item number not found. Please try again." << endl;
			}//end if
		}//end do	
		//while the end of file hasn't been reached, the item# doesn't match user input
		while (!(readFile.eof()) && (itemNum != userInput_item));

		//clear and reset stream
		readFile.clear();
                readFile.seekg(0);

		//while loop if item # found
		while (readFile >> itemNum >> itemName >> taxable >> sellType >> unitPrice)
		{
			//if item # found, obtain data to pass into Node with functions in receiptFun.cpp
		 	if (itemNum == userInput_item)
		 	{
				//calls calc_sale function to determine subtotal 
				quantity = get_quantity(sellType);
				//calculate subtotal
				subtotal = calc_subtotal_pre_tax(quantity, unitPrice);
				//calls calc_tax function
				tax = calc_tax(taxable, subtotal);
				//calls subtotal_with_tax function
				subtotal = calc_subtotal_with_tax(subtotal);
				//write data to a node and add to receipt list using insertNode from LinkFun.cpp
				list = insertNode(list, itemNum, itemName, quantity, unitPrice, tax, subtotal);
			 } // end if
		} // end while

		//clear and reset stream
		readFile.clear();
                readFile.seekg(0);		
	} //end if input = 1

	//print list if selection = 2
	if (menu_selection == '2')
	{
		//print function in LinkFun.cpp
		printList(list);
	}//end if input = 2

	//delete item if selection = 3
	if(menu_selection == '3')
	{
		system("clear");
		
		//if list is empty display message
		if(list == NULL)
		{
			cout << "List is empty" << endl;
		}//end if
		else{
		int deleteItem;
		cout << "Enter item number to delete" << endl;
		cin >> deleteItem;
		//call deleteNode function in LinkFun.cpp
		list = deleteNode(list, deleteItem);
		}//end else
	}//end if input = 3

	}//end while (menu loop exits when input = 4)
        while(menu_selection != '4');	

	//calculate total from receiptFun.cpp
	total = calc_total(list);

	//write functions from receiptFun.cpp
	//write receipt header
        write_receipt_header(writeFile);	
	//write list to receipt file
	write_receipt(writeFile, list);
	//writes final total line on receipt
	write_total(writeFile, total);

	//close read and write files
	readFile.close();
	writeFile.close();
	return 0;
}//end main



