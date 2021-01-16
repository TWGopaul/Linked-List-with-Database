//Programmer: Travis Gopaul
//9/24/20
//LinkFun.cpp
//Member definitions for Link.h


#include <iostream>
#include <iomanip>
#include  "Link.h"

using namespace std;

//creates new node
Node *createNode(int itemNum, char *name, double quantity, double unitPrice, double tax, double subtotal)
{
	//create a new node called newptr
	Node *newptr = new Node;
	//set itemNum
	newptr->itemNum = itemNum;
	//set itemName; uses for loop to copy char array
	for(int i = 0; i < 40; i++)
	{
		newptr->itemName[i] = name[i];
	}
	//set quantity
	newptr->unit = quantity;
	//set unit price
	newptr->unitPrice = unitPrice;
	//set tax
	newptr->tax = tax;
	//set subtotal
	newptr->subtotal = subtotal;
	//set the new node's next pointer to NULL
	newptr->next = NULL;

	//returns the new node
	return newptr;
}//end create function

//insert node function
Node *insertNode(Node *list, int itemNum, char name[], double quantity, double unitPrice, double tax, double subtotal)
{	
	//call createNode function to create new node to insert
	Node *newNode = createNode(itemNum, name, quantity, unitPrice, tax, subtotal);
	//temporary pointer intialized to first position in list
	Node *temp = list;
	
	//determines if id number ALREADY EXISTS
	while(list != NULL)
	{
		//if current position itemNumber == newNode itemNumber, add quantity together
		if(temp->itemNum == newNode->itemNum)
		{
			cout << "***Item added to existing quantity.***" << endl << endl;
			//add to quantity
			temp->unit += newNode->unit;
			//if taxable, expression calculates new tax
			//if not taxable, (temp->tax/temp->unitPrice) = 0 so tax remains 0.00
			temp->tax = (temp->tax/temp->unitPrice) * (temp->unitPrice * temp->unit);
			//recalculate subtotal
			temp->subtotal = (temp->unit * temp->unitPrice) + temp->tax;	
		}
		if(temp->next == NULL)
                	break;
		//move current position to next node
                temp = temp->next;	
	}//end while loop

	//inserts newNode in BEGINNING if list is empty (NULL)
        if(list == NULL)
	{
                //list is assigned the data in newNode
                list = newNode;
        }//end if

	//insert beginning as smallest id
        if (list->itemNum > newNode->itemNum)
        {
		//newNode's next pointer assigned to list's address
		newNode->next = list;
		//list is assigned the data in newNode
		list = newNode;
	}//end if
	//if there is only 1 element in list, and the newNode is larger than it
	else if((list->itemNum < newNode->itemNum) && (list->next == NULL))
	{
		//insert newNode in the end of a list with 1 node
		list->next = newNode;
	}//end else if

	//reset temp
        temp = list;

	//while not at the end of list
	while (temp->next != NULL)
	{
		//insert between
		if((temp->itemNum < newNode->itemNum) && (temp->next->itemNum > newNode->itemNum))
   		{
			//set newNode's next pointer to the next node in the list
			newNode->next = temp->next;
			//set the next pointer at the current position to the newNode's location
			temp->next = newNode;
		}//end if

		//insert at the end
		if((temp->next->itemNum < newNode->itemNum) && (temp->next->next == NULL))
		{
			//set the pointer at current location to point to the new end node
			temp->next->next = newNode;
		}//end if

		//keep searching
                temp = temp->next;
	}//end while

	return list;
}//end insert function

/**SEARCH FUNCTION NOT NEEDED FOR THIS PROGRAM***
//search node function
Node *searchNode(Node* list, int itemNum)
{
	//temporary pointer intialized to first position in list
        Node *temp = list;

	//if list is EMPTY
	if(list == NULL)
	{
		cout << "List is empty." << endl;
		return list;
	}//end if

	//if node DOESN'T EXIST
        while((list != NULL) && (itemNum != temp->itemNum))
        {
                if(temp->next == NULL)
                {
                        cout << "Item not found." << endl;
                        return list;
                }//end if
                //keep searching list
                temp = temp->next;
        }//end while

	//returns node if FOUND
	while(list != NULL)
	{
		if(temp->itemNum == itemNum)
		{
			//print node info
			cout <<  setw(14) << left << temp->itemNum << setw(30) << left << temp->itemName << setw(8) << left <<
			temp->unit << setw(14) << left << temp->unitPrice << setw(7) << left  << fixed <<  setprecision(2) <<
			temp->tax  << setw(12) << left << fixed << setprecision(2) << temp->subtotal <<  setw(20) << left  <<  endl;

			return temp;
		}//end if
		//keep searching
		temp = temp->next;
	}//end while
}
*/

//delete node function
Node *deleteNode(Node  *list, int itemNum)
{
	//two temporary pointers needed to delete nodes
        Node *temp = list;
	Node *temp1;
	
	//if node DOESN'T EXIST
	while((temp->next != NULL) && (itemNum != temp->itemNum))
	{
		//keep searching list
                temp = temp->next;
	
		if((temp->next == NULL) && (itemNum != temp->itemNum))
		{
			cout << "Item not found." << endl;
		}//end if
	}//end while

	//reset temp variable
	temp = list;

	//if only 1 node and does not match
	if((list->next == NULL) && (list->itemNum != itemNum))
	{
		cout << "Item not found" << endl;
	}//end if
	
	//delete if  ONLY NODE IN LIST
	if((list->next == NULL) && (list->itemNum == itemNum))
	{
		//placehold list address
		temp = list;
		//reassign list to NULL
		list = NULL;
		//delete the place holder
		delete temp;
	}//end if

	//checks for correct node in a list of size  > 1 
	while (temp->next != NULL)
	{
     		//delete BEGINNING of list with more than one element
        	if((itemNum == list->itemNum) && (temp->next!=NULL))
        	{
                	//placehold list address
                	temp = list;
                	//reassign list to the next position
                	list = list->next;
                	//delete the place holder
                	delete temp;
        	}//end if

    		//delete BETWEEN if id # match and not at the end of list
                if((itemNum == temp->next->itemNum) && (temp->next->next != NULL))
		{
			//2nd temp ptr holds place of deleted node
                        temp1 = temp->next;
                        //set prior node to point to node after deleted node
                        temp->next = temp->next->next;
                        //delete place holder
                        delete temp1;
                }//end if

     		//delete END if id # match and at the end of the list
                if((itemNum == temp->next->itemNum) && (temp->next->next == NULL))
                {
                        //2nd temp ptr holds place of deleted node
                        temp1 = temp->next;
                        //set prior node to point to the end of the list
                        temp->next = NULL;
                        //delete place holder
                        delete temp1;
                       
                }//end if

		//keep searching if not at the end of the list
		if(temp->next != NULL)
		{
            		//keep searching list
               		temp = temp->next;
		}//end if
	}//end while

	return list;
}//end delete function

void printList(Node *list)
{
	//clear stream
	system("clear");

	//temp Node to traverse list
        Node *temp = list;
	
	//write receipt header
        cout << setw(14) << left << "Item number" << setw(30) << left <<  "Item Name" <<
               setw(8) << left << "Unit" << setw(14) << left << "Unit Price" <<
               setw(7) << left << "Tax" << setw(12) << left <<  "Subtotal" << endl;

        cout << setfill('-') << setw(12) << right << " "  << setfill('-') <<  setw(30) << left <<
                "  " << setfill('-') << setw(8) << left << "  " <<  setfill('-') <<  setw(13) << left <<
                "  " << setfill('-') << setw(7) << left << "  " << setfill('-') << setw(12) << left <<
                "  " << endl;
        cout << setfill(' ');
	
        //while list is not empty, print node data
        while(list!=NULL)
        {
        cout <<  setw(14) << left << temp->itemNum << setw(30) << left << temp->itemName << setw(8) << left <<
        temp->unit << setw(14) << left << temp->unitPrice << setw(7) << left  << fixed <<  setprecision(2) <<
        temp->tax  << setw(12) << left << fixed << setprecision(2) << temp->subtotal <<  setw(20) << left  <<  endl
	<< endl;

                //exit loop if end of list is reached
                if(temp->next == NULL)
                {
                        break;
                }//end if
                //move to next node
                temp = temp->next;
        }//end while

}//end print list
