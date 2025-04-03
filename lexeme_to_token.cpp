#include <iostream>
using namespace std;

#define LETTER 0 //for letter
#define DIGIT 1 //for numbers
#define UNKNOWN 99 // for define characters 
#define EOF_TOKEN -1 // for undefine characters

#define INT_LIT 10 //for int_literal
#define IDENT 11 //identifier
#define ASSIGN_OP 20 // =
#define ADD_OP 21 // +
#define SUB_OP 22 // -
#define MULT_OP 23 // * 
#define DIV_OP 24 // / 
#define LEFT_PAREN 25 // (
#define RIGHT_PAREN 26 // )
#define SEMECOLON_OP 27 //;

char lexeme[100];
char nextChar;
int charClass;
int lexLen;
int token;
int nextToken;

void addChar() //save the lexeme in array
{
    if (lexLen < 98) // to disallow overflow
    {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = '\0';
    }
    else {
        cout << "Error - lexeme is too long" << endl;
    }
}

void getChar()
{
    if (cin.get(nextChar)) //to get the next character from input
    {
        if (isalpha(nextChar)) //to define him as a letter 
            charClass = LETTER; // 0
        else if (isdigit(nextChar)) //to define him as a digit
            charClass = DIGIT; // 1
        else //for any character define
            charClass = UNKNOWN; // 99 
    }
    else //character not define
    {
        charClass = EOF_TOKEN; // -1
    }
}

void getNonBlank() //remove whitespace
{
    while (isspace(nextChar))
    {
        getChar();
    }
}

int lookup(char ch) //to define unknown 
{
    switch (ch) {
    case '(': addChar(); return LEFT_PAREN; //25
    case ')': addChar(); return RIGHT_PAREN; //26
    case '+': addChar(); return ADD_OP; //21
    case '-': addChar(); return SUB_OP; //22
    case '*': addChar(); return MULT_OP; //23
    case '/': addChar(); return DIV_OP; //24
    case '=': addChar(); return ASSIGN_OP; //20
    case ';': addChar(); return SEMECOLON_OP; //27
    default: addChar(); return EOF_TOKEN; //-1
    }
}

int lex() {
    lexLen = 0;
    getNonBlank(); //to remove whitespace

    switch (charClass) {
    case LETTER:
        addChar(); //to save the identifier
        getChar(); //to get the identifier from user
        while (charClass == LETTER)
        {
            addChar(); //to save the nextchar
            getChar(); //to get the nextchar
        }
        nextToken = IDENT; // 11
        break;

    case DIGIT:
        addChar(); //to save the number
        getChar(); //to get the number from user
        while (charClass == DIGIT) {
            addChar(); //to save the nextchar
            getChar(); //to get the nextchar
        }
        nextToken = INT_LIT; //10
        break;

    case UNKNOWN:
        nextToken = lookup(nextChar); // to define any character
        getChar(); //to get the nextchar
        break;

    case EOF_TOKEN:
        nextToken = EOF_TOKEN; // stop the program if you find undefine character
        break;
    }

    cout << "Next token is: " << nextToken << ", Next lexeme is " << lexeme << endl;
    return nextToken; //return to main function
}

int main() {
    getChar();
    do // loop function lex() where it does not = EOF_TOKEN (-1)  
    {
        lex();
    } while (nextToken != EOF_TOKEN); //stop the program if you find undefine character

    return 0;
}