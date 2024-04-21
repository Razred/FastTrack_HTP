#include <iostream>
#include <vector>
#include <memory>
#include <array>
#include <variant>
#include <unordered_map>

// (1 + 2) * 3 / 4 + 5 * (6 - 7)

// 1. Токенизация
// 2. Парсер (построение дерева разбора выражения)

// +, -, *, /, %

struct OpeningBracket {};

struct ClosingBracket {};

struct Number {
    int value;
};

struct UnknownToken {
    std::string value;
};

struct MinToken {};

struct AbsToken {};

struct MaxToken {};

struct SqrToken {};

struct Plus {};

struct Minus {};

struct Multiply {};

struct Modulo {};

struct Divide {};


using Token = std::variant<OpeningBracket, ClosingBracket, Number, UnknownToken, MinToken, AbsToken, Plus, Minus, Multiply, Divide, Modulo, MaxToken, SqrToken>;

const std::unordered_map<char, Token> kSymbol2Token {
        {'+', Plus{}}, {'-', Minus{}}, {'*', Multiply{}}, {'/', Divide{}}, {'%', Modulo{}}, {'(', OpeningBracket{}}, {')', ClosingBracket{}}};

const std::unordered_map<std::string, Token>  kExpression2Token {
        {"min", MinToken{}}, {"max", MaxToken{}}, {"abs", AbsToken{}}, {"sqr", SqrToken{}}};

int ToDigit(unsigned char symbol) {
    return symbol - '0';
}

Number ParseNumber(const std::string& input, size_t& pos) {
    int value = 0;
    auto symbol = static_cast<unsigned char>(input[pos]);
    while (std::isdigit(symbol)) {
        value = value * 10 + ToDigit(symbol);
        if (pos == input.size() - 1) {
            break;
        }
        symbol = static_cast<unsigned char>(input[++pos]);
    }
    return Number{value};
}

Token ParseName(const std::string& input, size_t& pos) {
    std::string expression;
    while (std::isalpha(static_cast<unsigned char>(input[pos]))) {
        expression += input[pos++];
        if (pos == input.size()) {
            break;
        }
    }

    if (auto it = kExpression2Token.find(expression); it != kExpression2Token.end()) {
        return it->second;
    }

    return UnknownToken{expression};


}

std::vector<Token> Tokenize(const std::string& input) {
    std::vector<Token> tokens;
    const size_t size = input.size();
    size_t pos = 0;
    while (pos < size) {
        const auto symbol = static_cast<unsigned char>(input[pos]);
        if (std::isspace(symbol)) {
            ++pos;
            continue;
        } else if (std::isdigit(symbol)) {
            tokens.emplace_back(ParseNumber(input, pos));
        } else if (auto it = kSymbol2Token.find(symbol); it != kSymbol2Token.end()) {
            tokens.emplace_back(it->second);
        } else if (std::isalpha(symbol)) {
            tokens.emplace_back(ParseName(input, pos));
        }
        ++pos;
    }
    return tokens;
}

int main() {
    std::string input = "1 + min(3,2)";
    auto tmp = Tokenize(input);

    int k = 1;
    return 0;

}