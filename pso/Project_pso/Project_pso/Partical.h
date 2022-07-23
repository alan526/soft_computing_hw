#ifndef _PARTICAL_H_
#define _PARTICAL_H_

class partical {
public:
	partical();
	partical(double new_x1, double new_x2, double new_x3);
	void init_value(double new_x1, double new_x2, double new_x3);
	double eval_fitness();
	void update_value(const double gbest[]);
	double get_pbest();
	double get_pbest_x1();
	double get_pbest_x2();
	double get_pbest_x3();
	double get_x1() { return(x[0]); }
	double get_x2() { return(x[1]); }
	double get_x3() { return(x[2]); }
	void display();

private:
	double x[3];
	double pbest_x[3];
	double pbest;
}; 
#endif