#include <gtest/gtest.h>

#include "Controller/Controller.h"

TEST(ModelTest, Test1) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  c.Validator("2+2");
  c.Parser();
  EXPECT_EQ(c.Calculator(0), 4);
}

TEST(ModelTest, Test2) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  c.Validator("-1");
  c.Parser();
  EXPECT_EQ(c.Calculator(0), -1);
}

TEST(ModelTest, Test3) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  c.Validator("2*2");
  c.Parser();
  EXPECT_EQ(c.Calculator(0), 4);
}

TEST(ModelTest, Test4) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  c.Validator("44-2");
  c.Parser();
  EXPECT_EQ(c.Calculator(0), 44 - 2);
}

TEST(ModelTest, Test5) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  c.Validator("15*3");
  c.Parser();
  EXPECT_EQ(c.Calculator(0), 15 * 3);
}

TEST(ModelTest, Test6) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  c.Validator("12/4");
  c.Parser();
  EXPECT_EQ(c.Calculator(0), 12 / 4);
}

TEST(ModelTest, Test7) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  c.Validator("11^2");
  c.Parser();
  EXPECT_EQ(c.Calculator(0), pow(11, 2));
}

TEST(ModelTest, Test8) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  c.Validator("3 mod 10");
  c.Parser();
  EXPECT_EQ(c.Calculator(0), fmod(3, 10));
}

TEST(ModelTest, Test9) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  c.Validator("-1+3");
  c.Parser();
  EXPECT_EQ(c.Calculator(0), -1 + 3);
}

TEST(ModelTest, Test10) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  c.Validator("cos(2)");
  c.Parser();
  EXPECT_EQ(c.Calculator(0), cos(2));
}

TEST(ModelTest, Test11) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  c.Validator("tan(2)");
  c.Parser();
  EXPECT_EQ(c.Calculator(0), tan(2));
}

TEST(ModelTest, Test12) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  c.Validator("acos(0.4)");
  c.Parser();
  EXPECT_EQ(c.Calculator(0), acos(0.4));
}

TEST(ModelTest, Test13) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  c.Validator("sqrt(169)");
  c.Parser();
  EXPECT_EQ(c.Calculator(0), sqrt(169));
}

TEST(ModelTest, Test14) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  c.Validator("ln(3)");
  c.Parser();
  EXPECT_EQ(c.Calculator(0), log(3));
}

TEST(ModelTest, Test15) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  c.Validator("ln(10000)");
  c.Parser();
  EXPECT_EQ(c.Calculator(0), log(10000));
}

TEST(ModelTest, Test16) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  c.Validator("asin(0.4)");
  c.Parser();
  EXPECT_EQ(c.Calculator(0), asin(0.4));
}

TEST(ModelTest, Test17) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  c.Validator("atan(5)");
  c.Parser();
  EXPECT_EQ(c.Calculator(0), atan(5));
}

TEST(ModelTest, Test18) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  c.Validator("sin(1)^tan(1)+43/2*0+cos(45)");
  c.Parser();
  EXPECT_LT(c.Calculator(0) - 1.289607, 1e-06);
}

TEST(ModelTest, Test19) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  c.Validator("sin ( x )");
  c.Parser();
  EXPECT_EQ(c.Calculator(0), sin(0));
}

TEST(ModelTest, Test20) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  c.Validator("1/(1+3-5)*1000");
  c.Parser();
  EXPECT_EQ(c.Calculator(0), 1 / (1 + 3 - 5) * 1000);
}

TEST(ModelTest, Test21) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  c.Validator("log(1)");
  c.Parser();
  EXPECT_EQ(c.Calculator(0), log(1));
}

TEST(ModelTest, Test22) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  c.Validator("1.2e1+5");
  c.Parser();
  EXPECT_EQ(c.Calculator(0), 1.2e1 + 5);
}

TEST(ModelTest, Test23) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  c.Validator("1.2e-1+5e7");
  c.Parser();
  EXPECT_EQ(c.Calculator(0), 1.2e-1 + 5e7);
}

TEST(ValidatorTest, Test1) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  EXPECT_THROW(c.Validator("1.2e4.5-1+5e7"), std::invalid_argument);
}

TEST(ValidatorTest, Test2) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  EXPECT_THROW(c.Validator("1/(*1+3-5)*1000"), std::invalid_argument);
}

TEST(ValidatorTest, Test3) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  EXPECT_THROW(c.Validator("sin( )"), std::invalid_argument);
}

TEST(ValidatorTest, Test4) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  EXPECT_THROW(c.Validator("lnsinsqrtx"), std::invalid_argument);
}

TEST(ValidatorTest, Test5) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  EXPECT_THROW(c.Validator("1++12"), std::invalid_argument);
}

TEST(ValidatorTest, Test6) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  EXPECT_THROW(c.Validator("2.345.2324"), std::invalid_argument);
}

TEST(ValidatorTest, Test7) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  EXPECT_THROW(c.Validator("123123456765432123456787654321345678909876543212345"
                           "678909876543212345678"
                           "909876543212345678909876543234567898765432123456789"
                           "876543212345678987654"
                           "321234567897654323456789876543234567876543213456789"
                           "876543213456789876543"
                           "234567898765432345678987654323456789876543234567890"
                           "987654321234567890987"
                           "654321234567898765432123456789098765432123456789876"
                           "543234567898765432"),
               std::length_error);
}

// TEST(ValidatorTest, Test1) {
//   s21::Model m;
//   s21::Economy e;
//   s21::Controller c(m, e);
//   EXPECT_THROW(c.Validator("1++12"), std::invalid_argument);
// }

// TEST(ValidatorTest, Test1) {
//   s21::Model m;
//   s21::Economy e;
//   s21::Controller c(m, e);
//   EXPECT_THROW(c.Validator("1++12"), std::invalid_argument);
// }

TEST(CreditTest, Test1) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  double sum = 20000, term = 12, per = 15, payment = 0, total = 0, over = 0;
  std::tie(payment, total, over) = c.Annuity(sum, term, per);
  EXPECT_LE(payment - 1805.166247, 1e-6);
  EXPECT_LE(over - 1661.994963, 1e-6);
  EXPECT_LE(total - 21661.994963, 1e-6);
}

TEST(CreditTest, Test2) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  double sum = 20000, term = 12, per = 15, payment1 = 0, payment2 = 0,
         total = 0, over = 0;
  std::tie(payment1, payment2, total, over) = c.Differentiated(sum, term, per);
  EXPECT_LE(payment2 - 1916.666667, 1e-6);
  EXPECT_LE(payment1 - 1687.5, 1e-6);
  EXPECT_LE(over, 1625);
  EXPECT_LE(total - 21625, 1e-2);
}

TEST(DepositTest, Test1) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  double sum = 20000, per = 12, nalog_per = 12, add = 0, take = 0, payment = 0,
         total = 0, nalog_sum = 0;
  int term = 9, term_payment = 0, kapital = 0, list_add = 0, list_take = 0;
  std::tie(payment, total, nalog_sum) =
      c.Deposit(sum, term, per, nalog_per, term_payment, kapital, list_add, add,
                list_take, take);
  EXPECT_LE(payment - 1798.79, 1e-2);
  EXPECT_LE(total - 21798.79, 1e-2);
  EXPECT_LE(nalog_sum, 0);
}

TEST(DepositTest, Test2) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  double sum = 20000, per = 12, nalog_per = 12, add = 0, take = 0, payment = 0,
         total = 0, nalog_sum = 0;
  int term = 9, term_payment = 0, kapital = 0, list_add = 1, list_take = 1;
  std::tie(payment, total, nalog_sum) =
      c.Deposit(sum, term, per, nalog_per, term_payment, kapital, list_add, add,
                list_take, take);
  EXPECT_LE(payment - 1798.79, 1e-2);
  EXPECT_LE(total - 21798.79, 1e-2);
  EXPECT_LE(nalog_sum, 0);
}

TEST(DepositTest, Test3) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  double sum = 20000, per = 12, nalog_per = 12, add = 0, take = 0, payment = 0,
         total = 0, nalog_sum = 0;
  int term = 9, term_payment = 0, kapital = 0, list_add = 2, list_take = 2;
  std::tie(payment, total, nalog_sum) =
      c.Deposit(sum, term, per, nalog_per, term_payment, kapital, list_add, add,
                list_take, take);
  EXPECT_LE(payment - 1798.79, 1e-2);
  EXPECT_LE(total - 21798.79, 1e-2);
  EXPECT_LE(nalog_sum, 0);
}

TEST(DepositTest, Test4) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  double sum = 20000, per = 12, nalog_per = 12, add = 0, take = 0, payment = 0,
         total = 0, nalog_sum = 0;
  int term = 9, term_payment = 0, kapital = 0, list_add = 3, list_take = 3;
  std::tie(payment, total, nalog_sum) =
      c.Deposit(sum, term, per, nalog_per, term_payment, kapital, list_add, add,
                list_take, take);
  EXPECT_LE(payment - 1798.79, 1e-2);
  EXPECT_LE(total - 21798.79, 1e-2);
  EXPECT_LE(nalog_sum, 0);
}

TEST(DepositTest, Test5) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  double sum = 20000, per = 12, nalog_per = 12, add = 0, take = 0, payment = 0,
         total = 0, nalog_sum = 0;
  int term = 9, term_payment = 0, kapital = 0, list_add = 4, list_take = 4;
  std::tie(payment, total, nalog_sum) =
      c.Deposit(sum, term, per, nalog_per, term_payment, kapital, list_add, add,
                list_take, take);
  EXPECT_LE(payment - 1798.79, 1e-2);
  EXPECT_LE(total - 21798.79, 1e-2);
  EXPECT_LE(nalog_sum, 0);
}

TEST(DepositTest, Test6) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  double sum = 20000, per = 15, nalog_per = 12, add = 0, take = 0, payment = 0,
         total = 0, nalog_sum = 0;
  int term = 9, term_payment = 0, kapital = 1, list_add = 4, list_take = 4;
  std::tie(payment, total, nalog_sum) =
      c.Deposit(sum, term, per, nalog_per, term_payment, kapital, list_add, add,
                list_take, take);
  EXPECT_LE(payment - 2248.48, 1e-2);
  EXPECT_LE(total - 22248.48, 1e-2);
  EXPECT_LE(nalog_sum, 0);
}

TEST(DepositTest, Test7) {
  s21::Model m;
  s21::Economy e;
  s21::Controller c(m, e);
  double sum = 200000000, per = 15, nalog_per = 10, add = 0, take = 0,
         payment = 0, total = 0, nalog_sum = 0;
  int term = 9, term_payment = 0, kapital = 1, list_add = 4, list_take = 4;
  std::tie(payment, total, nalog_sum) =
      c.Deposit(sum, term, per, nalog_per, term_payment, kapital, list_add, add,
                list_take, take);
  EXPECT_LE(payment - 22484845.995893, 1e-2);
  EXPECT_LE(total - 222484845.995893, 1e-2);
  EXPECT_LE(nalog_sum - 1623029.979466, 1e-6);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}