#include "Model.h"

namespace s21 {

Model::Model() : pos_(0U) {}

void Model::Parser() {
  pos_ = 0U;
  while (note_[pos_]) {
    if (note_[pos_] == ' ') {
      ++pos_;
    } else if (note_[pos_] == 'x') {
      polish_.append("x");
      ++pos_;
    } else if (std::isdigit(note_[pos_])) {
      CopyNum();
    } else if (note_[pos_] > 32) {
      if ((!pos_ || note_[pos_ - 1] == '(') &&
          (note_[pos_] == '-' || note_[pos_] == '+')) {
        polish_.append("0 ", 2);
      }
      TakeOper();
    }
  }
  while (!stack_.empty()) {
    CopyOper(stack_.top().first);
    stack_.pop();
  }
}

void Model::CopyNum() {
  while (isdigit(note_[pos_]) || note_[pos_] == '.' || note_[pos_] == 'e') {
    if (note_[pos_] == 'e') {
      polish_.append(&note_[pos_], 2);
      pos_ += 2;
    } else {
      polish_ += note_[pos_++];
    }
    // ++pos_;
  }
  polish_ += ' ';
}

void Model::TakeOper() {
  std::pair<tok, int> token = OperDef(note_);
  if (!stack_.empty() && stack_.top().first <= LOG &&
      token.second <= stack_.top().second) {
    while (!stack_.empty() && stack_.top().first <= LOG &&
           token.second <= stack_.top().second) {
      CopyOper(stack_.top().first);
      stack_.pop();
    }
    stack_.push(token);
  } else if (token.first == CL_BR) {
    while (stack_.top().first < OP_BR) {
      CopyOper(stack_.top().first);
      stack_.pop();
    }
    stack_.pop();
  } else {
    stack_.push(token);
  }
}

std::pair<tok, int> Model::OperDef(std::string& str) {
  std::pair<tok, int> op(NUM, 0);
  if (!str.compare(pos_, 3, "cos")) {
    op = std::make_pair(COS, 4);
    pos_ += 3;
  } else if (!str.compare(pos_, 3, "sin")) {
    op = std::make_pair(SIN, 4);
    pos_ += 3;
  } else if (!str.compare(pos_, 3, "tan")) {
    op = std::make_pair(TAN, 4);
    pos_ += 3;
  } else if (!str.compare(pos_, 3, "log")) {
    op = std::make_pair(LOG, 4);
    pos_ += 3;
  } else if (!str.compare(pos_, 3, "mod")) {
    op = std::make_pair(MOD, 3);
    pos_ += 3;
  } else if (!str.compare(pos_, 4, "acos")) {
    op = std::make_pair(ACOS, 4);
    pos_ += 4;
  } else if (!str.compare(pos_, 4, "asin")) {
    op = std::make_pair(ASIN, 4);
    pos_ += 4;
  } else if (!str.compare(pos_, 4, "atan")) {
    op = std::make_pair(ATAN, 4);
    pos_ += 4;
  } else if (!str.compare(pos_, 4, "sqrt")) {
    op = std::make_pair(SQRT, 4);
    pos_ += 4;
  } else if (!str.compare(pos_, 2, "ln")) {
    op = std::make_pair(LN, 4);
    pos_ += 2;
  } else if (str[pos_] == '+') {
    op = std::make_pair(PLUS, 1);
    ++pos_;
  } else if (str[pos_] == '-') {
    op = std::make_pair(MINUS, 1);
    ++pos_;
  } else if (str[pos_] == '*') {
    op = std::make_pair(MULT, 2);
    ++pos_;
  } else if (str[pos_] == '/') {
    op = std::make_pair(DIV, 2);
    ++pos_;
  } else if (str[pos_] == '^') {
    op = std::make_pair(POW, 3);
    ++pos_;
  } else if (str[pos_] == '(') {
    op = std::make_pair(OP_BR, 5);
    ++pos_;
  } else if (str[pos_] == ')') {
    op = std::make_pair(CL_BR, 5);
    ++pos_;
  } else {
    ++pos_;
  }
  return op;
}

void Model::CopyOper(int token) {
  switch (token) {
    case PLUS:
      polish_.append("+ ", 2);
      break;
    case MINUS:
      polish_.append("- ", 2);
      break;
    case MULT:
      polish_.append("* ", 2);
      break;
    case DIV:
      polish_.append("/ ", 2);
      break;
    case POW:
      polish_.append("^ ", 2);
      break;
    case MOD:
      polish_.append("mod ", 4);
      break;
    case COS:
      polish_.append("cos ", 4);
      break;
    case SIN:
      polish_.append("sin ", 4);
      break;
    case TAN:
      polish_.append("tan ", 4);
      break;
    case ACOS:
      polish_.append("acos ", 5);
      break;
    case ASIN:
      polish_.append("asin ", 5);
      break;
    case ATAN:
      polish_.append("atan ", 5);
      break;
    case SQRT:
      polish_.append("sqrt ", 5);
      break;
    case LN:
      polish_.append("ln ", 3);
      break;
    case LOG:
      polish_.append("log ", 4);
      break;
    default:
      break;
  }
}

double Model::Calculator(double x) {
  pos_ = 0U;
  while (!stack_.empty()) {
    stack_.pop();
  }
  while (polish_[pos_]) {
    if (std::isdigit(polish_[pos_])) {
      stack_.push(std::make_pair(std::stod(&polish_[pos_]), NUM));
      while (polish_[++pos_] != ' ')
        ;
    } else if (polish_[pos_] == 'x') {
      stack_.push(std::make_pair(x, X));
      ++pos_;
    } else if (polish_[pos_] > 32) {
      std::pair<tok, int> token = OperDef(polish_);
      if (token.first < COS) {
        double x = stack_.top().first;
        stack_.pop();
        double y = stack_.top().first;
        stack_.pop();
        BinCalc(x, y, token.first);
      } else {
        double x = stack_.top().first;
        stack_.pop();
        UnCalc(x, token.first);
      }
    } else {
      ++pos_;
    }
  }
  double result = stack_.top().first;
  stack_.pop();
  return result;
}

void Model::BinCalc(double x, double y, tok token) {
  switch (token) {
    case PLUS:
      stack_.push(std::make_pair(x + y, NUM));
      break;
    case MINUS:
      stack_.push(std::make_pair(y - x, NUM));
      break;
    case MULT:
      stack_.push(std::make_pair(x * y, NUM));
      break;
    case DIV:
      stack_.push(std::make_pair(y / x, NUM));
      break;
    case POW:
      stack_.push(std::make_pair(pow(y, x), NUM));
      break;
    case MOD:
      stack_.push(std::make_pair(fmod(y, x), NUM));
      break;
    default:
      break;
  }
}

void Model::UnCalc(double x, tok token) {
  switch (token) {
    case COS:
      stack_.push(std::make_pair(cos(x), NUM));
      break;
    case SIN:
      stack_.push(std::make_pair(sin(x), NUM));
      break;
    case TAN:
      stack_.push(std::make_pair(tan(x), NUM));
      break;
    case ACOS:
      stack_.push(std::make_pair(acos(x), NUM));
      break;
    case ASIN:
      stack_.push(std::make_pair(asin(x), NUM));
      break;
    case ATAN:
      stack_.push(std::make_pair(atan(x), NUM));
      break;
    case SQRT:
      stack_.push(std::make_pair(sqrt(x), NUM));
      break;
    case LN:
      stack_.push(std::make_pair(log(x), NUM));
      break;
    case LOG:
      stack_.push(std::make_pair(log10(x), NUM));
      break;
    default:
      break;
  }
}

void Model::Validate(std::string str) {
  int un = 0, bin = 0, br = 0, op = 0, dg = 0;
  pos_ = 0U, note_ = str;
  if (note_.length() > 256) {
    throw std::length_error("Expression length exceeds allowable length");
  }
  while (note_[pos_]) {
    while (note_[pos_] == ' ') {
      ++pos_;
    }
    if (std::isdigit(note_[pos_]) || note_[pos_] == 'x') {
      if (dg) {
        throw std::invalid_argument("Incorrect expression");
      }
      bin = 0, un = 0, op = 0, ++pos_;
      int point = 0, e = 0;
      while ((std::isdigit(note_[pos_]) || note_[pos_] == '.' ||
              note_[pos_] == 'e')) {
        if (note_[pos_] == 'e') {
          if (e) {
            throw std::invalid_argument("Incorrect expression");
          }
          e = 1, point = 1;
        }
        if (note_[pos_] == '.') {
          if (point) {
            throw std::invalid_argument("Incorrect expression");
          }
          point = 1;
        }
        ++pos_;
      }
      dg = 1;
    } else {
      std::pair x = OperDef(note_);
      if (!x.first) {
        throw std::invalid_argument("Incorrect expression");
      } else if (x.first >= PLUS && x.first <= MINUS && !bin) {
        bin = 1, dg = 0, un = 0, op = 0;
      } else if (x.first >= MULT && x.first <= MOD && !bin && !op) {
        bin = 1, dg = 0, un = 0, op = 0;
      } else if (x.first >= COS && x.first <= LOG && !un && !dg) {
        un = 1, dg = 0, bin = 0, op = 0;
      } else if (x.first == OP_BR) {
        op = 1, bin = 0, un = 0, dg = 0;
        br++;
      } else if (x.first == CL_BR && !bin && !op) {
        br--;
      } else {
        throw std::invalid_argument("Incorrect expression");
      }
    }
  }
  if (br) {
    throw std::invalid_argument("Incorrect expression");
  }
}

}  // namespace s21
