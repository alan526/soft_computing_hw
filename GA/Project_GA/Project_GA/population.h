#ifndef _POPULATION_H_
#define _POPULATION_H_

class population {
public:
	population();
	population(double new_x1, double new_x2, double new_x3);
	void init_value(double new_x1, double new_x2, double new_x3);
	double eval_fitness();
	double get_x1() { return(x[0]); }
	double get_x2() { return(x[1]); }
	double get_x3() { return(x[2]); }
	void display();
	population crossover(population mom);
	void swap(population& target);
	void mutate(double new_x1, double new_x2, double new_x3);

private:
	double x[3];
};

#endif

