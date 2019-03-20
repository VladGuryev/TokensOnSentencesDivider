#ifndef SPLIT_INTO_SENTENCES_H
#define SPLIT_INTO_SENTENCES_H
#include <vector>

using namespace std;

// Объявляем Sentence<Token> для произвольного типа Token
// синонимом vector<Token>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор предложений — vector<Sentence<Token>>.
template <typename Token>
using Sentence = vector<Token>;

// Класс Token имеет метод bool IsEndSentencePunctuation() const
template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
  // Напишите реализацию функции, не копируя объекты типа Token
  vector<Sentence<Token>> sentences;
  Sentence<Token> sentence;

  bool previousWasEndPunc = false;
  bool currentIsEndPunc = false;

  for(auto&& token : tokens){
      currentIsEndPunc = token.IsEndSentencePunctuation();
      if(!currentIsEndPunc && previousWasEndPunc){
        sentences.push_back(move(sentence));
        previousWasEndPunc = false;
      } else {
        if(currentIsEndPunc)
          previousWasEndPunc = true;
      }
      sentence.push_back(move(token));
    }
  sentences.push_back(move(sentence));
  return sentences;
}
#endif // SPLIT_INTO_SENTENCES_H
