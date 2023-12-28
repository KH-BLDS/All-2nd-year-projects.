#include <stdio.h>
#include <stdlib.h>

#define NUM_PAWNS 3
#define NUM_COLORS 8
#define NUM_ATTEMPTS 10

enum color_t{RED, GREEN, BLUE, YELLOW, BLACK, WHITE, GRAY, PURPLE};
const char*colors[] = { "RED", "GREEN", "BLUE", "YELLOW", "BLACK","WHITE", "GRAY", "PURPLE"};

typedef enum color_t board[NUM_PAWNS];

void generate_hidden_combination(enum color_t*);
void read_proposed_combination(enum color_t*);
void evaluate_proposed_combination(enum color_t *, enum color_t *, int *, int *);
void Game(enum color_t [], enum color_t [], int *, int *);

int main() {
    int NumWellPlacedPawns = 0, NumMisplacedPawns = 0;
    enum color_t ProposedCombination[NUM_PAWNS];
    enum color_t HiddenCombination[NUM_PAWNS];
    Game(HiddenCombination, ProposedCombination, &NumWellPlacedPawns, &NumMisplacedPawns);
    return 0;
}

/*void generate_hidden_combination(enum color_t board[]) {
    board[0] = RED;
    board[1] = GREEN;
    board[2] = BLUE;
    board[3] = YELLOW;
    board[4] = BLACK;
}*/

void generate_hidden_combination(enum color_t board[]) {
    /*for (int i = 0; i < NUM_PAWNS; i++) {
        board[i] = rand() % NUM_COLORS;
    }*/
    printf("\n\t++The 1st player's part (codemaker) ..\n\n");
    printf("\n\t\t\t---------- *** The liste of numbers & colors *** ----------\n\n\t\t\t\t|0: RED.\t\t\t|1: GREEN.\n\
    \t\t\t\t|2: BLUE.\t\t\t|3: YELLOW.\n\t\t\t\t|4: BLACK.\t\t\t|5: WHITE.\n\t\t\t\t|6: GRAY.\t\t\t|7: PURPLE.\n");
    
    printf("\n\t**Please insert the %d numbers of the colors you proposed for your frend:\n\n", NUM_PAWNS);
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
    system("cls");
}

void read_proposed_combination(enum color_t board[]) {
    printf("\n\t++The 2nd player's part..\n\n");
    printf("\n\t\t\t---------- *** The liste of numbers & colors *** ----------\n\n\t\t\t\t|0: RED.\t\t\t|1: GREEN.\n\
    \t\t\t\t|2: BLUE.\t\t\t|3: YELLOW.\n\t\t\t\t|4: BLACK.\t\t\t|5: WHITE.\n\t\t\t\t|6: GRAY.\t\t\t|7: PURPLE.\n");
    
    printf("\n\t**Please insert the %d numbers of the colors you chose:\n\n", NUM_PAWNS);
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
}

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

void Game(enum color_t H_C[], enum color_t P_C[], int* NWPP, int* NMP) {
    int i = 1;
    generate_hidden_combination(H_C);
    while (i <= NUM_ATTEMPTS && *NWPP < NUM_PAWNS) {
        
        read_proposed_combination(P_C);
        evaluate_proposed_combination(H_C, P_C, NWPP, NMP);
        
        printf("\n\t|Number well placed pawns: %i|\t ---\t" ,*NWPP);
        printf("|Number misplaced pawns: %i|\n" ,*NMP);
        if (*NWPP == NUM_PAWNS) {
            printf("\n\t\t\t<< Awesome! YOU WON THE GAME >>\n\
            \t\t\tYeah you got it...\n\n ** This is the hidden combinition: \n");
        
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