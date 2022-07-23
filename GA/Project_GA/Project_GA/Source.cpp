#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include "population.h"
#define FUNC_MAX 23
#define MUTATION_RATE 20

using namespace std;

double get_random_x();
int r_w_selection(int roulette[], int max, int p_size);
int get_select_value(population* p, int* roulette, int p_size);
void mating(int cross_num, int p_size, population* X);
void select_next_generation(population* X, population* newborn, int p_size, int cross_num);
void mutation(population* newborn, int cross_num);
void find_gbest(population* p, double gbest[4], int p_size);
void global_display(const double gbest[]);
void iter_record(population* X, const double gbest[], int iter, int size);

int main(void) {
	int population_size = 30;
	int iteration = 50;
	population* X = new population[population_size];
	double gbest[4] = { 0, 0, 0, 10000 };
	srand(time(NULL));

	int crossover_num = 30;
	

	for (int i = 0; i < population_size; i++) {
		X[i].init_value(get_random_x(), get_random_x(), get_random_x());
		//X[i].display();
	}
	
	for (int i = 0; i < iteration; i++) {
		cout << "-----------------" << i << "-----------------" << endl;
		mating(crossover_num, population_size, X);
		find_gbest(X, gbest, population_size);
		iter_record(X, gbest, i, population_size);
		global_display(gbest);
	}
	delete[] X;
	system("pause");
	return(0);
}

double get_random_x() {
	return (rand() % 6401) / 100.0 - 32;
}

int r_w_selection(int roulette[], int max, int p_size) {
	int select_num, temp;
	temp = rand() % max;
	for (int i = 0; i < p_size; i++) {
		if (temp <= roulette[i]) {
			select_num = i;
			break;
		}
	}
	return(select_num);
}

int get_select_value(population* p, int* roulette, int p_size) {
	int temp = 0;
	for (int i = 0; i < p_size; i++) {
		roulette[i] = 0;
		temp += round(FUNC_MAX - p[i].eval_fitness());
		roulette[i] = temp;
	}
	return(temp);
}

void mating(int cross_num, int p_size, population* X) {
	int* roulette = new int[p_size];
	int* dad_list = new int[cross_num];
	int* mom_list = new int[cross_num];
	population* newborn = new population[cross_num];
	int roulette_max = get_select_value(X, roulette, p_size);
	/*mating*/
	for (int i = 0; i < cross_num; i++) {
		dad_list[i] = r_w_selection(roulette, roulette_max, p_size);
		do {
			mom_list[i] = r_w_selection(roulette, roulette_max, p_size);
			
		} while (dad_list == mom_list);
		newborn[i] = X[dad_list[i]].crossover(X[mom_list[i]]);
	}
	mutation(newborn, cross_num);
	select_next_generation(X, newborn, p_size, cross_num);
	delete[] roulette;
	delete[] dad_list;
	delete[] mom_list;
	delete[] newborn;
}

void select_next_generation(population* X, population* newborn, int p_size, int cross_num) {
	population* temp = new population[p_size + cross_num];
	for (int i = 0; i < p_size; i++) {
		temp[i].init_value(X[i].get_x1(), X[i].get_x2(), X[i].get_x3());
	}
	for (int i = 0; i < cross_num; i++) {
		temp[i + p_size].init_value(newborn[i].get_x1(), newborn[i].get_x2(), newborn[i].get_x3());
	}

	for (int i = 0; i < p_size + cross_num; i++) {
		for (int j = 0; j < p_size + cross_num - i - 1; j++) {
			if (temp[j].eval_fitness() > temp[j + 1].eval_fitness()) {
				temp[j].swap(temp[j + 1]);
			}
		}
	}

	for (int i = 0; i < p_size; i++) {
		X[i].swap(temp[i]);
	}
	delete[] temp;
}

void mutation(population* newborn, int cross_num) {
	for (int i = 0; i < cross_num; i++) {
		int dice = rand() % 100;
		if (dice < MUTATION_RATE) {
			newborn[i].mutate(get_random_x(), get_random_x(), get_random_x());
		}
	}
}

void find_gbest(population* p, double gbest[4], int p_size) {
	for (int i = 0; i < p_size; i++) {
		if (p[i].eval_fitness() < gbest[3]) {
			gbest[0] = p[i].get_x1();
			gbest[1] = p[i].get_x2();
			gbest[2] = p[i].get_x3();
			gbest[3] = p[i].eval_fitness();
		}
	}
}

void global_display(const double gbest[]) {
	cout << "The best value => " << gbest[3] << endl;
	cout << "X1 => " << gbest[0] << ", X2 = > " << gbest[1] << ", X3 => " << gbest[2] << endl;
}

void iter_record(population* X, const double gbest[], int iter, int size) {
	ofstream wf;
	string fn = "../../../drawplot/GA_record/iter" + to_string(iter) + ".csv";
	wf.open(fn, 'w');
	//wf << "This is iter " << iter << " record\n";
	wf << "X1,X2,X3,fitness_value\n";
	for (int i = 0; i < size; i++) {
		wf << X[i].get_x1() << "," << X[i].get_x2() << "," << X[i].get_x3() << "," << X[i].eval_fitness() << "\n";
	}
	wf << "gbest_X1,gbest_X2,gbest_X3,gbest\n";
	wf << gbest[0] << "," << gbest[1] << "," << gbest[2] << "," << gbest[3] << "\n";
	wf.close();
}