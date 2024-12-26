#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_WORD_LEN 15
#define MAX_CHANCES 7

// Function to display the hangman based on remaining chances
void display_hangman(int chances) {
    switch (chances) {
        case 7: printf("____\n\n"); break;
        case 6: printf("  |  \n  |  \n  |  \n  |  \n__|__\n\n"); break;
        case 5: printf("  ____\n  |  \n  |  \n  |  \n  |  \n__|__\n\n"); break;
        case 4: printf("  ____\n  |/  \n  |  \n  |  \n  |  \n__|__\n\n"); break;
        case 3: printf("  ____\n  |/ |\n  |  \n  |  \n  |  \n__|__\n\n"); break;
        case 2: printf("  ____\n  |/ |\n  |  O\n  |  \n  |  \n__|__\n\n"); break;
        case 1: printf("  ____\n  |/ |\n  |  O\n  |  |\n  |  \n__|__\n\n"); break;
        case 0: printf("  ____\n  |/ |\n  |  O\n  | /|\\\n  | / \\\n__|__\n\n"); break;
    }
}

// Function to select a random word from the file
void get_random_word(char *filename, char *word) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Count lines in the file
    int line_count = 0;
    char temp[MAX_WORD_LEN];
    while (fgets(temp, sizeof(temp), fp) != NULL) {
        line_count++;
    }

    // Select a random line
    srand(time(NULL));
    int random_line = rand() % line_count;

    // Retrieve the random word
    rewind(fp);
    for (int i = 0; i <= random_line; i++) {
        fgets(word, MAX_WORD_LEN, fp);
    }

    // Remove the newline character
    word[strcspn(word, "\n")] = '\0';
    fclose(fp);
}

int main() {
    char word[MAX_WORD_LEN]; // The random word
    get_random_word("/Users/mac/Desktop/CTest/words.txt", word);
    int word_len = strlen(word);

    printf("Welcome to Hangman! You have %d chances to guess the word.\n", MAX_CHANCES);
    printf("If you guess wrong too many times, you'll get hanged!\n");
    printf("You can also type \"MyGuess\" to guess the word directly.\n");

    int chances = MAX_CHANCES;
    char guessed_letters[word_len + 1];
    for (int i = 0; i < word_len; i++) {
        guessed_letters[i] = '_';
    }
    guessed_letters[word_len] = '\0';

    while (chances > 0) {
        printf("\nCurrent word: %s\n", guessed_letters);
        printf("Guess a letter: ");
        char guess[MAX_WORD_LEN];
        scanf("%s", guess);
        guess[strcspn(guess, "\n")] = '\0';
        printf("\nGuess : %s\n", guess);

        if (strcasecmp(guess, "MyGuess") == 0) {
            char user_guess[MAX_WORD_LEN];
            printf("Enter your guess for the word: ");
            scanf(" %s", user_guess);
            user_guess[strcspn(user_guess, "\n")] = '\0';

            if (strcasecmp(user_guess, word) == 0) {
                printf("Congratulations! You guessed the word: %s\n", word);
                return 0;
            } else {
                printf("Wrong guess! You lose.\n");
                break;
            }
        }

        char letter = tolower(guess[0]);
        if (!isalpha(letter) || strlen(guess) > 1) {
            printf("Please enter a single valid letter.\n");
            continue;
        }

        int correct = 0;
        for (int i = 0; i < word_len; i++) {
            if (tolower(word[i]) == letter && guessed_letters[i] == '_') {
                guessed_letters[i] = word[i];
                correct = 1;
            }
        }

        if (!correct) {
            chances--;
            printf("Incorrect guess. Remaining chances: %d\n", chances);
            display_hangman(chances);
        } else {
            printf("Correct guess!\n");
        }

        if (strcmp(guessed_letters, word) == 0) {
            printf("You win! The word was: %s\n", word);
            return 0;
        }
    }

    display_hangman(0);
    printf("You lose! The word was: %s\n", word);
    return 0;
}
