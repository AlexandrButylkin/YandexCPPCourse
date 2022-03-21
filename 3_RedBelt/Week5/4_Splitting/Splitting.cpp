#include "../../Utils/TestRunner.h"

#include <vector>

using namespace std;

template <typename Token>
using Sentence = vector<Token>;

template <typename It>
It FindEndSentence(It begin, It end){
    It res = std::adjacent_find(begin, end, [](const auto& lhs, const auto& rhs){
        return lhs.IsEndSentencePunctuation() && !rhs.IsEndSentencePunctuation();
    });
    return res == end ? res : ++res;
}

template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
    std::vector<Sentence<Token>> res;
    auto curr_iter = tokens.begin();

    while(curr_iter != tokens.end()){
        auto iter_begin = curr_iter;
        curr_iter = FindEndSentence(curr_iter, tokens.end());
        res.emplace_back( Sentence<Token>(std::make_move_iterator(iter_begin), make_move_iterator(curr_iter)));
    }
    return res;
}


struct TestToken {
    string data;
    bool is_end_sentence_punctuation = false;

    bool IsEndSentencePunctuation() const {
        return is_end_sentence_punctuation;
    }
    bool operator==(const TestToken& other) const {
        return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
    }
};

ostream& operator<<(ostream& stream, const TestToken& token) {
    return stream << token.data;
}

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

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSplitting);
    return 0;
}
