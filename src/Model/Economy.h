#ifndef ECONOMY_H
#define ECONOMY_H

#include <cmath>
#include <tuple>

namespace s21 {

class Economy {
 public:
  Economy();
  std::tuple<double, double, double> Annuity(double sum, int term, double per);
  ~Economy() = default;
  std::tuple<double, double, double, double> Differentiated(double sum,
                                                            int term,
                                                            double per);
  std::tuple<double, double, double> Deposit(double sum, int term, double per,
                                             double nalog_per, int term_payment,
                                             int kapital, int list_add,
                                             double add, int list_take,
                                             double take);
};

}  // namespace s21

#endif  // ECONOMY_H