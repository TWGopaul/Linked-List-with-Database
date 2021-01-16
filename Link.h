//Programmer: Travis Gopaul
//9/24/20
//Link.h
//Header file for struct and function declarations

#ifndef LINK_H
#define LINK_H

//Node struct
struct Node
{
	int itemNum;
	char itemName[40];
	double unit; //for pound or number of unit
	double unitPrice;
	double tax;
	double subtotal;
	Node *next;
};

//functions
Node *createNode(int, char*, double, double, double, double);
Node *insertNode(Node *,int, char*, double, double, double, double);
Node *searchNode(Node*, int);
Node *deleteNode(Node*, int);
void printList (Node *);

#endif
