/*
main.cpp

An example implementation of transportSimplex.h. 

Last edit April 25 2015

Copyright (C) 2006, 2015
Darren T. MacDonald
darrentmacdonald@gmail.com

This program demonstrates the use of transportSimplex.h by solving an operations 
research problem. Suppose there are four factories manufacturing goods which
much be transported to five warehouses in different locations. 
The factories and their current supply of goods are as follows:
Fredericton, 18
Halifax, 18
Charlottown, 8
St. John's, 16

The warehouses and their demands are as follows:
Dartmouth, 9
Nackawic, 11
Summerside, 4
Corner Brook, 10
Sydney, 6

Unit costs for transporting goods are computed by Dist. The function transportSimplex finds the 
most efficient allocation of goods. 
*/

#include "transportSimplex.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

using namespace t_simplex;
using namespace std;


double Dist(string * facPtr,string * warPtr) {
	//Formula for approximating the distance between a factory and a warehouse;
	return abs((*facPtr).at(0) - (*warPtr).at(0)) + abs((*facPtr).at(1) - (*warPtr).at(1)) +
		abs((*facPtr).at(2) - (*warPtr).at(2));
};

int main(int argc, char** argv) {
	string factories[4];
	factories[0] = "Fredericton";
	factories[1] = "Halifax";
	factories[2] = "Charlottown";
	factories[3] = "St. John's";
		
	double supply[] = {18, 18, 8, 16};

	string warehouses[5];
	warehouses[0] = "Dartmouth";
	warehouses[1] = "Nackawic";
	warehouses[2] = "Summerside";
	warehouses[3] = "Corner Brook";
	warehouses[4] = "Sydney";
		
	double demand[] = {9, 11, 4, 10, 6};
	
	cout << "Costs:" << endl;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 5; j++)
			cout << factories[i] << " to " << warehouses[j] << " : " << Dist(&factories[i], &warehouses[j]) << endl;

	TsSignature<string> srcSig(4, factories, supply);
	TsSignature<string> snkSig(5, warehouses, demand);

	TsFlow flow[8];
	int flowVars = 0;

	double result = transportSimplex(&srcSig, &snkSig, Dist, flow, &flowVars);
	
	cout << "Total cost: " << result << endl;
	cout << "Flows:" << endl;

	for (int i = 0; i < flowVars; i++) 
		cout << factories[flow[i].from] << " to " << warehouses[flow[i].to] << " : " << flow[i].amount << endl;
	
}

