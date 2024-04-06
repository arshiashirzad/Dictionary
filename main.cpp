#include <iostream>
using namespace std;
struct Synonym {
    string value;
    Synonym* next{};
};
struct Word{
    string value;
    Word* next{};
    Synonym* synonym{};
};

int main() {

}
