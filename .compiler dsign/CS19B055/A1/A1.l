%{
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<stdbool.h>
#include <assert.h>
#include "lab2.tab.h" 


%}

digit [0-9]
integer 0|[1-9]{digit}*

%%


"#defineStmt" { 
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return define_stmt;}
"#defineStmt0" { 
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return define_stmt0;}
"#defineStmt1" { 
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return define_stmt1;}
"#defineStmt2" { 
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return define_stmt2;}

"#defineExpr" {
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return define_expr;}
"#defineExpr0" {
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return define_expr0;}
"#defineExpr1" {
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return define_expr1;}
"#defineExpr2" {
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return define_expr2;}

"{" { 
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return curly_left;}
"}" { 
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return curly_right;}
"(" { 
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return bracket_left;}
")" { 
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return bracket_right;}

"if" {
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return If;}
"then" { 
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return Then;}
"else" {
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return Else;}
"while" {
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return While;}
"this" {
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return This;}
"new" { 
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return New;}
".length" {
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return Length;}
"System.out.println" { 
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return print;}
"true" { 
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return True;}
"false" {
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return False;}
"int" {
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return Int;}
"boolean" {
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return Bool;}
"class" {
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	reutrn Class;
}
"extends" {
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return Extends;
}
"public" {
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return Public;
}
"static" {
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return Static;
}
"void" {
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return Void;
}
"main" {
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return Main;
}
"String" {
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return String;
}
"return" {
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return RETURN;
}
"?" {
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return Ques;
}
"+" {
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return Plus;
}
"-" {
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return Minus;
}
"*" {
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return Mul;
}
"/" {
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return Div;
}
"&&" {
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return And;
}

"||" {
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return Or;
}
"." { 
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return dot;}
"," { 
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return comma;}
"[" { 
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return sqr_left;}
"]" { 
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return sqr_right;}
"=" {
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return equal;}
";" {
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return semi_col;}
"!" {
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return not;}
"!=" {
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return Noteq;
}
"<=" {
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return Leq;
}
{integer} { 
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return Integer;
}
[a - z A - Z _][a - z A - Z 0 - 9 _] *{
	int len = strlen(yytext);
	yylval.text = (char*) malloc((len + 1) * sizeof(char));
	yylval.text[0] = '\0';
	strcat(yylval.text,yytext);
	return Identifier;
}

"\n" {return EOF}
[ \t\f] { }
. { printf("error"); }
%%
