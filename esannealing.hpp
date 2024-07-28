//                                            __ __              //
// .-----.-----.---.-.-----.-----.-----.---.-|  |__.-----.-----. //
// |  -__|__ --|  _  |     |     |  -__|  _  |  |  |     |  _  | //
// |_____|_____|___._|__|__|__|__|_____|___._|__|__|__|__|___  | //
//                                                       |_____| //
#pragma once
#include <cmath>
#include <iomanip>
#include <iostream>
#include <set>
#include <tuple>
#include <random>
#include <cassert>

template <class T>
class ESAnnealing
{
public:
  T state;

  void annealing(double epoch, double temperature, double temperature_target, double coolingcoef, unsigned int seed = 42, bool verbose = true)
  {
    assert(0 <= coolingcoef and coolingcoef < 1);
    assert(temperature >= temperature_target);
    srand(seed);
    double initscore = state.eval();
    double beststate_score = initscore;
    T beststate = state;
    int estimeted_epoch = std::ceil((std::log(temperature_target) - std::log(temperature)) / std::log(coolingcoef));
    if (verbose)
      std::cout << std::fixed << std::setprecision(6)
                << "ESAnnealing started with:" << "\n"
                << "| epoch       " << epoch << "\n"
                << "| temperature " << temperature << "\n"
                << "| target temp " << temperature_target << "\n"
                << "| coolingcoef " << coolingcoef << "\n"
                << "| seed        " << seed << "\n"
                << "| est epoch   " << estimeted_epoch << "\n"
                << std::flush;
    int cnt = 0;
    while (temperature > temperature_target)
    {
      for (int i = 0; i < epoch; i++)
      {
        T newstate = state;
        newstate.modify();
        double statescore = state.eval();
        double newstatescore = newstate.eval();
        double delta = newstatescore - statescore;

        if (0 < delta)
        {
          state = newstate;
        }
        else if (frand() > std::exp(delta / temperature))
        {
          state = newstate;
        }

        if (beststate_score < newstatescore)
        {
          beststate_score = newstatescore;
          beststate = newstate;
        }
      }
      temperature *= coolingcoef;

      if (verbose)
        std::cout << cnt << "/" << estimeted_epoch - 1 << " temp: " << temperature << " eval: " << beststate_score << std::endl;

      cnt++;
    }
    state = beststate;
    if (verbose)
      std::cout << "annealed: " << initscore << "->" << beststate_score << std::endl;
  }

private:
  double frand()
  {
    return ((double)rand() / (RAND_MAX));
  }
};