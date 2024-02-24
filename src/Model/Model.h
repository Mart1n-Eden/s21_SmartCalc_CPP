#ifndef MODEL_H
#define MODEL_H

#include <cmath>
#include <iostream>
#include <stack>
#include <string>

namespace s21 {

enum tok {
  NUM,
  X,
  UN_PLUS,
  UN_MINUS,
  PLUS,
  MINUS,
  MULT,
  DIV,
  POW,
  MOD,
  COS,
  SIN,
  TAN,
  ACOS,
  ASIN,
  ATAN,
  SQRT,
  LN,
  LOG,
  OP_BR,
  CL_BR
};

class Model {
 public:
  Model();
  ~Model() = default;
  void Parser();
  void CopyNum();
  void CopyOper(int token);
  void TakeOper();
  void LenOper(tok token);
  std::pair<tok, int> OperDef(std::string& str);
  double Calculator(double x);
  void BinCalc(double x, double y, tok token);
  void UnCalc(double x, tok token);
  void Validate(std::string str);

 private:
  std::string note_;
  std::string polish_;
  size_t pos_;
  std::stack<std::pair<double, int> > stack_;
};
}  // namespace s21

#endif  // MODEL_H