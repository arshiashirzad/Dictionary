#include <iostream>
#include <string>
using namespace std;
struct Synonym {
    string value;
    Synonym* next;
};

struct Word {
    string value;
    Word* next;
    Synonym* synonym;
};

void addWord(Word*& head, string word, string synonym) {
    Synonym* newSynonym = new Synonym;
    newSynonym->value = synonym;
    newSynonym->next = nullptr;

    Word* newWord = new Word;
    newWord->value = word;
    newWord->synonym = newSynonym;

    if (head == nullptr || head->value > word) {
        newWord->next = head;
        head = newWord;
        return;
    }

    Word* current = head;
    while (current->next != nullptr && current->next->value <= word) {
        current = current->next;
    }

    if (current->value == word) {
        Synonym* syn = current->synonym;
        while (syn->next != nullptr) {
            syn = syn->next;
        }
        syn->next = newSynonym;
        delete newWord;
    } else {
        newWord->next = current->next;
        current->next = newWord;
    }
}
void showWordAndSynonym(Word* head){
    Word* current = head;
    while (current != nullptr) {
        cout << "Word: " << current->value << endl;
        cout<< "Synonym: ";
        Synonym* syn = current->synonym;
        while (syn != nullptr) {
            cout << syn->value << " " ;
            syn = syn->next;
        }
        cout << endl;
        current = current->next;
    }
}
int main() {
    Word* head = nullptr;
    addWord(head, "happy", "joyful");
    addWord(head, "happy", "content");
    addWord(head, "happy", "glad");
    addWord(head, "sad", "unhappy");
    showWordAndSynonym(head);
    return 0;
}
