#include <catch.hpp>

#include <Arduino.h>

#include "../src/signature.tcc"

extern Stream Serial;


TEST_CASE("Function pointer types", "[signature][basic]") {
  short int (*f0)(char, float) {};
  void (*f1)(char, float) {};

  Serial.reset();
  signature(Serial, f0);
  signature(Serial, f1);
  REQUIRE(Serial.inspect<String>() == "h: c f: c f");
}

TEST_CASE("Class member function pointer types", "[signature][class]") {
  class C {
    public:
      short int f0(char, float) {
        return 0;
      }
      void f1(char, float) {}
  };

  Serial.reset();
  signature(Serial, &C::f0);
  signature(Serial, &C::f1);
  REQUIRE(Serial.inspect<String>() == "h: c f: c f");
}

TEST_CASE("Tuples", "[signature][object]") {
  void (*f0)(Tuple<int, char>, float) {};
  Tuple<int, char> (*f1)(float) {};

  Serial.reset();
  signature(Serial, f0);
  signature(Serial, f1);
  REQUIRE(Serial.inspect<String>() == ": (ic) f(ic): f");
}
