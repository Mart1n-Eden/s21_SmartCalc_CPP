#include "Economy.h"

namespace s21 {

Economy::Economy() {}

std::tuple<double, double, double> Economy::Annuity(double sum, int term,
                                                    double per) {
  double month = 0, over = 0, total = 0;
  month = sum * ((per / 1200.0) / (1 - pow(1 + (per / 1200.0), -term)));
  total = month * term;
  over = total - sum;
  return std::make_tuple(month, total, over);
}

std::tuple<double, double, double, double> Economy::Differentiated(double sum,
                                                                   int term,
                                                                   double per) {
  double max_month = 0, min_month = 0, over = 0, total = 0, pay = sum / term;
  max_month = pay + sum * per / (100 * 12);
  for (int i = 0; i < term; i++) {
    min_month = pay + (sum - (pay * i)) * per / 12 / 100;
    total += min_month;
  }
  over = total - sum;
  return std::make_tuple(min_month, max_month, total, over);
}

std::tuple<double, double, double> Economy::Deposit(
    double sum, int term, double per, double nalog_per, int term_payment,
    int kapital, int list_add, double add, int list_take, double take) {
  double payment = 0, total = 0, nalog_sum = 0;
  int a = 0, m = 0;
  if (list_add || list_take) {
    if (list_add == 1)
      a = 1;
    else if (list_add == 2)
      a = 3;
    else if (list_add == 3)
      a = 6;
    else if (list_add == 4)
      a = 12;

    if (list_take == 1)
      m = 1;
    else if (list_take == 2)
      m = 3;
    else if (list_take == 3)
      m = 6;
    else if (list_take == 4)
      m = 12;
  }
  if (!kapital) {
    double p = 0;
    for (int i = 1; i <= term; i++) {
      payment += ((sum + p) * per * 30.417 / 365.25 / 100);
      sum += !fmod(i, a) ? add : 0;
      sum -= !fmod(i, m) ? take : 0;
    }
    total = sum + payment;
    if (payment > 1000000 * nalog_per) {
      nalog_sum = ((payment - 1000000 * nalog_per) * 13 * 0.01);
    }
  } else {
    int k = 0;
    if (term_payment == 0)
      k = 9999;
    else if (term_payment == 1)
      k = 1;
    else if (term_payment == 2)
      k = 4;
    else if (term_payment == 3)
      k = 12;
    double p = 0;
    for (int i = 1; i <= term; i++) {
      payment += ((sum + p) * per * 30.417 / 365.25 / 100);
      p = !fmod(i, k) ? payment : 0;
      sum += !fmod(i, a) ? add : 0;
      sum -= !fmod(i, m) ? take : 0;
    }
    total = sum + payment;
    if (payment > 1000000 * nalog_per) {
      nalog_sum = ((payment - 1000000 * nalog_per) * 13 * 0.01);
    }
  }
  return std::make_tuple(payment, total, nalog_sum);
}

}  // namespace s21