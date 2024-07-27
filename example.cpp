#include "esannealing.hpp"

struct State{
  double x;

  // f(x) = -x^4 + x^3 + x^2 + x
  // max f(x): 2.33.... (x = 1.28...)
  double eval(){
    return -pow(x,4)+pow(x,3)+pow(x,2)+x;
  }
  void modify(){
    x += ((double)rand() / (RAND_MAX))-0.5;
  }
};

int main(){
  ESAnnealing<State> sa;
  sa.state.x=0;

  sa.annealing(100,100000,0.1,0.99);

  std::cout << "Solution: " << "f(x) = " << sa.state.eval() << ", x = " << sa.state.x << std::endl;
}