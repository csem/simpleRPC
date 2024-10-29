#include <catch.hpp>

#include "../src/del.tcc"
#include "../src/read.tcc"

extern Stream Serial;


TEST_CASE("Read basic types", "[read][basic]") {
  int i;
  char c;

  Serial.reset();
  Serial.prepare(1234, 'x');
  rpcRead(Serial, &i);
  rpcRead(Serial, &c);
  REQUIRE(i == 1234);
  REQUIRE(c == 'x');
}

TEST_CASE("Read String", "[read][string]") {
  String s;

  Serial.reset();
  Serial.prepare("xyz");
  rpcRead(Serial, &s);
  REQUIRE(s == "xyz");
}

TEST_CASE("Read string of type char*", "[read][string]") {
  char* s;

  Serial.reset();
  Serial.prepare("xyz");
  rpcRead(Serial, &s);
  REQUIRE(not strcmp(s, "xyz"));
  rpcDel(&s);
}

TEST_CASE("Read string of type char const*", "[read][string]") {
  char const* s;

  Serial.reset();
  Serial.prepare("xyz");
  rpcRead(Serial, &s);
  REQUIRE(not strcmp(s, "xyz"));
  rpcDel(&s);
}

TEST_CASE("Read tuple", "[read][tuple]") {
  Tuple<int, char> t;

  Serial.reset();
  Serial.prepare(1234, 'x');
  rpcRead(Serial, &t);
  REQUIRE(t.head == 1234);
  REQUIRE(t.tail.head == 'x');
}

TEST_CASE("Read array", "[read][array]") {
  Array<int, 3> a;

  Serial.reset();
  Serial.prepare(3ul, 1234, 2345, 3456);
  rpcRead(Serial, &a);
  REQUIRE(a.size() == 3);
  REQUIRE(a[0] == 1234);
  REQUIRE(a[1] == 2345);
  REQUIRE(a[2] == 3456);
}

