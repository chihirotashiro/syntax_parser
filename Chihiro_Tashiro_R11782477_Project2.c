

/* Chihiro_Tashiro_R11782477_Project1.c - a lexical analyzer system for arithmetic expressions */
#include <stdio.h>
#include <ctype.h>
#include<string.h>
#include <stdlib.h>

/* Global Variable */
int nextToken;

/* Local Variables */
static int charClass;
static char lexeme [100];
static char nextChar;
static int lexLen;
static FILE *in_fp;
char*filename;
const char *tokenName[15];
const char name[30][15]={"LETTER","DIGIT", "UNKNOWN","INT_LIT","IDENT","ASSIGN_OP","ADD_OP","SUB_OP", "MULT_OP","DIV_OP","LEFT_PAREN","RIGHT_PAREN","EQUAL_OP","SEMICOLON","NEQUAL_OP","LEQUAL_OP","GEQUAL_OP","INC_OP","DEC_OP","KEY_READ","KEY_WRITE","KEY_WHILE","KEY_DO","KEY_OD","GREATER_OP","LESSER_OP"};

/* Local Function declarations */
static void addChar();
static void getChar();
static void getNonBlank();
static int lookup(char ch);
int isKeyword(char *str);
const char* getTokenName(int num);
int lex();
static void error();
void program();
void statement();
void gram_c();
void gram_e();
void gram_t();
void gram_f();
void gram_o();
void variable();
void number();

/*****************************************************/
/* main - read file and call functions. If there is an error regarding reading files, exit.
 */
int main(int argc, char ** argv ) 
{

 if (argc == 2) {

    filename = argv[1];
    in_fp = fopen(filename,"r");  
   
    if (in_fp) {
        printf("DCooke Parser ::R11782477");
 
        printf("\n");
        getChar();
        
        do {
        lex();
        program();
        } while (nextToken != EOF); 
        fclose(in_fp);
        printf("Syntax validated\n");
        exit(0);  

    }
   //If the user did provide a file as input but the file does not exist:
    else {
     printf("You provided a file as input but the file doesn't exist.\n");
      exit(3);
    }
  }
  //If the user did not provide a file as input
  else {
    printf("You didn't provide a file as input.\n");
    exit(2);
  } 
}





/*****************************************************/
/* lookup - a function to lookup operators and parentheses and return the 
 * nextToken */
static int lookup(char ch) {
  
    switch (ch) {
        case '(':
           addChar();
            nextToken = 25;
            break;
        case ')':
            addChar();
            nextToken = 26;
            break;
        case '+':
            addChar();
            getChar();
        
            if(nextChar=='+'){
               addChar();
               nextToken=32;
            }
            else {
            nextToken = 21;
            ungetc(nextChar, in_fp);
            }
            break;
        case '-':
            addChar();
            getChar();
     
            if(nextChar=='-'){
            addChar();
            nextToken=33;
            }
            else {
            nextToken = 22;
            ungetc(nextChar, in_fp);
            }
            break;
        case '*':
            addChar();
            nextToken = 23;
            break;
        case '/':
            addChar();
            nextToken = 24;
            break;
        case '=':
            addChar();
            nextToken=27;
            break;
        case ';':
            addChar();
            nextToken=28;
            break;
        case '>':
            addChar();
            getChar();
            if( nextChar=='='){
                addChar();
                nextToken=31;
            }
           
            else {
            nextToken=39;
            ungetc(nextChar, in_fp);
            }
            break;
        case '<':
            addChar();
            getChar();

            if(nextChar=='='){
                addChar();
                nextToken=30;
            }
            else {
            nextToken=40;
            ungetc(nextChar, in_fp);
            }
            break;
        case '!':
            addChar();
            getChar();
            if (nextChar=='='){
                addChar();
                nextToken=29;
            }
            else{
                ungetc(nextChar, in_fp);
                nextToken=99;
            }
            break;
        case ':':
            addChar();
            getChar();
            if(nextChar=='='){
                addChar();
                nextToken=20;
            }
           else{
                ungetc(nextChar, in_fp); 
                nextToken=99;
            }
              break;
        default:
            addChar();
            nextToken = 99;
            break;
    }
    return nextToken;
}

/*****************************************************/
/* addChar a function to add nextChar to lexeme */
static void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    } else {
        printf("Error - lexeme is too long \n");
    }
}

/*****************************************************/
/* getChar - a function to get the next character of input and determine its 
 * character class */
static void getChar() 
{
    if ((nextChar = fgetc(in_fp)) != EOF) 
    {
        if (isalpha(nextChar))
            charClass = 0;
        else if (isdigit(nextChar))
            charClass = 1;
       
        else {
            charClass = 99;
            
             }
    } 
    else {
        charClass = EOF;
         }
}
 
/*****************************************************/
/* getNonBlank - a function to call getChar until it returns a non-whitespace 
 * character */
static void getNonBlank() {
    while (isspace(nextChar)) getChar();
}

/*****************************************************/
/* getTokenName - a function to determine token besed on nextToken integer and returns a tokenname*/
const char* getTokenName(int num){
    switch (num)
     {
        case 0:
           return name[0];
        case 1:
           return name[1];
        case 10:
           return name[3];
        case 11:
           return name[4];
        case 20:
           return name[5];
        case 21:
           return name[6];
        case 22:
           return name[7];
        case 23:
           return name[8];
        case 24:
           return name[9];
        case 25:
           return name[10];
        case 26:
           return name[11];
        case 27:
           return name[12];
        case 28:
           return name[13];
        case 29:
           return name[14];
        case 30:
           return name[15];
        case 31:
           return name[16];
        case 32:
           return name[17];
        case 33:
           return name[18];
        case 34:
           return name[19];
        case 35:
           return name[20];
        case 36:
           return name[21];
        case 37:
           return name[22];
        case 38:
           return name[23];
        case 39:
           return name[24];
        case 40:
           return name[25];
        case 99:
            return name[2];
            break;
        
     }
    return 0;
}

/*****************************************************/
/* iskeyword - a function to lookup keywords and return the 
 * flag*/
 int isKeyword(char *str){
char keywords[6][10] = {"read","write","while","do","od", "while"};
int i, flag = 0;
for(i = 0; i < 6; ++i){
if(strcmp(str,keywords[i]) == 0){
flag = 1;
break;
}
}
return flag;
}

/*****************************************************/
/* lex - a lexical analyzer for arithmetic expressions */
int lex() {
    lexLen = 0;
    getNonBlank();

    switch (charClass) {
        /* Parse identifiers */
        case 0:
            addChar();
            getChar(); 
            while (charClass == 0 || charClass == 1)
            {
                addChar();
                getChar();
            }
            
            if (isKeyword(lexeme)==1)
            {
                if(strcmp(lexeme, "read")==0){
                nextToken=34;
                }
            else if (strcmp(lexeme, "write")==0){
                nextToken=35;
                }
            else if (strcmp(lexeme, "while")==0){
                nextToken = 36;
                }
            else if (strcmp(lexeme, "do")==0){
                nextToken = 37;  
                }
            else if (strcmp(lexeme, "od")==0){
                nextToken = 38;
                }
            break;
            }
            else nextToken = 11;
            break;

        /* Parse integer literals */
        case 1:
            addChar();
            getChar();
            while (charClass == 1) {
                addChar();
                getChar();
            }
            nextToken = 10;
            break;

        /* Parentheses and operators */
        case 99:
             lookup(nextChar);
             getChar();
            break;

        /* EOF */
        case EOF:
            nextToken = EOF; 
            break; 
    } /* End of switch */

    if(getTokenName(nextToken)!=NULL){
    printf("%s\t\t%s\n", lexeme, getTokenName(nextToken));}
    
    return nextToken;
} /* End of function lex */



/*****************************************************/
/* program - a function for grammar P */
void program()
{
    statement();
}


/*****************************************************/
/* statement - a function for grammar S */
void statement()
{
    /*V:=E*/
    if ( nextToken == 11 ) {
        lex();

        if ( nextToken == 20) {
            lex();
            gram_e();
        }
        else {
            printf("Error not assign in statement\n");
            error();
        }
    }
    /*read(V)*/
    else if ( nextToken == 34) {
        lex();

        if ( nextToken == 25 ) {
            lex();
            variable();

            if ( nextToken == 26) {
                lex();
            }
            else {
                error();
            }
        }
        else {
            error();
        }
    }
    /*write(V)*/
    else if ( nextToken == 35 ) {
        lex();

        if ( nextToken == 25 ) {
            lex();
            variable();

            if ( nextToken == 26 ) {
                lex();
            }
            else {
                error();
            }
        }
        else {

            error();
        }
    }
    /*O*/
     else if(nextToken == 32 || nextToken == 33){
        lex();
        gram_o();
    }
    /*while(C) do S od*/
    else if ( nextToken == 36 ) 
    {
        lex();
        if (nextToken == 25){
            lex();
            gram_c();
            if ( nextToken == 26 ) {
                lex();
                 if ( nextToken == 37) {
            lex();
            statement();

            if ( nextToken == 38 ) {
                lex();
            }
            else {
               
                error();
            }
        }
        else {
            
            error();
        }
            }
             else {
                error();
            }

        }
        else{
            error();
        }

    }
    else 
    {
        error();
    }

    
    /*S;S*/
    while(1) {
        if (nextToken == 28) {
            lex();
            statement();
        }
        else {
            return;  
        }
    }
}

/*****************************************************/
/* gram_c - a function for grammar C */
/* C=E>E,E<E,E=E,E!=E,E<=E,E>=E */
void gram_c(){
    gram_e();

    if (nextToken == 39 || nextToken == 40 || nextToken == 27 || nextToken == 29 || nextToken == 30 || nextToken == 31 ){
        lex();
    }
    else {
    
        error();
    }

    gram_e();
}

/*****************************************************/
/* gram_e - a function for grammar E */
/* E=T ,E+T,E-T*/
void gram_e(){
    gram_t();

    while (1) {
        if ( nextToken == 21|| nextToken == 22) {
            lex();
            gram_t();
        }
        else {
            return; 
        }
    }
}

/*****************************************************/
/* gram_t - a function for grammar T
*T ::= F | T * F | T / F*/

void gram_t() {
    gram_f();

    while (1) {
        if ( nextToken == 23) {
            lex();
            gram_f();
        }
        else if (nextToken == 24) {
            lex();
            gram_f();
        }
        else {
            return; 
        }
    }
}

/*****************************************************/
/* gram_f - a function for grammar F */
/*F=(E),O,N,V */
void gram_f() {
    // N
    if ( nextToken == 10 ) {
        number();
    }
    //V
    else if ( nextToken == 11 ){
        variable();
    }
    //(E)
    else if ( nextToken == 25 ) {
        lex();
        gram_e();

        if ( nextToken == 26 ) {
            lex();
        }
        else {
            error();
        }
    }
    // O 
    else if(nextToken == 32 || nextToken == 33){
        lex();
        gram_o();
    }
    else {
        
        error();
    }
    
}

/*****************************************************/
/* gram_o - a function for grammar O
*O ::= ++V | --V*/
void gram_o() { 
    if ( nextToken == 11 ) {
        lex();
        variable();
    }
    else{
        error();
    }
    
   
}



/*****************************************************/
/* variable - a function for grammar V */

void variable(){
    if ( nextToken == 11 ) {
        lex();
  
    }
    
    
}

/*****************************************************/
/* number - a function for grammar N */
void number(){
    if ( nextToken == 10 ) {
        lex();

    }
   
}

/*****************************************************/
/* error - a function to show the error message, lexeme, and next token */
static void error() 
{
     printf("Error encounter: The next lexeme was %s and the next token was %s\n", lexeme, getTokenName(nextToken));
     exit(1);
}