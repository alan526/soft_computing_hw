#include "population.h"
#include <cmath>
#include <iostream>
#define PI 3.1415926
#define NEW_GENE 0.1

population::population() {

}

population::population(double new_x1, double new_x2, double new_x3) {
	this->x[0] = new_x1;
	this->x[1] = new_x2;
	this->x[2] = new_x3;
}

void population::init_value(double new_x1, double new_x2, double new_x3) {
	this->x[0] = new_x1;
	this->x[1] = new_x2;
	this->x[2] = new_x3;
}

double population::eval_fitness() {
	double fitness_value;
	double x_squre_sum = (pow(x[0], 2) + pow(x[1], 2) + pow(x[2], 2));
	double x_cos_sum = cos(2 * PI * x[0]) + cos(2 * PI * x[1]) + cos(2 * PI * x[2]);
	fitness_value = 20 + exp(1) - 20 * exp((-0.2) * sqrt(x_squre_sum / 3.0)) - exp(x_cos_sum / 3.0);
	return(fitness_value);
}

void population::display() {
	std::cout << "x1 => " << x[0] << ", x2 => " << x[1] << ", x3 => " << x[2] << ", fn => " << eval_fitness() << std::endl;
}

population population::crossover(population mom) {
	population newborn;
	double newX[3];
	double r1 = (rand() % 101) / 100.0;
	double r2 = (rand() % 101) / 100.0;
	double r3 = (rand() % 101) / 100.0;

	newX[0] = x[0] * r1 + mom.get_x1() * (1 - r1);
	newX[1] = x[1] * r2 + mom.get_x2() * (1 - r2);
	newX[2] = x[2] * r3 + mom.get_x3() * (1 - r3);

	newborn.init_value(newX[0], newX[1], newX[2]);
	return(newborn);
}

void population::swap(population& target) {
	double temp[3] = {x[0], x[1], x[2]};
	x[0] = target.get_x1();
	x[1] = target.get_x2();
	x[2] = target.get_x3();
	target.init_value(temp[0], temp[1], temp[2]);
}

void population::mutate(double new_x1, double new_x2, double new_x3) {
	x[0] = (1 - NEW_GENE) * x[0] + NEW_GENE * new_x1;
	x[1] = (1 - NEW_GENE) * x[1] + NEW_GENE * new_x2;
	x[2] = (1 - NEW_GENE) * x[2] + NEW_GENE * new_x3;
}