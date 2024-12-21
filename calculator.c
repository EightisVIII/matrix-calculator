#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <conio.h>

int *resultSingle, **resultPoly, **resultIdentity, **resultInv, resultDet;
int *matrixSingleElementA, *matrixSingleElementB;
int **matrixPolyElementA, **matrixPolyElementB;

// OPERATION FUNCTIONS
int **identityMatrix(int row, int col);
int *addSingleMatrix(int *arr, int *arr2, int n);
int **addPolyMatrix(int **arr, int **arr2, int row, int col);
int *subSingleMatrix(int *arr, int *arr2, int n);
int **subPolyMatrix(int **arr, int **arr2, int row, int col);
int *multSingleMatrix(int *arr, int *arr2, int n);
int **multPolyMatrix(int **arr, int **arr2, int row, int col);
int **scalarPolyMatrix(int **arr, int s, int row, int col);
int **invMatrix(int **arr, int **arr2, int row, int col);
int detMatrix(int **arr, int row, int col);

// PRINTING FUNCTIONS
void detMatrix0(int row, int col);
void invMatrix0(int row, int col);
void multMatrix0(int row, int col, int s);
void addMatrix1(int n);
void subMatrix1(int n);
void multMatrix1(int n);
void addMatrix2(int row, int col);
void subMatrix2(int row, int col);
void multMatrix2(int row, int col);

// HELPER FUNCTIONS
void freeMatrix(int **arr, int row);
void nullMessage(int row);

void decorBlue(){
    printf("\033[0;34m");
}

void resetColor(){
    printf("\033[0;37m");
}

void mainMenu(){
    printf("\t\t\t\t\t--------------------------------");
    printf("\n\t\t\t\t\t       MATRIX CALCULATOR\n");
    printf("\t\t\t\t\t      made by EightisVIII\n");
    printf("\t\t\t\t\t--------------------------------");

    printf("\n\n\t\t\t\t\t   -------- SELECTION --------");
    printf("\n\t\t\t\t\t     1. Add Matrix");
    printf("\n\t\t\t\t\t     2. Subtract Matrix");
    printf("\n\t\t\t\t\t     3. Multiply Matrix");
    printf("\n\t\t\t\t\t     4. Find Matrix Inverse");
    printf("\n\t\t\t\t\t     5. Find Matrix Determinant");
    printf("\n\t\t\t\t\t     6. Quit Program");
    printf("\n\t\t\t\t\t   ---------------------------");
}

void matrixSelectionScr(int userChoice){
    system("cls");
    printf("\t\t\t\t\t--------------------------------");
    if(userChoice == 1){
        printf("\n\t\t\t\t\t      ADDITION OF MATRIX\n");
    }
    else if(userChoice == 2){
        printf("\n\t\t\t\t\t     SUBTRACTION OF MATRIX\n");
    }
    else if(userChoice == 3){
        printf("\n\t\t\t\t\t    MULTIPLICATION OF MATRIX\n");
    }
    else if(userChoice == 4){
        printf("\n\t\t\t\t\t        INVERSE OF MATRIX\n");
    }
    else{
        printf("\n\t\t\t\t\t     DETERMINANT OF MATRIX\n");
    }
    printf("\t\t\t\t\t--------------------------------");

    printf("\n\n\t\t\t\t\t   ------- SELECTION -------");
    if(userChoice == 3){
        printf("\n\t\t\t\t\t     0. Scalar Multiplication");
    }
    printf("\n\t\t\t\t\t     1. Singular Matrix");
    printf("\n\t\t\t\t\t     2. Multidimensional Matrix");
    printf("\n\t\t\t\t\t     3. Return to Main Menu");
    printf("\n\t\t\t\t\t     4. Quit Program");
    printf("\n\t\t\t\t\t   -------------------------");
}

int main(){
    int userChoice, matrixChoice;
    int row, col, elem;
    int scalar; // FOR SCALAR MULTIPLICATION
    bool repeatQues = true, repeatQues0 = true;

  while(1){
   repeatQues0 = true;

   do{
    system("cls");
    mainMenu();
    printf("\n\n\t\t\t\t\t     Enter your choice: ");
    scanf("%d", &userChoice);

    if(userChoice < 1 || userChoice > 6){
        getchar();
        printf("\n\t\t\t\t    ERROR: Incorrect input. Please try again.\n");
        getch();
        repeatQues = true;
    } else{
        repeatQues = false;
    }
   } while(repeatQues);

  if(userChoice != 6){
   do{
    matrixSelectionScr(userChoice);
    printf("\n\n\t\t\t\t\t     Enter your choice: ");
    scanf("%d", &matrixChoice);

    if(matrixChoice == 1){
        if(userChoice == 4){
            printf("\n\n\t\t\t\tERROR: An inverted matrix can't be a singular matrix. Please try again.");
            repeatQues0 = true;
        } else if(userChoice == 5){
            printf("\n\n\t\t\t\tERROR: A matrix determinant can't be solved with a singular matrix. Please try again.");
            repeatQues0 = true;
        }
        repeatQues0 = false;
        printf("\n\t\t\t\t\t   ------ INPUT VALUES ------");
        printf("\n\t\t\t\t\tHow many elements in your matrix? ");
        decorBlue();
        scanf("%d", &elem);
        resetColor();
    } else if((matrixChoice == 2) ||
              (userChoice == 3 && matrixChoice == 0)){
        repeatQues0 = false;
        if(userChoice == 4 || userChoice == 5){
            printf("\t\t\t\t\t   ------ INPUT VALUES ------");
            printf("\n\t\t\t\t\tHow many rows-by-columns(nxn)? ");
            decorBlue();
            scanf("%d", &row);
            resetColor();
            col = row;
        } else{
            printf("\t\t\t\t\t   ------ INPUT VALUES ------");
            printf("\n\t\t\t\t\t        How many rows? ");
            decorBlue();
            scanf("%d", &row);
            resetColor();

            printf("\t\t\t\t\t      How many columns? ");
            decorBlue();
            scanf("%d", &col);
            resetColor();
        }
    } else if(matrixChoice == 3){
        repeatQues0 = false;
        repeatQues = true;
        break;
    } else if(matrixChoice == 4){
        exit(0);
    } else{
        getchar();
        printf("\n\t\t\t\t    ERROR: Incorrect input. Please try again.\n");
        getch();
        repeatQues0 = true;
    }
   } while(repeatQues0);
  }

    if(repeatQues){
        continue;
    }

    if(matrixChoice == 1){
        // SINGULAR
        matrixSingleElementA = (int *)malloc(elem * sizeof(int));
        matrixSingleElementB = (int *)malloc(elem * sizeof(int));
        if(matrixSingleElementA == NULL || matrixSingleElementB == NULL){
            nullMessage(row);
        }

        printf("\n\t\t\t\t\t   Enter %d elements for Matrix A:\n", elem);

        for(int i = 0; i < elem; i++){
            printf("\t\t\t\t\t[%d] = ", i);
            decorBlue();
            scanf("%d", &matrixSingleElementA[i]);
            resetColor();
        }

        printf("\t\t\t\t\t   Enter %d elements for Matrix B:\n", elem);

        for(int j = 0; j < elem; j++){
            printf("\t\t\t\t\t[%d] = ", j);
            decorBlue();
            scanf("%d", &matrixSingleElementB[j]);
            resetColor();
        }
    } else if(matrixChoice == 2 && userChoice == 5){
        // FOR DETERMINANT
        matrixPolyElementA = (int **)malloc(row * sizeof(int *));
        if(matrixPolyElementA == NULL){
            nullMessage(row);
        }

        printf("\n\t\t\t\t\tEnter %d elements for Matrix A:\n", row * col);

        for(int i = 0; i < row; i++){
            matrixPolyElementA[i] = (int *)malloc(col * sizeof(int));
            if(matrixPolyElementA[i] == NULL){
              nullMessage(row);
            }

            for(int j = 0; j < col; j++){
                printf("\t\t\t\t\t[%d][%d] = ", i, j);
                decorBlue();
                scanf("%d", &matrixPolyElementA[i][j]);
                resetColor();
            }
        }
    } else{
        // MULTIDIMENSIONAL
        matrixPolyElementA = (int **)malloc(row * sizeof(int *));
        matrixPolyElementB = (int **)malloc(row * sizeof(int *));
        if(matrixPolyElementA == NULL || matrixPolyElementB == NULL){
            nullMessage(row);
        }

        printf("\n\t\t\t\t\tEnter %d elements for Matrix A:\n", row * col);

        for(int i = 0; i < row; i++){
            matrixPolyElementA[i] = (int *)malloc(col * sizeof(int));
            if(matrixPolyElementA[i] == NULL){
              nullMessage(row);
            }

            for(int j = 0; j < col; j++){
                printf("\t\t\t\t\t[%d][%d] = ", i, j);
                decorBlue();
                scanf("%d", &matrixPolyElementA[i][j]);
                resetColor();
            }
        }

        if(matrixChoice == 0){
            printf("\n\t\t\t\t\tEnter a number to multiply Matrix A with: ");
            decorBlue();
            scanf("%d", &scalar);
            resetColor();
        } else{
            printf("\n\t\t\t\t\tEnter %d elements for Matrix B:\n", row * col);

            for(int x = 0; x < row; x++){
                matrixPolyElementB[x] = (int *)malloc(col * sizeof(int));
                if(matrixPolyElementB[x] == NULL){
                    nullMessage(row);
                 }

                for(int y = 0; y < col; y++){
                    printf("\t\t\t\t\t[%d][%d] = ", x, y);
                    decorBlue();
                    scanf("%d", &matrixPolyElementB[x][y]);
                    resetColor();
                }
            }
        }
        printf("\t\t\t\t\t----------------------------------");
    }

    switch(userChoice){
        case 1:
            repeatQues = false;
            printf("\033[H\033[J");
            printf("\n\n\t\t\t------------------------ ADDITION OF MATRIX ------------------------");
            decorBlue();
            printf("\n\n\t\t\t\t\tYour equation: ");
            resetColor();
            if(matrixChoice == 1){
                addMatrix1(elem);
                free(matrixSingleElementA);
                free(matrixSingleElementB);
                free(resultSingle);
            }
            else if(matrixChoice == 2){
                addMatrix2(row, col);
                freeMatrix(matrixPolyElementA, row);
                freeMatrix(matrixPolyElementB, row);
                freeMatrix(resultPoly, row);
            }
            printf("\n\t\t\t--------------------------------------------------------------------");
            getch();
            break;
        case 2:
            repeatQues = false;
            printf("\033[H\033[J");
            printf("\n\n\t\t\t------------------------ SUBSTRACTION OF MATRIX ------------------------");
            decorBlue();
            printf("\n\n\t\t\t\t\tYour equation: ");
            resetColor();
            if(matrixChoice == 1){
                subMatrix1(elem);
                free(matrixSingleElementA);
                free(matrixSingleElementB);
                free(resultSingle);
            }
            else if(matrixChoice == 2){
                subMatrix2(row, col);
                freeMatrix(matrixPolyElementA, row);
                freeMatrix(matrixPolyElementB, row);
                freeMatrix(resultPoly, row);
            }
            printf("\n\t\t\t-----------------------------------------------------------------------");
            getch();
            break;
        case 3:
            repeatQues = false;
            printf("\033[H\033[J");
            printf("\n\n\t\t\t------------------------ MULTIPLICATION OF MATRIX ------------------------");
            decorBlue();
            printf("\n\n\t\t\t\t\tYour equation: ");
            resetColor();
            if(matrixChoice == 0){
                multMatrix0(row, col, scalar);
                freeMatrix(matrixPolyElementA, row);
                freeMatrix(resultPoly, row);
            }
            else if(matrixChoice == 1){
                multMatrix1(elem);
                free(matrixSingleElementA);
                free(matrixSingleElementB);
                free(resultSingle);
            }
            else if(matrixChoice == 2){
                multMatrix2(row, col);
                freeMatrix(matrixPolyElementA, row);
                freeMatrix(matrixPolyElementB, row);
                freeMatrix(resultPoly, row);
            }
            printf("\n\t\t\t--------------------------------------------------------------------------");
            getch();
            break;
        case 4:
            repeatQues = false;
            printf("\033[H\033[J");
            printf("\n\n\t\t\t------------------------ INVERSE OF MATRIX ------------------------");
            decorBlue();
            printf("\n\n\t\t\t\t\tYour equation: ");
            resetColor();
            invMatrix0(row, col);
            freeMatrix(matrixPolyElementA, row);
            freeMatrix(matrixPolyElementB, row);
            freeMatrix(resultInv, row);
            free(resultIdentity);
            printf("\n\t\t\t--------------------------------------------------------------------");
            getch();
            break;
        case 5:
            repeatQues = false;
            printf("\033[H\033[J");
            printf("\n\n\t\t\t------------------------ DETERMINANT OF MATRIX ------------------------");
            decorBlue();
            printf("\n\n\t\t\t\t\tYour equation: ");
            resetColor();
            detMatrix0(row, col);
            freeMatrix(matrixPolyElementA, row);
            printf("\n\t\t\t-----------------------------------------------------------------------");
            getch();
            break;
        case 6:
            exit(0);
            break;
    }
  }

  return 0;
}

void freeMatrix(int **arr, int row){
    for(int i = 0; i < row; i++){
        free(arr[i]);
    }
    free(arr);
}

void nullMessage(int row){
    free(matrixSingleElementA);
    free(matrixSingleElementB);
    for(int i = 0; i < row; i++){
        free(matrixPolyElementA[i]);
        free(matrixPolyElementB[i]);
    }
    free(matrixPolyElementA);
    free(matrixPolyElementB);
    printf("\n\t\t\t\t\t\t\tERROR: Memory allocation failed.\n");
    exit(1);
}

int **identityMatrix(int row, int col){
    resultIdentity = (int **)malloc(row * sizeof(int *));

    if(resultIdentity == NULL){
        nullMessage(row);
    }

    for(int i = 0; i < row; i++){
        resultIdentity[i] = (int *)malloc(col * sizeof(int));

        if(resultIdentity[i] == NULL){
            nullMessage(row);
        }
        for(int j = 0; j < col; j++){
            if(i == j){
                resultIdentity[i][j] = 1;
            } else{
                resultIdentity[i][j] = 0;
            }
        }
    }

    return resultIdentity;
}

void invMatrix0(int row, int col){
    identityMatrix(row, col);

    for(int i = 0; i < row; i++){
        printf("{ ");
        for(int j = 0; j < col; j++){
            printf("%d ", matrixPolyElementA[i][j]);
        }
        printf("}");

        if(i == 0){
            printf(" * ");
        } else{
            printf("   ");
        }

        printf("{ ");
        for(int j = 0; j < col; j++){
            printf("%d ", matrixPolyElementB[i][j]);
        }
        printf("}");

        if(i == 0){
            printf(" = ");
        } else{
            printf("   ");
        }

        printf("{ ");
        for(int j = 0; j < col; j++){
            printf("%d ", resultIdentity[i][j]);
        }
        printf("}");
        printf("\n\t\t\t\t\t\t       ");
    }

    invMatrix(matrixPolyElementA, matrixPolyElementB, row, col);

    decorBlue();
    printf("\n\t\t\t\t\tAnswer: ");
    resetColor();
    for(int l = 0; l < row; l++){
        printf("{ ");
        for(int m = 0; m < col; m++){
            printf("%d ", resultInv[l][m]);
        }
        printf("}");
        printf("\n\t\t\t\t\t\t");
    }
}

void detMatrix0(int row, int col){
    for(int i = 0; i < row; i++){
        printf("{ ");
        for(int j = 0; j < col; j++){
            printf("%d ", matrixPolyElementA[i][j]);
        }
        printf("}");
        printf("\n\t\t\t\t\t\t       ");
    }

    detMatrix(matrixPolyElementA, row, col);

    decorBlue();
    printf("\n\t\t\t\t\t\tAnswer: ");
    resetColor();
    printf("%d", resultDet);
}

void multMatrix0(int row, int col, int s){
    for(int i = 0; i < row; i++){
        printf("{ ");
        for(int j = 0; j < col; j++){
            printf("%d ", matrixPolyElementA[i][j]);
        }
        printf("}");

        if(i == 0){
            printf(" * ");
            printf("{ %d }", s);
        }

        printf("\n\t\t\t\t\t\t       ");
    }

    scalarPolyMatrix(matrixPolyElementA, s, row, col);

    decorBlue();
    printf("\n\t\t\t\t\tAnswer: ");
    resetColor();
    for(int l = 0; l < row; l++){
        printf("{ ");
        for(int m = 0; m < col; m++){
            printf("%d ", resultPoly[l][m]);
        }
        printf("}");
        printf("\n\t\t\t\t\t\t");
    }
}

void addMatrix1(int n){
    printf("{ ");
    for(int i = 0; i < n; i++){
        printf("%d ", matrixSingleElementA[i]);
    }
    printf("}");

    printf(" + ");

    printf("{ ");
    for(int j = 0; j < n; j++){
        printf("%d ", matrixSingleElementB[j]);
    }
    printf("}");

    addSingleMatrix(matrixSingleElementA, matrixSingleElementB, n);

    decorBlue();
    printf("\n\n\t\t\t\t\tAnswer: ");
    resetColor();
    printf("{ ");
    for(int k = 0; k < n; k++){
        printf("%d ", resultSingle[k]);
    }
    printf("}");
    printf("\n");
}

void subMatrix1(int n){
    printf("{ ");
    for(int i = 0; i < n; i++){
        printf("%d ", matrixSingleElementA[i]);
    }
    printf("}");

    printf(" - ");

    printf("{ ");
    for(int j = 0; j < n; j++){
        printf("%d ", matrixSingleElementB[j]);
    }
    printf("}");

    subSingleMatrix(matrixSingleElementA, matrixSingleElementB, n);

    decorBlue();
    printf("\n\n\t\t\t\t\tAnswer: ");
    resetColor();
    printf("{ ");
    for(int k = 0; k < n; k++){
        printf("%d ", resultSingle[k]);
    }
    printf("}");
    printf("\n");
}

void multMatrix1(int n){
    printf("{ ");
    for(int i = 0; i < n; i++){
        printf("%d ", matrixSingleElementA[i]);
    }
    printf("}");

    printf(" * ");

    printf("{ ");
    for(int j = 0; j < n; j++){
        printf("%d ", matrixSingleElementB[j]);
    }
    printf("}");

    multSingleMatrix(matrixSingleElementA, matrixSingleElementB, n);

    decorBlue();
    printf("\n\n\t\t\t\t\tAnswer: ");
    resetColor();
    printf("{ ");
    for(int k = 0; k < n; k++){
        printf("%d ", resultSingle[k]);
    }
    printf("}");
    printf("\n");
}

void addMatrix2(int row, int col){
    for(int i = 0; i < row; i++){
        printf("{ ");
        for(int j = 0; j < col; j++){
            printf("%d ", matrixPolyElementA[i][j]);
        }
        printf("}");

        if(i == 0){
            printf(" + ");
        } else{
            printf("   ");
        }

        printf("{ ");
        for(int j = 0; j < col; j++){
            printf("%d ", matrixPolyElementB[i][j]);
        }
        printf("}");
        printf("\n\t\t\t\t\t\t       ");
    }

    addPolyMatrix(matrixPolyElementA, matrixPolyElementB, row, col);

    decorBlue();
    printf("\n\t\t\t\t\tAnswer: ");
    resetColor();
    for(int l = 0; l < row; l++){
        printf("{ ");
        for(int m = 0; m < col; m++){
            printf("%d ", resultPoly[l][m]);
        }
        printf("}");
        printf("\n\t\t\t\t\t        ");
    }
}

void subMatrix2(int row, int col){
    for(int i = 0; i < row; i++){
        printf("{ ");
        for(int j = 0; j < col; j++){
            printf("%d ", matrixPolyElementA[i][j]);
        }
        printf("}");

        if(i == 0){
            printf(" - ");
        } else{
            printf("   ");
        }

        printf("{ ");
        for(int j = 0; j < col; j++){
            printf("%d ", matrixPolyElementB[i][j]);
        }
        printf("}");
        printf("\n\t\t\t\t\t\t       ");
    }

    subPolyMatrix(matrixPolyElementA, matrixPolyElementB, row, col);

    decorBlue();
    printf("\n\t\t\t\t\tAnswer: ");
    resetColor();
    for(int l = 0; l < row; l++){
        printf("{ ");
        for(int m = 0; m < col; m++){
            printf("%d ", resultPoly[l][m]);
        }
        printf("}");
        printf("\n\t\t\t\t\t        ");
    }
}

void multMatrix2(int row, int col){
    for(int i = 0; i < row; i++){
        printf("{ ");
        for(int j = 0; j < col; j++){
            printf("%d ", matrixPolyElementA[i][j]);
        }
        printf("}");

        if(i == 0){
            printf(" * ");
        } else{
            printf("   ");
        }

        printf("{ ");
        for(int j = 0; j < col; j++){
            printf("%d ", matrixPolyElementB[i][j]);
        }
        printf("}");
        printf("\n\t\t\t\t\t\t       ");
    }

    multPolyMatrix(matrixPolyElementA, matrixPolyElementB, row, col);

    decorBlue();
    printf("\n\t\t\t\t\tAnswer: ");
    resetColor();
    for(int l = 0; l < row; l++){
        printf("{ ");
        for(int m = 0; m < col; m++){
            printf("%d ", resultPoly[l][m]);
        }
        printf("}");
        printf("\n\t\t\t\t\t        ");
    }
}

int *addSingleMatrix(int *arr, int *arr2, int n){
    resultSingle = (int *)malloc(n * sizeof(int));
    if(resultSingle == NULL){
        nullMessage(n);
    }

    for(int i = 0; i < n; i++){
        resultSingle[i] = arr[i] + arr2[i];
    }

    return resultSingle;
}

int **addPolyMatrix(int **arr, int **arr2, int row, int col){
    resultPoly = (int **)malloc(row * sizeof(int *));
    if(resultPoly == NULL){
        nullMessage(row);
    }

    for(int i = 0; i < row; i++){
        resultPoly[i] = (int *)malloc(col * sizeof(int));
        if(resultPoly[i] == NULL){
            nullMessage(row);
        }

        for(int j = 0; j < col; j++){
            resultPoly[i][j] = arr[i][j] + arr2[i][j];
       }
    }

    return resultPoly;
}

int *subSingleMatrix(int *arr, int *arr2, int n){
    resultSingle = (int *)malloc(n * sizeof(int));
    if(resultSingle == NULL){
        nullMessage(n);
    }

    for(int i = 0; i < n; i++){
        resultSingle[i] = arr[i] - arr2[i];
    }

    return resultSingle;
}

int **subPolyMatrix(int **arr, int **arr2, int row, int col){
    resultPoly = (int **)malloc(row * sizeof(int *));
    if(resultPoly == NULL){
        nullMessage(row);
    }

    for(int i = 0; i < row; i++){
        resultPoly[i] = (int *)malloc(col * sizeof(int));
        if(resultPoly[i] == NULL){
            nullMessage(row);
        }

        for(int j = 0; j < col; j++){
            resultPoly[i][j] = arr[i][j] - arr2[i][j];
       }
    }

    return resultPoly;
}

int *multSingleMatrix(int *arr, int *arr2, int n){
    resultSingle = (int *)malloc(n * sizeof(int));
    if(resultSingle == NULL){
        nullMessage(n);
    }

    for(int i = 0; i < n; i++){
        resultSingle[i] = arr[i] * arr2[i];
    }

    return resultSingle;
}

int **multPolyMatrix(int **arr, int **arr2, int row, int col){
    resultPoly = (int **)malloc(row * sizeof(int *));
    if(resultPoly == NULL){
        nullMessage(row);
    }

    for(int i = 0; i < row; i++){
        resultPoly[i] = (int *)malloc(col * sizeof(int));
        if(resultPoly[i] == NULL){
            nullMessage(row);
        }

        for(int j = 0; j < col; j++){
            for(int k = 0; k < col; k++){
                resultPoly[i][j] = 0;
                resultPoly[i][j] += arr[i][k] * arr[k][j];
            }
        }
    }

    return resultPoly;
}

int **scalarPolyMatrix(int **arr, int s, int row, int col){
    resultPoly = (int **)malloc(row * sizeof(int *));
    if(resultPoly == NULL){
        nullMessage(row);
    }

    for(int i = 0; i < row; i++){
        resultPoly[i] = (int *)malloc(col * sizeof(int));
        if(resultPoly[i] == NULL){
            nullMessage(row);
        }

        for(int j = 0; j < col; j++){
            for(int k = 0; k < col; k++){
                resultPoly[i][j] = arr[i][k] * s;
            }
        }
    }

    return resultPoly;
}

int **invMatrix(int **arr, int **arr2, int row, int col){
    resultInv = (int **)malloc(row * sizeof(int *));
    if(resultInv == NULL){
        nullMessage(row);
    }

    for(int i = 0; i < row; i++){
        resultInv[i] = (int *)malloc(col * sizeof(int));
        if(resultInv[i] == NULL){
            nullMessage(row);
        }

        for(int j = 0; j < col; j++){
            for(int k = 0; k < col; k++){
                resultInv[i][j] = 0;
                resultInv[i][j] += arr[i][k] * arr[k][j];
            }
        }
    }

    return resultInv;
}

int detMatrix(int **arr, int row, int col){
    /*
        A = [0][0]
        B = [0][1]
        C = [1][0]
        D = [1][1]
    */

    resultDet = (arr[0][0] * arr[1][1]) - (arr[1][0] * arr[0][1]);

    return resultDet;
}
