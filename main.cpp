#include <iostream>
#include <string>
using namespace std;
//Declaring LinkedLists
struct Dictionary{

};
 struct Synonym {
    string value;
    Synonym* next;
};
 struct Word{
    string value;
    Word* next;
    Synonym* synonym;
};
//new word
void addWord(){
    string wrd;
    cout <<"ENTER WORD:\n";
    cin >> wrd;
    Word* word = new Word;
    word->value = wrd;
    word->next= nullptr;
}
void showWordInfo(Word* word){
    while(word->next != nullptr){
        cout<< word->value;
        word = word->next;
    }
}
int main() {
addWord();
}
