#ifndef TESTS_H
#define TESTS_H
#include <string>
#include <utility>
#include "split_into_sentences.h"
#include <test_runner.h>
#include <cstdint>
using namespace  std;

struct TestToken {
  string data;
  bool is_end_sentence_punctuation = false;

  bool IsEndSentencePunctuation() const {
    return is_end_sentence_punctuation;
  }
  bool operator==(const TestToken& other) const {
    return data == other.data
        && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
  }
};

ostream& operator<<(ostream& stream, const TestToken& token) {
  return stream << token.data;
}

// Тест содержит копирования объектов класса TestToken.
// Для проверки отсутствия копирований в функции SplitIntoSentences
// необходимо написать отдельный тест.
void TestSplitting() {
  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!"}}
    })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
    })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
        {{"Without"}, {"copies"}, {".", true}},
    })
  );
}

struct TestNonCopyableToken {
  string data;
  bool is_end_sentence_punctuation = false;

  TestNonCopyableToken(const TestNonCopyableToken&) = delete;
  TestNonCopyableToken& operator=(const TestNonCopyableToken&) = delete;

  TestNonCopyableToken(TestNonCopyableToken&&) = default;
  TestNonCopyableToken& operator=(TestNonCopyableToken&&) = default;

  bool IsEndSentencePunctuation() const {
    return is_end_sentence_punctuation;
  }

  bool operator==(const TestNonCopyableToken& other) const {
    return data == other.data
        && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
  }
};

ostream& operator<<(ostream& stream, const TestNonCopyableToken& token) {
  return stream << token.data;
}

void TestSplitingNonCopy(){
  {
    vector<TestNonCopyableToken> vec;
    vec.push_back({"Split"});
    vec.push_back({"into"});
    vec.push_back({"sentences"});
    vec.push_back({"!"});

    Sentence<TestNonCopyableToken> sentence;
    sentence.push_back({"Split"});
    sentence.push_back({"into"});
    sentence.push_back({"sentences"});
    sentence.push_back({"!"});
    vector<Sentence<TestNonCopyableToken>> sentences;
    sentences.push_back(move(sentence));

    ASSERT_EQUAL(SplitIntoSentences(move(vec)), sentences);
  }
  {
    vector<TestNonCopyableToken> vec;
    vec.push_back({"Split"});
    vec.push_back({"into"});
    vec.push_back({"sentences"});
    vec.push_back({"!", true});

    Sentence<TestNonCopyableToken> sentence;
    sentence.push_back({"Split"});
    sentence.push_back({"into"});
    sentence.push_back({"sentences"});
    sentence.push_back({"!", true});
    vector<Sentence<TestNonCopyableToken>> sentences;
    sentences.push_back(move(sentence));

    ASSERT_EQUAL(SplitIntoSentences(move(vec)), sentences);
  }
  {
    vector<TestNonCopyableToken> vec;
    vec.push_back({"Split"});
    vec.push_back({"into"});
    vec.push_back({"sentences"});
    vec.push_back({"!", true});
    vec.push_back({"!", true});
    vec.push_back({"Without"});
    vec.push_back({"copies"});
    vec.push_back({".", true});

    Sentence<TestNonCopyableToken> sentence1;
    sentence1.push_back({"Split"});
    sentence1.push_back({"into"});
    sentence1.push_back({"sentences"});
    sentence1.push_back({"!", true});
    sentence1.push_back({"!", true});

    Sentence<TestNonCopyableToken> sentence2;
    sentence2.push_back({"Without"});
    sentence2.push_back({"copies"});
    sentence2.push_back({".", true});

    vector<Sentence<TestNonCopyableToken>> sentences;
    sentences.push_back(move(sentence1));
    sentences.push_back(move(sentence2));

    ASSERT_EQUAL(SplitIntoSentences(move(vec)), sentences);
  }


}

#endif // TESTS_H
