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
    if (current == nullptr) {
        cout << "Word not found in the dictionary." << endl;
        return;
    }
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

void deleteWord(Word*& head, string word) {
    Word* current = head;
    Word* prev = nullptr;

    while (current != nullptr && current->value != word) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Word not found in the dictionary." << endl;
        return;
    }

    if (prev == nullptr) {
        head = current->next;
    } else {
        prev->next = current->next;
    }

    Synonym* syn = current->synonym;
    while (syn != nullptr) {
        Synonym* temp = syn;
        syn = syn->next;
        delete temp;
        cout << "Word and it's synonyms are deleted successfully!";
    }
    delete current;
}
void deleteSynonym(Word*& head, string word, string synonym) {
    Word* current = head;

    // Search for the word in the linked list
    while (current != nullptr && current->value != word) {
        current = current->next;
    }

    // If the word is not found, return
    if (current == nullptr) {
        cout << "Word not found in the dictionary." << endl;
        return;
    }

    // Search for the synonym in the synonym list of the word
    Synonym* syn = current->synonym;
    Synonym* prev = nullptr;
    while (syn != nullptr && syn->value != synonym) {
        prev = syn;
        syn = syn->next;
    }

    // If the synonym is not found, return
    if (syn == nullptr) {
        cout << "Synonym not found for the word." << endl;
        return;
    }

    // If the synonym is found, remove it from the synonym list
    if (prev == nullptr) { // If the synonym to be deleted is the first node
        current->synonym = syn->next;
    } else {
        prev->next = syn->next;
    }

    // Free memory for the removed synonym node
    delete syn;

    // If the synonym list becomes empty, remove the word itself
    if (current->synonym == nullptr) {
        deleteWord(head, word);
    }
}
int main() {
    Word* head = nullptr;
    addWord(head, "happy", "joyful");
    addWord(head, "sad", "unhappy");
    showWordAndSynonym(head);
    deleteWord(head,"happy");
    showWordAndSynonym(head);
    return 0;
}
