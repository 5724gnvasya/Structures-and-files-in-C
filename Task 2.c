#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct izdatel {
    int god;
    char naz[100];
    char gor[100];
};

struct Book {
    char title[100];
    int price;
    int numPages;
    char author[100];
    struct izdatel publisherInfo;
};



void check_number(FILE *input_data, int *s) {
    int ret_code;
    do {
        ret_code = fscanf(input_data, "%d", s);
        //while (getchar() != '\n');  // clear the buffer (as not using fgets)
    } while (ret_code != 1 || *s <= 0);
}


// void check_year(FILE *input_data, int *s) {
//     int ret_code;
//     char buffer[100]; 
//     do {
//         ret_code = fscanf(input_data, " %99[^\n]%*c", buffer); 
//         if (ret_code == 1) {
//             int isValid = 1;
//             for (int i = 0; buffer[i] != '\0'; i++) {
//                 if (!isdigit(buffer[i])) {
//                     isValid = 0;
//                     break;
//                 }
//             }
//             if (isValid ) {
//                 *s = atoi(buffer); 
//                 if (*s >= 1458 && *s<= 2024) {
//                     break;
//                 }
//             }
//         }
//         printf("Invalid input. Please enter a valid positive integer:\n");
//         break;
//     } while (ret_code != 1 || *s <= 0);
// }


void check_year(FILE *input_data, int *s) {
    int ret_code;
    do {
        ret_code = fscanf(input_data, "%d", s);
        //while (getchar() != '\n');  // clear the buffer (as not using fgets)
    } while (ret_code != 1 || *s <= 0 || *s<1458 || *s > 2024);
}
void check_string(FILE *input_data, char s[]) {
    int invalid_input;
    do {
        invalid_input = 0;
        fscanf(input_data, " %99[^\n]%*c", s);

        for (int i = 0; i < strlen(s); i++) {
            if (!isalpha(s[i]) && !isspace(s[i])) { 
                invalid_input = 1;
                printf("Invalid input. Please enter a string without numbers or special characters.\n");
                break;
            }
        }

        if (invalid_input || strlen(s) == 0) {
            printf("Invalid input or empty string. Please try again.\n");
            break;
        }

    } while (strlen(s) == 0);
}

void input(struct Book *books, const int numStructs, FILE *input_data) {
    for (int i = 0; i < numStructs; i++) {
        check_string(input_data, books->title);
        check_number(input_data, &books->price);
        check_number(input_data, &books->numPages);
        check_string(input_data, books->author);
        check_year(input_data, &books->publisherInfo.god);
        check_string(input_data, books->publisherInfo.naz);
        check_string(input_data, books->publisherInfo.gor);
        books++;  
    }
}

void solution(struct Book *books, const int numStructs, FILE *output_data) {
    int minYear = books->publisherInfo.god;
    for (int i = 1; i < numStructs; i++) {
        if ((books + i)->publisherInfo.god < minYear) {
            minYear = (books + i)->publisherInfo.god;
        }
    }
     
    fprintf(output_data, "Publishing companies with the cheapest books:\n");
    for (int i = 0; i < numStructs; i++) {
        if ((books + i)->publisherInfo.god == minYear) {
            fprintf(output_data, "%s\n", (books + i)->publisherInfo.naz);
        }
    }
}

int main() {
    FILE *inputFile, *outputFile;
    int numStructs;

    printf("Enter the number of books: ");
    scanf("%d", &numStructs);
    struct Book books[numStructs];

    inputFile = fopen("input_data.txt", "r");
    outputFile = fopen("output_data.txt", "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    input(books, numStructs, inputFile);
    solution(books, numStructs, outputFile);

    fclose(inputFile);
    fclose(outputFile);
    
    return 0;
}
