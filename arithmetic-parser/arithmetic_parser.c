#include <stdio.h>
#include <stdbool.h>

/**
 * Arithemtic Language Definitions:
 * <not_zero> ::= '1'|...|'9'
 * <digit> ::= '0' | <not_zero>
 * <raw> ::= <digit> | <digit> <raw>
 * <number> ::= <digit> | <not_zero> <raw>
 * <str> ::= <number> '0'
 * 
 * EXPR TODO:
 * <expr> ::= <number> | <number> '+' <expr> | <number> '-' <expr> 
 * **/

const char* stream = NULL;

bool accept(char c) {
  if (*stream == c) {
    stream++;
    return true;
  }
  return false;
}

bool notzero(void) {
  return accept('1') || accept('2') || accept('3') || accept('4') ||
         accept('5') || accept('6') || accept('7') || accept('8') || 
         accept('9');
}

bool digit(void) {
  return accept('0') || notzero();
}

bool raw(void) {
  if (digit()) {
    raw();
    return true;
  }
  return false;
}

bool number() {
  if (notzero()) {
    raw();
    return true;
  }
  return accept('0');
}

bool str() {
  return number() && accept('\0');
}

bool recursive_descent_check(const char* expr) {
  stream = expr;
  return str();
};

int main(void) {
  const char* test_exprs[6] = { "304002", "1240", "123", "02342", "23c42", "abc"};
  const bool expectations[6] = { true, true, true, false, false, false};

  for (int i = 0; i < 6; i++) {
    const char* test_expr = test_exprs[i];
    bool result = recursive_descent_check(test_expr);
    bool expected = expectations[i];
    if (expected != result) {
      printf("%s: EXPECTED %s != RECIEVED %s =>FAILED\n", test_expr, expected ? "true" : "false", result ? "true" : "false");
    } else {
      printf("%s EXPECTED %s === RECIEVED %s => PASSED\n", test_expr,  expected ? "true" : "false", result ? "true" : "false");
    }
  }
  return 0;
}
