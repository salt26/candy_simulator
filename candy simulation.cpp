#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;

int main() {
	srand(unsigned(NULL));
	int h, h2;
	double prior;		// hypo. prior
	int cherry_num = 0;
	int lime_num = 0;
	int pick[101];
	double dh[5][101];	// prob. of lime in hypo. (likelihood)
	double hd[5][101];	// (posterior) prob. of each hypothesis
	double temp;
	double dd[101];		// prob. that next candy is lime
	ofstream fout;
	char fname[11] = "candy .csv";
	cout<<"Input integer 'h'. 'h' is the hypothesis number. (1 <= h <= 5)"<<endl;
	while(true) {
		cin>>h;
		if (cin.fail() || h < 1 || h > 5) {
			cout<<"Retry."<<endl;
			cin.clear();
			cin.ignore(100, '\n');
		} else {
			break;
		}
	}
	fname[5] = (char)(h+'0');
	fout.open(fname);
	
	h2 = h;
	
	if (h == 1 || h == 5) {
		prior = 0.1;
	} else if (h == 2 || h == 4) {
		prior = 0.2;
	} else {
		prior = 0.4;
	}
	
	for (int i = 1; i <= 100; i++) {
		if (rand() % 4 >= h - 1) {
			pick[i] = 0;
			cherry_num++;
			cout<<"c ";
		} else {
			pick[i] = 1;
			lime_num++;
			cout<<"l ";
		}
	}
	cout<<endl<<"cherry: "<<cherry_num<<" / lime: "<<lime_num<<endl;
	
	for (h = 1; h <= 5; h++) {
		dh[h-1][0] = 1;
		for (int i = 1; i <= 100; i++) {
			if (pick[i] == 0)
				dh[h-1][i] = dh[h-1][i-1] * ((5 - h) / (double)4);
			else
				dh[h-1][i] = dh[h-1][i-1] * ((h - 1) / (double)4);
			cout<<"dh["<<h<<"]["<<i<<"]="<<dh[h-1][i]<<"\n";
			hd[h-1][i] = dh[h-1][i] * prior;
		}
		cout<<endl<<endl;
	}
	
	for (int i = 1; i <= 100; i++) {
		temp = 0;
		for (h = 1; h <= 5; h++) {
			temp += hd[h-1][i];
		}
		for (h = 1; h <= 5; h++) {
			hd[h-1][i] *= 1 / temp;
			cout<<"P(h"<<h<<"|d1,...,d"<<i<<")="<<hd[h-1][i]<<"  ";
			fout<<hd[h-1][i]<<",";
		}
		cout<<endl;
		for (h = 1; h <= 5; h++) {
			dd[i] += ((h - 1) / (double)4) * hd[h-1][i];
		}
		cout<<"P(D"<<i+1<<"=lime|d1,...,d"<<i<<")="<<dd[i]<<endl<<endl;
		fout<<dd[i]<<endl;
	}
	
	cout<<endl<<"Save data to \"candy"<<h2<<".csv\"."<<endl;
	fout.close();
	system("pause");
	return 0;
}
