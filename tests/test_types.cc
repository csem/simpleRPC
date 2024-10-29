#include <catch.hpp>

#include <Arduino.h>

#include "../src/types.tcc"

extern Stream Serial;


TEST_CASE("Basic types 1", "[types][basic]") {
  bool b {};
  char c {};
  signed char sc {};
  unsigned char uc {};
  short int si {};
  unsigned short int usi {};
  long int li {};
  unsigned long int uli {};
  long long int lli {};
  unsigned long long int ulli {};
  float f {};

  Serial.reset();
  rpcTypeOf(Serial, b);
  rpcTypeOf(Serial, c);
  rpcTypeOf(Serial, sc);
  rpcTypeOf(Serial, uc);
  rpcTypeOf(Serial, si);
  rpcTypeOf(Serial, usi);
  rpcTypeOf(Serial, li);
  rpcTypeOf(Serial, uli);
  rpcTypeOf(Serial, lli);
  rpcTypeOf(Serial, ulli);
  rpcTypeOf(Serial, f);
  REQUIRE(Serial.inspect<String>() == "?cbBhHlLqQf");
}

TEST_CASE("Basic types 2", "[types][basic]") {
  int i {};
  unsigned int ui {};
  double d {};

  // Basic types of which the size may differ between platforms.
  Serial.reset();
  rpcTypeOf(Serial, i);
  rpcTypeOf(Serial, ui);
  if (sizeof(int) == 2) {
    REQUIRE(Serial.inspect<String>() == "hH");
  }
  else {
    REQUIRE(Serial.inspect<String>() == "iI");
  }

  Serial.reset();
  rpcTypeOf(Serial, d);
  if (sizeof(double) == 4) {
    REQUIRE(Serial.inspect<String>() == "f");
  }
  else {
    REQUIRE(Serial.inspect<String>() == "d");
  }
}

TEST_CASE("String type", "[types][string]") {
  String s0 {};
  char* s1 {};
  char const* s2 {};

  Serial.reset();
  rpcTypeOf(Serial, s0);
  rpcTypeOf(Serial, s1);
  rpcTypeOf(Serial, s2);
  REQUIRE(Serial.inspect<String>() == "sss");
}

TEST_CASE("Tuple types", "[types][tuple]") {
  Tuple<int, char> ic {};
  Tuple<int, signed char, unsigned long> iscul {};

  Serial.reset();
  rpcTypeOf(Serial, ic);
  rpcTypeOf(Serial, iscul);
  REQUIRE(Serial.inspect<String>() == "(ic)(ibL)");
}

TEST_CASE("Complex Tuple types", "[types][object]") {
  Tuple<Tuple<char, int>, unsigned long> o0 {};
  Tuple<
    Tuple<
      Tuple<char, char, char>,
      char>,
    char,
    Tuple<
      Tuple<char, char>,
      Tuple<char>>> o1 {};

  Serial.reset();
  rpcTypeOf(Serial, o0);
  rpcTypeOf(Serial, o1);
  REQUIRE(Serial.inspect<String>() == "((ci)L)(((ccc)c)c((cc)(c)))");
}

TEST_CASE("Array", "[types][array]") {
  Array<int, 2> a {};

  Serial.reset();
  rpcTypeOf(Serial, a);
  REQUIRE(Serial.inspect<char>() == '[');
  REQUIRE(Serial.inspect<size_t>() == 2);
  REQUIRE(Serial.inspect<String>() == "i]");
}