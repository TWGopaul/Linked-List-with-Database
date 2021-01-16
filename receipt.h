//Programmer: Travis Gopaul
//Date: 10/2/20
//receipt.h
//Header file for reciept functions

#ifndef RECEIPT_H
#define RECEIPT_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include "Link.h"

//funtion prototypes
double get_quantity(char);
double calc_subtotal_pre_tax(double, double);
double calc_subtotal_with_tax(double);
double calc_tax(char, double);
double calc_total(Node*);
void write_receipt_header(std::ostream &);
void write_receipt(std::ostream&, Node*);
void write_total(std::ostream&, double);

#endif
