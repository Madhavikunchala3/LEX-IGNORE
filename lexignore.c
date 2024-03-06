#include<stdio.h> 
#include<ctype.h> 
#include<string.h> 
// Token types 
typedef enum
{ 
IDENTIFIER, 
NUMBER, 
OPERATOR, 
COMMENT, 
WHITESPACE, 
NEWLINE, 
EOF_TOKEN 
} 
TokenType; 
// Token structure 
typedef struct 
{ 
TokenType type; 
char value[100]; 
} Token; 
// Lexical analyzer function 
Token getNextToken(char *input, int *pos) 
{ 
Token token; 
char c = input[*pos]; 
token.value[0] = '\0'; 
// Skip whitespace 
while (isspace(c)) 
{ 
(*pos)++; 
c = input[*pos];
}
// Skip comments 
if (c == '/') 
{ 
if (input[*pos + 1] == '/')
{ 
while (c != '\n')
{ 
(*pos)++; 
c = input[*pos];
}
return 
getNextToken(input, pos);
}
else if (input[*pos + 1] == '*') 
{
 while (!(input[*pos] == '*' && input[*pos + 1] == '/'))
 {
 (*pos)++;
 }
 (*pos) += 2;
 return 
getNextToken(input, pos);
 }
 } 
// End of file 
if (c == '\0') 
{ 
token.type = EOF_TOKEN; 
return token;
}
 // Identifier or keyword 
if (isalpha(c) || c == '_') 
{ 
int i = 0;
while (isalnum(c) || c == '_')
{
 token.value[i++] = c;
(*pos)++; 
c = input[*pos];
}
token.value[i] = '\0';
token.type = IDENTIFIER; 
return token;
} 
// Number 
if (isdigit(c) || c == '.')
{
int i = 0; 
while (isdigit(c) || c == '.')
{ 
token.value[i++] = c;
(*pos)++;
c = input[*pos];
}
token.value[i] = '\0';
token.type = NUMBER; 
return token;
}
// Operator if (c == '+' || c == '-' || c == '*' || c == '/')
{ 
token.value[0] = c;
token.value[1] = '\0';
token.type = OPERATOR;
(*pos)++;
return token;
}
// Newline 
if (c == '\n')
{
token.value[0] = '\n'; 
token.value[1] = '\0'; 
token.type = NEWLINE; 
(*pos)++; 
return token; 
} 
// Other characters 
token.value[0] = c; 
token.value[1] = '\0'; 
(*pos)++; 
return token; 
} 
int main()
{ 
char name[20];
char rollno[20];
printf("\n Enter the Name:");
scanf("%s",name);
printf("\n Enter the Roll No:");
scanf("%s",rollno);
char input[] = "int main() {\n // This is a comment\n int a=2;\n int b=20.5;\n int sum=a+b;\n return sum\n };\n}";
//char input[] = "int main() {\n // This is a comment\n int a=10;\n int b=20;\n int div=a/b;\n return div\n };\n}";
//char input[] = "int main() {\n // This is a comment\n int a=10;\n int b=20;\n int c=30;\n int mul=a*b*c;\n return mul\n };\n}";
//char input[]  = "int main() {\n // We can change values here for\n  float P = 1.0;\n float R = 1.0\n, float T = 1.0\n; // Calculate simple interest\n float SI = (P * T * R) / 100;\n return 0\n };\n}"; 
int pos = 0; 
Token token; 
printf("---------------------\n");
printf("\n OUTPUT:\n"); 
printf("---------------------\n");
do
{
token = getNextToken(input, &pos);
switch (token.type)
{
case IDENTIFIER:
printf("Identifier: %s\n", token.value); 
break; 
case NUMBER: 
printf("Number: %s\n", token.value); 
break; 
case OPERATOR: 
printf("Operator: %s\n", token.value); 
break; 
case COMMENT: 
printf("Comment: %s\n", token.value); 
break; 
case WHITESPACE:
// Ignore whitespace tokens 
break; 
case NEWLINE: 
printf("Newline\n"); 
break; 
case EOF_TOKEN: 
printf("End of file\n"); 
break; 
default: 
printf("Unknown token\n"); 
break; 
} 
} 
while (token.type != EOF_TOKEN);
return 0;
}