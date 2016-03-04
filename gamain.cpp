/*
	Physics 2G03 Final
	v. 0.6
	Written By: Robert Gorrie (ID#:1222547)
	November 28th, 2014
*/
#pragma warning(disable:4786)

#include "gamain.h"

#include <iostream>
#include <vector>
#include <time.h>				
#include <math.h>
#include <algorithm>

#define Q_MAX		0.7259f
#define Q_MIN		0.0f
#define P_MAX		8.0f
#define P_MIN		0.5f
#define ITER		5

using namespace std;

int pop = 20;
vector<entities> ents(pop); //vector of pop entities
float g = 9.0;
float m = 1; //mass of entities
float xstart = 0;
float ystart = 0;
float xgoal = 10;
float ygoal = 10;

float genRan(float a, float b){
	float random = ((float) rand()) / (float) RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

void initPop(){
	for (int i = 0; i < ents.size(); i++){
		ents[i].q =  genRan(Q_MIN,Q_MAX);
		ents[i].p1 = genRan(P_MIN,P_MAX);
		ents[i].p2 = genRan(P_MIN,P_MAX);
	}
}

void calcFitness(){
	float a = ygoal-ystart;
	float b = xgoal-xstart;
	float minD;
	float delta = 0;
	float alpha,phi,phiV,phiH;
	for (int i = 0; i < pop; i++){
		minD = 14;
		alpha = atan(a/b) + ents[i].q; //atan should always give correct sign because values we are dealing with will always be within 90 degrees (unless point B(x2,y2) is moved)
		phi = sqrt((a*ents[i].p1)*(a*ents[i].p1) + (b*ents[i].p2)*(b*ents[i].p2)) / 1000;
		phiV = phi * sin(alpha) + ents[i].p1/(ents[i].p2*2); /*+ ents[i].p1/(ents[i].p2*2)*/;
		phiH = phi * cos(alpha) + xgoal/(ents[i].p2*2);
		for (int t = 0; t < 40; t++){
			//update current location, change in locationv = phiV*t - 1/2g*t^2, change in locationh = locationh + phiH
			//delta = distance from goal to current location
			ents[i].y = phiV*(float)t - 1/2*g*(float)t*(float)t;
			ents[i].x = phiH*(float)t;
			delta = sqrt((ygoal-ents[i].y)*(ygoal-ents[i].y) + (xgoal-ents[i].x)*(xgoal-ents[i].x));
			if (delta < minD){minD=delta;}
		}
		if(minD==0.000){
			ents[i].fitness = 100;
		}else{
			ents[i].fitness = 1/minD;
		}
	}
}

bool sortents(entities a, entities b){ 
	return (a.fitness > b.fitness);
}

inline void sortFitness(){
	sort(ents.begin(), ents.end(), sortents); 
}

//-----------------genetic processes----------------
void selection(){
	entities s1 = ents[0];
	entities s2 = ents[1];
	entities s3 = ents[2];
	entities s4 = ents[3];
	entities s5 = ents[4];
	ents.clear();
	for (int i = 0; i < pop-5; i++){
		ents[i] = crossover(s1,s2,s3,s4,s5);
	}
	ents[pop-5] = s1;
	ents[pop-4] = s2;
	ents[pop-3] = s3;
	ents[pop-2] = s4;
	ents[pop-1] = s5;
}

entities crossover(entities s1, entities s2, entities s3, entities s4, entities s5){
	entities ent;
	int rq = rand() % 5 + 1;
	int rp1 = rand() % 5 + 1;
	int rp2 = rand() % 5 + 1;
	if(rq==1){ent.q = s1.q;}else if(rq==2){ent.q = s2.q;}else if(rq==3){ent.q = s3.q;}else if(rq==4){ent.q = s4.q;}else{ent.q = s5.q;}
	if(rp1==1){ent.p1=s1.p1;}else if(rp1==2){ent.p1=s2.p1;}else if(rp1==3){ent.p1=s3.p1;}else if(rp1==4){ent.p1=s4.p1;}else{ent.p1=s5.p1;}
	if(rp2==1){ent.p2=s1.p2;}else if(rp2==2){ent.p2=s2.p2;}else if(rp2==3){ent.p2=s3.p2;}else if(rp2==4){ent.p2=s4.p2;}else{ent.p2=s5.p2;}
	return ent;
}

void mutation(){
	int mEnt1 = rand() % pop;
	int mEnt2 = rand() % pop;
	int var1 = rand() % 3;
	int var2 = rand() % 3;
	if (var1==0){ents[mEnt1].q=genRan(Q_MIN,Q_MAX);}else if(var1==1){ents[mEnt1].p1=genRan(P_MIN,P_MAX);}else{ents[mEnt1].p2=genRan(P_MIN,P_MAX);}
	if (var2==0){ents[mEnt2].q=genRan(Q_MIN,Q_MAX);}else if(var2==1){ents[mEnt2].p1=genRan(P_MIN,P_MAX);}else{ents[mEnt2].p2=genRan(P_MIN,P_MAX);}
}
//---------------------------------------------------




int main(){
	srand(unsigned(time(NULL)));
	
	initPop();
	calcFitness();
	sortFitness();
	//cout << "highest fitness score is" << ents[0].fitness << "\n";

	for (int i=0; i<ITER; i++) {
		selection();
		mutation();
		calcFitness();
		sortFitness();
		cout << "highest fitness score is" << ents[0].fitness << "\n";
		for (int i = 0; i < pop; i++){
			//cout << "ent " << i << " has fitness rating " << ents[i].fitness << "\n";
		}cout << "\n";
	}
	cout << "q value of most successful ent: " << ents[0].q << ", p1 value: " << ents[0].p1 << ", p2 value: " << ents[0].p2 << ".\n";

	return (0); //return statement not required on all compilers
}


//
//entities class methods
entities::entities(){
	fitness = 0;
	angle = 0;
	force = 0;
	q = 0;
	p1 = 0;
	p2 = 0;
	x = 0;
	y = 0;
}
