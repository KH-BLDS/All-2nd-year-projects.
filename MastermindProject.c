#include <stdio.h>
#include <stdlib.h>
 
    // Definition of constants "pawns, colors, attempts" numbers..

#define NUM_PAWNS 5
#define NUM_COLORS 8
#define NUM_ATTEMPTS 10

    // Enum representing different colors..

enum color_t{RED, GREEN, BLUE, YELLOW, BLACK, WHITE, GRAY, PURPLE};
const char*colors[] = { "RED", "GREEN", "BLUE", "YELLOW", "BLACK","WHITE", "GRAY", "PURPLE"};

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
    printf("\n\t\t\t---------- *** The liste of numbers & colors *** ----------\n\n\t\t\t\t|0: RED.\t\t\t|1: GREEN.\n\
    \t\t\t\t|2: BLUE.\t\t\t|3: YELLOW.\n\t\t\t\t|4: BLACK.\t\t\t|5: WHITE.\n\t\t\t\t|6: GRAY.\t\t\t|7: PURPLE.\n");
    
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
    printf("\n\t\t\t---------- *** The liste of numbers & colors *** ----------\n\n\t\t\t\t|0: RED.\t\t\t|1: GREEN.\n\
    \t\t\t\t|2: BLUE.\t\t\t|3: YELLOW.\n\t\t\t\t|4: BLACK.\t\t\t|5: WHITE.\n\t\t\t\t|6: GRAY.\t\t\t|7: PURPLE.\n");
    
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
    printf("\n\t\t\t   *******************************");
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
        printf("\n\t\t|Well placed pawns: %i|\t ---\t" ,*NWPP);
        printf("|Misplaced pawns: %i|\n" ,*NMP);
        if (*NWPP == NUM_PAWNS) {
            printf("\n\t\t\t<< Awesome! YOU WON THE GAME >>\n\
            \t\t\tYeah you got it...\n\n ** The hidden combinition was: \n");
        
        // Display the hidden combinition..
        for (int i = 0; i < NUM_PAWNS; i++) {     
            printf("\t\t\t\t\t|%d: ", H_C[i]);
            printf("%s.\n", colors[H_C[i]]);
        }
            return;
        } else { printf("\n ** |%d| attempts left!!!\n", NUM_ATTEMPTS - i); }
        i++;
        *NWPP = 0;
        *NMP = 0;
    }
    if (i == NUM_ATTEMPTS + 1) {
        printf("\n\t\t>>  Oops!! YOU LOST THE GAME <<\n\
        \t\tYou were imminent!\n\n ** This is the hidden combinition: \n");
        
        for (int i = 0; i < NUM_PAWNS; i++) {     
            printf("\t\t\t\t\t|%d: ", H_C[i]);
            printf("%s.\n", colors[H_C[i]]);
        }
        return;
    }
}
