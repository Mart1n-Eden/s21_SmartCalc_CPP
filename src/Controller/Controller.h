#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Model/Economy.h"
#include "../Model/Model.h"

namespace s21 {

class Controller {
 public:
  Controller();
  Controller(s21::Model other_m, s21::Economy other_e);
  ~Controller() = default;
  void Validator(std::string str);
  void Parser();
  double Calculator(double x);
  std::tuple<double, double, double> Annuity(double sum, int term, double per);
  std::tuple<double, double, double, double> Differentiated(double sum,
                                                            int term,
                                                            double per);
  std::tuple<double, double, double> Deposit(double sum, int term, double per,
                                             double nalog_per, int term_payment,
                                             int kapital, int list_add,
                                             double add, int list_take,
                                             double take);

 private:
  s21::Model model;
  s21::Economy economy;
};

}  // namespace s21

#endif  // CONTROLLER_H