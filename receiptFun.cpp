//Programmer: Travis Gopaul
//Date: 10/2/20
//receiptFun.cpp
//Function definitions for receipt.h header file

#include "receipt.h"
#include "Link.h"

using namespace std;

//function accepts char selltype and returns quantity of item sold
double get_quantity(char sellType)
{
	double quantity;

	if (sellType == 'p')
	{
		cout << "Enter weight in pounds: " << endl;
		cin >> quantity;
	}//end if
	if (sellType == 'n')
	{
		cout << "Enter quantity: " << endl;
		cin >> quantity;
	}//end if
	if (sellType == 's')
	{
		quantity = 1;
	}//end if
	return quantity;

}

//returns subtotal before tax
double calc_subtotal_pre_tax(double quantity, double unitPrice)
{
	double subtotal_pre_tax = quantity * unitPrice;
	return subtotal_pre_tax;
}

//function calculates subtotal with tax included
double calc_subtotal_with_tax(double subtotal)
{
	double sub_with_tax = subtotal * 1.06;
	return sub_with_tax;
}

//function accepts subtotal and calculates tax only called if taxable == 't'
double calc_tax(char taxable, double subtotal)
{
	double tax = 0.0;

	if(taxable == 't')
	{
	//calculate tax
	tax = subtotal * .06;
	}
	return tax;
}

//function to calculate total accepts each total
double calc_total(Node *list)
{
	//temp node to traverse list
	Node *temp = list;
	//variable for total
	static double total = 0.0;
	
	//if list is empty total = 0.0
	if(list == NULL)
	{
		total = 0.0;
	}
	//if list has only 1 element
	else if(list->next == NULL)
	{
		total = list->subtotal;
	}
	else{
	//while loop iterates through the list and adds subtotals
		while(temp->next != NULL)
        	{
        	        total += temp->subtotal;
        	        temp = temp->next;
        	}//end while
		//get last elements' subtotal
		total += temp->subtotal;
	}//end else
	return total;
}

//write header of receipt file
void write_receipt_header(ostream& writeFile)
{
        //receipt headers
        writeFile << setw(14) << left << "Item number" << setw(30) << left <<  "Item Name" <<
               setw(8) << left << "Unit" << setw(14) << left << "Unit Price" <<
               setw(7) << left << "Tax" << setw(12) << left <<  "Subtotal" << endl;

        writeFile << setfill('-') << setw(12) << right << " "  << setfill('-') <<  setw(30) << left <<
                "  " << setfill('-') << setw(8) << left << "  " <<  setfill('-') <<  setw(13) << left <<
                "  " << setfill('-') << setw(7) << left << "  " << setfill('-') << setw(12) << left <<
                "  " << endl;
        writeFile << setfill(' ');
};

//write data to reciept file
void write_receipt(ostream& writeFile, Node *list)
{
	//temp Node to traverse list
	Node *temp = list;

	//while end of list has not been reached, print node data
	while(list != NULL)
	{
        	writeFile <<  setw(14) << left << temp->itemNum << setw(30) << left << temp->itemName << setw(8) << left <<
		temp->unit << setw(14) << left << temp->unitPrice << setw(7) << left  << fixed <<  setprecision(2) <<
		temp->tax  << setw(12) << left << fixed << setprecision(2) << temp->subtotal <<  setw(20) << left  <<  endl;
	
	//exit at end of list
		if(temp->next == NULL)
		{
			break;
		}//end if

	//move to next node
	temp = temp->next;
	}//end while
}//end function

//write total line at the end of the reciept
void write_total(ostream& writeFile, double total)
{
	 writeFile << setw(14) << left << "Total" << setw(64) << right << fixed <<  setprecision(2) << total << endl;
}
