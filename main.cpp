#include "test_runner.h"
#include "split_into_sentences.h"
#include "tests.h"

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSplitting);
  RUN_TEST(tr, TestSplitingNonCopy);
  return 0;
}
