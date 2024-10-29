#include <catch.hpp>

#include "../src/write.tcc"

extern Stream Serial;


TEST_CASE("Write basic types", "[write][basic]") {
  int i {1234};
  char c {'x'};

  Serial.reset();
  rpcWrite(Serial, &i);
  rpcWrite(Serial, &c);
  REQUIRE(Serial.inspect<int>() == 1234);
  REQUIRE(Serial.inspect<char>() == 'x');
}

TEST_CASE("Write String", "[write][string]") {
  String s {"xyz"};

  Serial.reset();
  rpcWrite(Serial, &s);
  REQUIRE(Serial.inspect<String>() == "xyz");
}

TEST_CASE("Write C string of type char*", "[write][string]") {
  char* s {const_cast<char*>("xyz")};

  Serial.reset();
  rpcWrite(Serial, &s);
  REQUIRE(Serial.inspect<String>() == "xyz");
}

TEST_CASE("Write C string of type char const*", "[write][string]") {
  char const* s {"xyz"};

  Serial.reset();
  rpcWrite(Serial, &s);
  REQUIRE(Serial.inspect<String>() == "xyz");
}

TEST_CASE("Write tuple", "[write][tuple]") {
  Tuple<int, char> t {1234, 'x'};

  Serial.reset();
  rpcWrite(Serial, &t);
  REQUIRE(Serial.inspect<int>() == 1234);
  REQUIRE(Serial.inspect<char>() == 'x');
}

TEST_CASE("Write array", "[write][array]") {
  Array<int, 2> a {{1234, 2345}};

  Serial.reset();
  rpcWrite(Serial, &a);
  REQUIRE(Serial.inspect<size_t>() == 2);
  REQUIRE(Serial.inspect<int>() == 1234);
  REQUIRE(Serial.inspect<int>() == 2345);
}