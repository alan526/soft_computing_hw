#include "Partical.h"
#include <iostream>
#include <cmath>
#define PI 3.1415926
#define C1 2.0
#define C2 2.0
#define IW 0.8

partical::partical() {
	
}

partical::partical(double new_x1, double new_x2, double new_x3) {
	this->x[0] = new_x1;
	this->x[1] = new_x2;
	this->x[2] = new_x3;
}

void partical::init_value(double new_x1, double new_x2, double new_x3) {
	this->x[0] = new_x1;
	this->x[1] = new_x2;
	this->x[2] = new_x3;
	this->pbest_x[0] = new_x1;
	this->pbest_x[1] = new_x2;
	this->pbest_x[2] = new_x3;
	this->pbest = eval_fitness();
}

double partical::eval_fitness() {
	double fitness_value;
	double x_squre_sum = (pow(x[0], 2) + pow(x[1], 2) + pow(x[2], 2));
	double x_cos_sum = cos(2 * PI * x[0]) + cos(2 * PI * x[1]) + cos(2 * PI * x[2]);
	fitness_value = 20 + exp(1) - 20 * exp((-0.2) * sqrt(x_squre_sum / 3.0)) - exp(x_cos_sum / 3.0);
	return(fitness_value);
}

void partical::update_value(const double gbest[]) {
	double velocity[3];
	double r1 = (rand() % 101) / 100.0;
	double r2 = (rand() % 101) / 100.0;

	for (int i = 0; i < 3; i++) {
		velocity[i] = C1 * r1 * (pbest_x[i] - x[i]) + C2 * r2 * (gbest[i] - x[i]);
		x[i] = IW * x[i] + velocity[i];
		if (x[i] >= 32 || x[i] <= -32) {
			x[i] = (rand() % 6401) / 100.0 - 32;
		}
	}
	if (eval_fitness() < pbest) {
		for (int j = 0; j < 3; j++) {
			pbest_x[j] = x[j];
		}
		pbest = eval_fitness();
	}
	
}

double partical::get_pbest() {
	return(pbest);
}

double partical::get_pbest_x1() {
	return(pbest_x[0]);
}

double partical::get_pbest_x2() {
	return(pbest_x[1]);
}

double partical::get_pbest_x3() {
	return(pbest_x[2]);
}

void partical::display() {
	std::cout << "x1 => " << x[0] << ", x2 => " << x[1] << ", x3 => " << x[2] << ", fn => " << eval_fitness() << std::endl;
}