#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
struct Synonym {
    string value;
    Synonym *next;
};
struct Word {
    string value;
    Word *next;
    Synonym *synonym;
};
void addWord(Word *&head, string word, string synonym) {
    Synonym *newSynonym = new Synonym;
    newSynonym->value = synonym;
    newSynonym->next = nullptr;
    Word *newWord = new Word;
    newWord->value = word;
    newWord->synonym = newSynonym;

    if (head == nullptr || head->value > word) {
        newWord->next = head;
        head = newWord;
        return;
    }

    Word *current = head;
    while (current->next != nullptr && current->next->value <= word) {
        current = current->next;
    }

    if (current->value == word) {
        Synonym *syn = current->synonym;
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

void showWordAndSynonym(Word *head) {
    Word *current = head;
    if (current == nullptr) {
        cout << "Dictionary is empty. " << endl;
        return;
    }
    while (current != nullptr) {
        cout << "Word: " << current->value<<"->";
        Synonym *syn = current->synonym;
        while (syn != nullptr) {
            cout << syn->value << " ";
            syn = syn->next;
        }
        cout << endl;
        current = current->next;
    }
}

void deleteWord(Word *&head, string word) {
    Word *current = head;
    Word *prev = nullptr;
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

    Synonym *syn = current->synonym;
    while (syn != nullptr) {
        Synonym *temp = syn;
        syn = syn->next;
        delete temp;
    }
    cout << "Word and it's synonyms are deleted successfully!" << endl;
    delete current;
}

void deleteSynonym(Word *&head, string word, string synonym) {
    Word *current = head;

    while (current != nullptr && current->value != word) {
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Word not found in the dictionary." << endl;
        return;
    }

    Synonym *syn = current->synonym;
    Synonym *prev = nullptr;
    while (syn != nullptr && syn->value != synonym) {
        prev = syn;
        syn = syn->next;
    }

    if (syn == nullptr) {
        cout << "Synonym not found for the word." << endl;
        return;
    }

    if (prev == nullptr) {
        current->synonym = syn->next;
    } else {
        prev->next = syn->next;
    }
    cout << "Synonym is deleted successfully!" << endl;
    delete syn;
}

void *searchWord(Word *head, string word) {
    Word *current = head;

    while (current != nullptr) {
        if (current->value == word) {
            cout << "Word: " << current->value<< "->";
            Synonym *syn = current->synonym;
            while (syn != nullptr) {
                cout << " " << syn->value ;
                syn = syn->next;
            }
            cout<< endl;
        } else {
            cout << "Word not found in the dictionary." << endl;
        }
        current = current->next;
    }
}

Word* readDictionary() {
    ifstream file("Dictionary.txt");
    Word* head = nullptr;
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string word;
            getline(ss, word, ':');
            Word* newWord = new Word;
            newWord->value = word;
            newWord->synonym = nullptr;
            newWord->next = nullptr;
            string synonyms;
            getline(ss, synonyms);
            stringstream synStream(synonyms);
            string synonym;
            while (getline(synStream, synonym, ',')) {
                addWord(head, word, synonym);
            }
        }
        file.close();
        cout << "Dictionary loaded from file successfully." << endl;
    } else {
        cout << "Unable to open the file." << endl;
    }
    return head;
}
void saveDictionary(Word *head) {
    ofstream file("Dictionary.txt");
    if (file.is_open()) {
        Word *current = head;
        while (current != nullptr) {
            file << current->value << ": ";
            Synonym *syn = current->synonym;
            while (syn != nullptr) {
                file << syn->value;
                if (syn->next != nullptr) {
                    file << ",";
                }
                syn = syn->next;
            }
            file << endl;
            current = current->next;
        }
        file.close();
        cout << "Dictionary saved to file successfully." << endl;
    } else {
        cout << "Unable to open the file." << endl;
    }
}

int main() {
    Word *head = readDictionary();
    int cntrl = 0;
    cout << "welcome to Dictionary" << endl;
    while (cntrl != 7) {
        cout << "1.Show dictionary" << endl <<
             "2.Add new word " << endl <<
             "3.Delete a word" << endl <<
             "4.Delete synonym" << endl <<
             "5.Search Word" << endl <<
             "6.Save Dictionary to file" << endl <<
             "7.Exit" << endl <<
             "ENTER HERE:" << endl;
        cin >> cntrl;
        string word, synonym;
        switch (cntrl) {
            case 1 :
                showWordAndSynonym(head);
                break;
            case 2 :
                cout << "Enter the word you want to add:" << endl;
                cin >> word;
                cout << "Enter the synonym you want to add:" << endl;
                cin >> synonym;
                addWord(head, word, synonym);
                break;
            case 3 :
                cout << "Enter the word you want to delete:" << endl;
                cin >> word;
                deleteWord(head, word);
                break;
            case 4:
                cout << "First enter the word:" << endl;
                cin >> word;
                cout << "Enter the synonym you want to delete:" << endl;
                cin >> synonym;
                deleteSynonym(head, word, synonym);
                break;
            case 5:
                cout << "Enter the word you want to search:" << endl;
                cin >> word;
                searchWord(head, word);
                break;
            case 6:
                saveDictionary(head);
                cntrl=7;
                break;
        }
    }
    return 0;
}
//Coded by Arshia