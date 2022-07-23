#include <cstdio>
#include <cstdlib>
#include "Partical.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

double get_random_x();
void find_gbest(partical X[], double gbest[4], int p_size);
void global_display(const double gbest[]);
void iter_record(partical X[], const double gbest[], int iter, int size);

int main(void) {
	
	int population_size = 30;
	int iteration = 50;
	partical* X = new partical[population_size];
	double gbest[4] = {0, 0, 0, 10000};
	srand(time(NULL));

	for (int i = 0; i < population_size; i++) {
		X[i].init_value(get_random_x(), get_random_x(), get_random_x());
		X[i].display();
	}
	find_gbest(X, gbest, population_size);
	//global_display(gbest);

	for (int i = 0; i < iteration; i++) {
		cout << "-----------------" << i << "-----------------" << endl;
		for (int j = 0; j < population_size; j++) {
			X[j].update_value(gbest);
			//X[j].display();
		}
		find_gbest(X, gbest, population_size);
		iter_record(X, gbest, i, population_size);
		global_display(gbest);
	}
	system("pause");
	return(0);
}

double get_random_x() {
	return (rand() % 6401) / 100.0 - 32;
}

void find_gbest(partical X[], double gbest[4], int p_size) {
	for (int i = 0; i < p_size; i++) {
		if (X[i].get_pbest() < gbest[3]) {
			gbest[0] = X[i].get_pbest_x1();
			gbest[1] = X[i].get_pbest_x2();
			gbest[2] = X[i].get_pbest_x3();
			gbest[3] = X[i].get_pbest();
		}
	}
}

void global_display(const double gbest[]) {
	cout << "The best value => " << gbest[3] << endl;
	cout << "X1 => " << gbest[0] << ", X2 = > " << gbest[1] << ", X3 => " << gbest[2] << endl;
}

void iter_record(partical X[], const double gbest[], int iter, int size) {
	ofstream wf;
	string fn = "../../../drawplot/PSO_record/iter" + to_string(iter) + ".csv";
	wf.open(fn, 'w');
	//wf << "This is iter " << iter << " record\n";
	wf << "X1,X2,X3,fitness_val\n";
	for (int i = 0; i < size; i++) {
		wf << X[i].get_x1() << "," << X[i].get_x2() << "," << X[i].get_x3() << "," << X[i].eval_fitness() << "\n";
	}
	wf << "gbest_X1,gbest_X2,gbest_X3,gbest\n";
	wf << gbest[0] << "," << gbest[1] << "," << gbest[2] << "," << gbest[3] << "\n";
	wf.close();
}