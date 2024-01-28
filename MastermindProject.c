#include <stdio.h>
#include <stdlib.h>
 
    // Definition of constants "pawns, colors, attempts" numbers..

#define NUM_PAWNS 5
#define NUM_COLORS 8
#define NUM_ATTEMPTS 10

    // Enum representing different colors..

enum color_t{RED, GREEN, BLUE, YELLOW, BLACK, WHITE, PURPLE, CYAN};
const char*colors[] = { "\033[1;31m RED", "\033[1;32m GREEN", "\033[1;34m BLUE", "\033[1;33m YELLOW", "\033[1;30m BLACK","\033[1;37m WHITE", "\033[1;35m PURPLE", "\033[1;36m CYAN"};

    // Type definition for the game board..

typedef enum color_t board[NUM_PAWNS];

    // Functions declaration..

void generate_hidden_combination(enum color_t*);
void read_proposed_combination(enum color_t*);
void evaluate_proposed_combination(enum color_t *, enum color_t *, int *, int *);
void Game(enum color_t [], enum color_t [], int *, int *);

    // Main fonction..

int main() {
    int NumWellPlacedPawns = 0, NumMisplacedPawns = 0;
    enum color_t ProposedCombination[NUM_PAWNS];
    enum color_t HiddenCombination[NUM_PAWNS];
    printf("\n\n\t\t\t-|||WELCOM TO MASTERMIND GAME|||-\n");
    
    // Start the game
    Game(HiddenCombination, ProposedCombination, &NumWellPlacedPawns, &NumMisplacedPawns);    
    return 0;
}

    // Function to generate a hidden combination Manually (commented out)..

/*void generate_hidden_combination(enum color_t board[]) {
    
    // Manual input for the game testing purposes..
    board[0] = RED;
    board[1] = GREEN;
    board[2] = BLUE;
    board[3] = YELLOW;
    board[4] = BLACK;
}*/

void generate_hidden_combination(enum color_t board[]) {
    
    // Code to generate a random combination (commented out)..
    /*for (int i = 0; i < NUM_PAWNS; i++) {
        board[i] = rand() % NUM_COLORS;
    }*/

    // Manual input for interactive game purposes..
    printf("\n\t++ The 1st player's part (codebreaker) ..\n\n");
    printf("\033[1;31m"); printf("\n\n\t\t\t\t|0: RED."); printf("\033[1;32m"); printf("\t\t\t|1: GREEN.");
    printf("\033[1;34m"); printf("\n\t\t\t\t|2: BLUE."); printf("\033[1;33m"); printf("\t\t\t|3: YELLOW.");
    printf("\033[1;30m"); printf("\n\t\t\t\t|4: BLACK."); printf("\033[1;37m"); printf("\t\t\t|5: WHITE.");
    printf("\033[1;35m"); printf("\n\t\t\t\t|6: PURPLE."); printf("\033[1;36m"); printf("\t\t\t|7: CYAN.\n");
    printf("\033[0m");
    printf("\n\t* Please insert the %d numbers of the colors for the hidden combination:\n\n", NUM_PAWNS);
    enum color_t Num;
    for (int i = 0; i < NUM_PAWNS; i++) {
        printf("\t  | Color %d :",i + 1);
        scanf("%d",&Num);  
        while (Num < 0 || Num > NUM_COLORS - 1) {
            printf("\n |Please choose your numbers between 0 and %d..|\n\n  \t  | Color %d :", NUM_COLORS - 1, i + 1);
            scanf("%d",&Num);
        }
        board[i] = Num;
    }
    system("cls");// Clear screen on Windows
}

    // Function to read a proposed combination from the player..

void read_proposed_combination(enum color_t board[]) {
    printf("\033[1;31m"); printf("\n\n\t\t\t\t|0: RED."); printf("\033[1;32m"); printf("\t\t\t|1: GREEN.");
    printf("\033[1;34m"); printf("\n\t\t\t\t|2: BLUE."); printf("\033[1;33m"); printf("\t\t\t|3: YELLOW.");
    printf("\033[1;30m"); printf("\n\t\t\t\t|4: BLACK."); printf("\033[1;37m"); printf("\t\t\t|5: WHITE.");
    printf("\033[1;35m"); printf("\n\t\t\t\t|6: PURPLE."); printf("\033[1;36m"); printf("\t\t\t|7: CYAN.\n");
    printf("\033[0m");
 
    printf("\n\t* Please insert the %d numbers of the colors for your guess:\n\n", NUM_PAWNS);
    enum color_t Num;
    for (int i = 0; i < NUM_PAWNS; i++) {
        printf("\t  | Color %d :",i + 1);
        scanf("%d",&Num);  
        while (Num < 0 || Num > NUM_COLORS - 1) {
            printf("\n |Please choose your numbers between 0 and %d..|\n\n  \t  | Color %d :", NUM_COLORS - 1, i + 1);
            scanf("%d",&Num);
        }
        board[i] = Num;
    }
    printf("\n\t\t\t\t\t \033[1;37m*******************************");
}

    // Function to evaluate the proposed combination against the hidden combination..

void evaluate_proposed_combination(enum color_t *hidden_combination, enum color_t *proposed_combination, int *num_well_placed_pawns, int *num_misplaced_pawns) {
    for (int k = 0; k < NUM_PAWNS; k++) {
        if (proposed_combination[k] == hidden_combination[k]) {
            (*num_well_placed_pawns) ++;
        } else {
            for (int t = 0; t < NUM_PAWNS; t++) {
                if (proposed_combination[k] == hidden_combination[t]) {
                    (*num_misplaced_pawns) ++;
                    break;
                }
            }
        }
    }  
}

    // Main game function..

void Game(enum color_t H_C[], enum color_t P_C[], int* NWPP, int* NMP) {
    int i = 1;
    
    generate_hidden_combination(H_C);
    
    printf("\n\t++ The 2nd player's part ..\n\n");
    while (i <= NUM_ATTEMPTS && *NWPP < NUM_PAWNS) {
        
        read_proposed_combination(P_C);
        evaluate_proposed_combination(H_C, P_C, NWPP, NMP);
        
        // Display feedback..
        printf("\n\t\t\t   \033[1;33m|Well placed pawns: %i|\t ---\t" ,*NWPP);
        printf("\033[1;31m |Misplaced pawns: %i| \033[1;37m\n" ,*NMP);
        if (*NWPP == NUM_PAWNS) {
            printf("\n\t\t\t\t\t \033[1;32m<< Awesome! YOU WON THE GAME >>\n\
            \n\t\t\t\t\t\t Yeah you got it...\n\n \033[1;30m** The hidden combinition was: \033[1;0m\n");
        
        // Display the hidden combinition..
        for (int i = 0; i < NUM_PAWNS; i++) {     
            printf("\t\t\t\t\t|%d: ", H_C[i]);
            printf("%s.\033[1;0m\n", colors[H_C[i]]);
        }
            return;
        } else { printf("\n\033[1;30m ** |%d| attempts left!!!\033[1;0m\n", NUM_ATTEMPTS - i); }
        i++;
        *NWPP = 0;
        *NMP = 0;
    }
    if (i == NUM_ATTEMPTS + 1) {
        printf("\n\t\t\t\t\t \033[1;31m>>  Oops!! YOU LOST THE GAME <<\n\
        \n\t\t\t\t\t\t You were imminent!\n\n \033[1;30m** This is the hidden combinition: \033[1;0m\n");
        
        for (int i = 0; i < NUM_PAWNS; i++) {     
            printf("\t\t\t\t\t|%d: ", H_C[i]);
            printf("%s.\033[1;0m\n", colors[H_C[i]]);
        }
        return;
    }
}
