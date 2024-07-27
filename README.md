# ESAnnealing

## Usage
構造体に状態変数及び評価関数`double eval()`と遷移`void modify()`を実装し、`ESAnnealing<class>`で宣言した後`ESAnnealing.annealing()`で焼きなましを行う。

## Example
from /example.cpp  
関数 $ f(x) = -x^4 + x^3 + x^2 + x$の最大値を焼きなまし法で求める
```cpp
#include "esannealing.hpp"

struct State{ // 状態を表す構造体
  double x;

  // f(x) = -x^4 + x^3 + x^2 + x
  // max f(x): 2.33.... (x = 1.28...)
  double eval(){ // 評価関数
    return -pow(x,4)+pow(x,3)+pow(x,2)+x;
  }
  void modify(){ // 遷移
    x += ((double)rand() / (RAND_MAX))-0.5;
  }
};

int main(){
  ESAnnealing<State> sa;
  // sa内のStateの初期設定をする
  sa.state.x=0;

  // (epoch当たりの試行回数, 初期温度, 目標温度, 冷却係数)
  sa.annealing(100,100000,0.1,0.99);

  // 結果はクラス内のstateで参照できる
  std::cout << "Solution: " << "f(x) = " << sa.state.eval() << ", x = " << sa.state.x << std::endl;
}
```