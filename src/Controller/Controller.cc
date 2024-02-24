#include "Controller.h"

namespace s21 {

Controller::Controller(s21::Model other_m, s21::Economy other_e)
    : model(other_m), economy(other_e) {}
void Controller::Validator(std::string str) { model.Validate(str); }

void Controller::Parser() { model.Parser(); }

double Controller::Calculator(double x) { return model.Calculator(x); }

std::tuple<double, double, double> Controller::Annuity(double sum, int term,
                                                       double per) {
  return economy.Annuity(sum, term, per);
}

std::tuple<double, double, double, double> Controller::Differentiated(
    double sum, int term, double per) {
  return economy.Differentiated(sum, term, per);
}
std::tuple<double, double, double> Controller::Deposit(
    double sum, int term, double per, double nalog_per, int term_payment,
    int kapital, int list_add, double add, int list_take, double take) {
  return economy.Deposit(sum, term, per, nalog_per, term_payment, kapital,
                         list_add, add, list_take, take);
}

}  // namespace s21
