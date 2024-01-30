// Compatibility: Ensure functionality on VS Code Terminal and Code::Blocks.

// Word list: Employs lowercase-only English words from a CSV dictionary.

// Objective: Generates all word permutations without repetition and validates them against the dictionary.

// Efficiency concerns: Current algorithm exhibits high time complexity for large datasets.

// Future exploration: Potential performance improvements via dictionary's word trees implementation (in progress).

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

    // Definition of constants "length, size.."

#define ALPHABET_SIZE 26
#define MAX_WORD_LENGTH 8
#define MAX_LINE_LENGTH 4319

char ChosenChars[MAX_WORD_LENGTH];
char LongestWord[MAX_WORD_LENGTH];
char *vowels = "aeiou";
char *consonants = "bcdfghjklmnpqrstvwxyz";

    // Define a structure for a binary tree node..

typedef struct node {
    char word[MAX_WORD_LENGTH];
    struct node *left, *right;
} Node;

    // Functions declaration..

Node* new_node(char*);
Node* insert(Node*, char*);
Node* search(Node*, char*);
void draw_random_chars(int);
void quick_sort_chars(char [], int , int);
int partition(char [], int, int);
void swap(char*, char*);
void generate_permutations(int, int, int, char **, int, int * , Node**);
char **read_CSV_file(char*, int*);
bool is_word_in_dictionary(char*, char**, int);
void delete(char** , int );
void game(int, char **);
    
    // Main fonction..

int main() {
    int NumWords;
    char **word = read_CSV_file("most.csv", &NumWords);
    
    // Start the game
    game(NumWords, word);

    delete(word, NumWords);

    return 0;
}

void game(int NumWords, char **Word) {
    int NumVowel;
    printf("\n\n\t\t\t-|||WELCOM TO *LONGEST_WORD* GAME|||-\n");
    printf("\n\tPlease provide the number of vowels: ");
    scanf("%d", &NumVowel);
    while (NumVowel < 0 || NumVowel > MAX_WORD_LENGTH - 1) {
        printf("\n |Please choose your numbers between 0 and %d..|\n\n  \t  | number of vowels: ", MAX_WORD_LENGTH - 1);
        scanf("%d",&NumVowel);
    }

    draw_random_chars(NumVowel);
    quick_sort_chars(ChosenChars, 0, MAX_WORD_LENGTH - 2);

    int NumberOfLongWords = 0;
    Node *root = NULL;
    generate_permutations(0, MAX_WORD_LENGTH - 2, NumVowel, Word, NumWords, &NumberOfLongWords, &root);

    if (strlen(LongestWord) > 0) {
        printf("\n");
        printf("\n\t\033[1;0m\033[1;36m* Longest Word found: | %s | *\033[1;0m\n\n", LongestWord);
    } else {
        printf("\n");
        printf("\n\t\033[1;31m!* There is no Longest Word *!\033[1;0m\n\n");
    }
}

    // Function to create a new binary tree node..

Node* new_node(char *word) {
    Node* node = (Node*)malloc(sizeof(Node));
    strcpy(node->word, word);
    node->left = node->right = NULL;
    return node;
}

    // Function to insert a word into the binary tree..

Node* insert(Node* node, char *word) {
    if (node == NULL) { return new_node(word); }
    int cmp = strcmp(word, node->word);
    if (cmp < 0) {
        node->left  = insert(node->left, word);
    } else if (cmp > 0) {
        node->right = insert(node->right, word);
    }
    return node;
}

    // Function to search for a word in the binary tree..

Node* search(Node* root, char *word) {
    while (root != NULL) {
        int cmp = strcmp(word, root->word);
        if (cmp < 0) {
            root = root->left;
        } else if (cmp > 0) {
            root = root->right;
        } else {
            return root;
        }
    }
    return NULL;
}

    // Function to randomly draw characters..

void draw_random_chars(int NumVowel) {
    srand(time(NULL));
    for (int i = 0; i < MAX_WORD_LENGTH - 1; i++) {
        if (i < NumVowel) {
            ChosenChars[i] = vowels[rand() % 5];
        } else {
            ChosenChars[i] = consonants[rand() % 21];
        }
    }
    ChosenChars[MAX_WORD_LENGTH - 1] = '\0';
}

    // Function to perform quicksort on an array of characters..

void quick_sort_chars(char arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quick_sort_chars(arr, low, pi - 1);
        quick_sort_chars(arr, pi + 1, high);
    }
}

    // Function to partition an array of characters for quicksort..

int partition(char arr[], int low, int high) {
    char pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

    // Function to swap two characters..

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

    // Function to generate permutations of characters and search in the dictionary..

void generate_permutations(int start, int end, int NumVowel, char **word, int NumWords, int *NumberOfLongWords, Node **root) {
    if (start == end) {
        for (int len = end; len >= 2; len--) {
            char temp[len + 1];
            strncpy(temp, ChosenChars, len);
            temp[len] = '\0';
            if (search(*root, temp) == NULL) {
                *root = insert(*root, temp);
                printf("\n\033[1;32m! RANDOMLY DRAWN LETTERS LOADING.. !\n\n\t   |%s  |", temp);
                system("cls");
                if (is_word_in_dictionary(temp, word, NumWords)) {
                    if (strlen(temp) > strlen(LongestWord)) {
                        strcpy(LongestWord, temp);
                        *NumberOfLongWords = 1;
                    }
                    else if (strlen(temp) == strlen(LongestWord)) {
                        (*NumberOfLongWords)++;
                    }
                }
            }
        }
    } else {
        for (int i = start; i <= end; i++) {
            char temp = ChosenChars[start];
            ChosenChars[start] = ChosenChars[i];
            ChosenChars[i] = temp;
            generate_permutations(start + 1, end, NumVowel, word, NumWords, NumberOfLongWords, root);
            temp = ChosenChars[start];
            ChosenChars[start] = ChosenChars[i];
            ChosenChars[i] = temp;
        }
    }
}

    // Function to read a CSV file and return an array of words..

char **read_CSV_file(char *filename, int *NumWords) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return NULL;
    }

    char buffer[MAX_LINE_LENGTH];
    char *headerLine = fgets(buffer, MAX_LINE_LENGTH, fp);

    int numLines = 0;
    while (fgets(buffer, MAX_LINE_LENGTH, fp) != NULL) {
        numLines++;
    }

    char **words = malloc(numLines * sizeof(char *));
    rewind(fp);

    fgets(buffer, MAX_LINE_LENGTH, fp);

    for (int i = 0; i < numLines; i++) {
        words[i] = malloc(MAX_LINE_LENGTH * sizeof(char));
        fgets(words[i], MAX_LINE_LENGTH, fp);
        strtok(words[i], "\n");
    }

    fclose(fp);

    *NumWords = numLines;
    return words;
}

    // Function to check if a word is in the dictionary..

bool is_word_in_dictionary(char *word, char **Word, int NumWords) {
    for (int i = 0; i < NumWords; i++) {
        if (strcmp(word, Word[i]) == 0) {
            return true;
        }
    }
    return false;
}

    // Fonction to delete an array of words..

void delete(char **Word, int NumWords)
{
    for (int i = 0; i < NumWords; i++) {
        free(Word[i]);
    }

    free(Word);
}
