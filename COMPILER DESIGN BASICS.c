#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// List of some C keywords
char *keywords[] = {
    "int", "float", "if", "else", "while", "for",
    "return", "char", "double", "void", "do", "break", "continue"
};

int isKeyword(char *word) {
    for (int i = 0; i < sizeof(keywords)/sizeof(keywords[0]); i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int isOperator(char ch) {
    char operators[] = "+-*/%=<>&|!";
    for (int i = 0; operators[i] != '\0'; i++) {
        if (ch == operators[i])
            return 1;
    }
    return 0;
}

void analyzeFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening file");
        return;
    }

    char ch;
    char buffer[100];
    int i = 0;

    printf("\nLexical Tokens Found:\n");
    while ((ch = fgetc(fp)) != EOF) {
        // If it's a letter or underscore, start building identifier or keyword
        if (isalpha(ch) || ch == '_') {
            buffer[i++] = ch;
            while (isalnum(ch = fgetc(fp)) || ch == '_') {
                buffer[i++] = ch;
            }
            buffer[i] = '\0';
            i = 0;
            ungetc(ch, fp);  // push back non-matching character

            if (isKeyword(buffer))
                printf("Keyword: %s\n", buffer);
            else
                printf("Identifier: %s\n", buffer);
        }
        // If it's an operator
        else if (isOperator(ch)) {
            printf("Operator: %c\n", ch);
        }
        // If it's a number (optional for this basic version)
        else if (isdigit(ch)) {
            buffer[i++] = ch;
            while (isdigit(ch = fgetc(fp))) {
                buffer[i++] = ch;
            }
            buffer[i] = '\0';
            i = 0;
            ungetc(ch, fp);  // push back non-digit
            printf("Number: %s\n", buffer);
        }
    }

    fclose(fp);
}

int main() {
    char filename[100];

    printf("Enter input filename: ");
    scanf("%s", filename);

    analyzeFile(filename);

    return 0;
}
