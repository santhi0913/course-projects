%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
extern int yylex();
extern void yyerror(char *);

%}

%union {
	char *text;
}

/*declare all the tokens here*/
%token  define_stmt define_stmt0 define_stmt1 define_stmt2 define_expr define_expr0 define_expr1 define_expr2
%token curly_left curly_right bracket_left bracket_right dot comma sqr_left sqr_right equal semi_col not
%token If Then Else While This New Length print True False Int Bool
%token Class Extends Public Static Void Main 
%token Plus Minus Mul Div And Or Notequal Lequal String Ques RETURN

%type<text> Integer Identifier Plus Minus Mul Div And Or Notequal Lequal String Ques RETURN curly_left curly_right bracket_left bracket_right dot comma sqr_left sqr_right equal semi_col not If Then Else While This New Length print True False Int Bool
%type<text> Goal Statement Expression PrimaryExpression MacroDefinition MacroDefStatement MacroDefExpression
%type<text> MainClass TypeDeclaration MethodDeclaration Type INTEGER IDENTIFIER
%type <text> helpone CommaIdStar
%type <text> helptwo Class Extends Public Static Void Main 
%type <text> helpthree define_stmt define_stmt0 define_stmt1 define_stmt2 define_expr define_expr0 define_expr1 define_expr2
%type <text> helpfour
%type <text> helpfive
%type <text> helpsix
%type <text> helpseven
%type <text> helpeight
%% 

Goal:   MainClass	{sprintf($$,"%s\n",$1); printf("%s\n",$$);}	
	|	helpseven MainClass {sprintf($$,"%s\n",$2); printf("%s\n",$$);}	
	|	MainClass helpeight {sprintf($$,"%s %s\n",$1,$2); printf("%s\n",$$);}
	|	helpseven MainClass helpeight 	{sprintf($$,"%s %s\n",$2,$3); printf("%s\n",$$);};

MainClass: Class Identifier curly_left Public Static Void Main bracket_left String sqr_left sqr_right Identifier bracket_right curly_left print bracket_left Expression bracket_right semi_col curly_right curly_right		{sprintf($$,"%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s",$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13,$14,$15,$16,$17,$18,$19,$20,$21);};

TypeDeclaration: Class Identifier curly_left curly_right {sprintf($$,"%s %s %s %s",$1,$2,$3,$4);}
		|	Class Identifier curly_left helptwo curly_right  {sprintf($$,"%s %s %s %s %s",$1,$2,$3,$4,$5);}
		| 	Class Identifier curly_left helpone curly_right   {sprintf($$,"%s %s %s %s %s",$1,$2,$3,$4,$5);}
		|	Class Identifier curly_left helpone helptwo curly_right	{sprintf($$,"%s %s %s %s %s %s",$1,$2,$3,$4,$5,$6);}
		|	Class Identifier Extends Identifier curly_left curly_right	{sprintf($$,"%s %s %s %s %s %s",$1,$2,$3,$4,$5,$6);}
		|	Class Identifier Extends Identifier curly_left helptwo curly_right	{sprintf($$,"%s %s %s %s %s %s %s",$1,$2,$3,$4,$5,$6,$7);}
		|	Class Identifier Extends Identifier curly_left helpone curly_right	{sprintf($$,"%s %s %s %s %s %s %s",$1,$2,$3,$4,$5,$6,$7);}
		|	Class Identifier Extends Identifier curly_left helpone helptwo curly_right	{sprintf($$,"%s %s %s %s %s %s %s %s",$1,$2,$3,$4,$5,$6,$7,$8);}	;

MethodDeclaration: Public Type Identifier bracket_left bracket_right curly_left RETURN Expression semi_col curly_right	{sprintf($$,"%s %s %s %s %s %s %s %s %s %s",$1,$2,$3,$4,$5,$6,$7,$8,$9,$10);}
		|	Public Type Identifier bracket_left bracket_right curly_left helpone RETURN Expression semi_col curly_right	{sprintf($$,"%s %s %s %s %s %s %s %s %s %s %s",$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11);}		|	Public Type Identifier bracket_left bracket_right curly_left helpthree RETURN Expression semi_col curly_right	{sprintf($$,"%s %s %s %s %s %s %s %s %s %s %s",$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11);}
		|	Public Type Identifier bracket_left bracket_right curly_left helpone helpthree RETURN Expression semi_col curly_right {sprintf($$,"%s %s %s %s %s %s %s %s %s %s %s %s",$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12);}	
		|	Public Type Identifier bracket_left Type Identifier bracket_right curly_left RETURN Expression semi_col curly_right  {sprintf($$,"%s %s %s %s %s %s %s %s %s %s %s %s",$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12);}	
		|	Public Type Identifier bracket_left Type Identifier bracket_right curly_left helpone RETURN Expression semi_col curly_right  {sprintf($$,"%s %s %s %s %s %s %s %s %s %s %s %s %s",$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13);}	
		|	Public Type Identifier bracket_left Type Identifier bracket_right curly_left helpthree RETURN Expression semi_col curly_right  {sprintf($$,"%s %s %s %s %s %s %s %s %s %s %s %s %s",$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13);}		
		|	Public Type Identifier bracket_left Type Identifier bracket_right curly_left helpone helpthree RETURN Expression semi_col curly_right    {sprintf($$,"%s %s %s %s %s %s %s %s %s %s %s %s %s %s",$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13,$14);}	
		|	Public Type Identifier bracket_left Type Identifier helpfour bracket_right curly_left RETURN Expression semi_col curly_right    {sprintf($$,"%s %s %s %s %s %s %s %s %s %s %s %s %s",$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13);}
		|	Public Type Identifier bracket_left Type Identifier helpfour bracket_right curly_left helpone RETURN Expression semi_col curly_right   {sprintf($$,"%s %s %s %s %s %s %s %s %s %s %s %s %s %s",$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13,$14);}	
		|	Public Type Identifier bracket_left Type Identifier helpfour bracket_right curly_left helpthree RETURN Expression semi_col curly_right	{sprintf($$,"%s %s %s %s %s %s %s %s %s %s %s %s %s %s",$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13,$14);}		
		|	Public Type Identifier bracket_left Type Identifier helpfour bracket_right curly_left helpone helpthree RETURN Expression semi_col curly_right	{sprintf($$,"%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s",$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13,$14,$15);}		;

Type: Int   {sprintf($$,"%s",$1);}
	|	Bool	{sprintf($$,"%s",$1);}
	|	Int sqr_left sqr_right	{sprintf($$,"%s %s %s",$1,$2,$3);}
	|	Identifier	{sprintf($$,"%s",$1);}	;

Statement: curly_left curly_right	{sprintf($$,"%s %s",$1,$2);}
	|	curly_left helpthree curly_right	{sprintf($$,"%s %s %s",$1,$2,$3);}
	|	print bracket_left Expression bracket_right semi_col	{sprintf($$,"%s %s %s %s %s",$1,$2,$3,$4,$5);}
	|	Identifier equal Expression semi_col	{sprintf($$,"%s %s %s %s",$1,$2,$3,$4);}
	|	Identifier sqr_left Expression sqr_right equal Expression semi_col	{sprintf($$,"%s %s %s %s %s %s %s",$1,$2,$3,$4,$5,$6,$7);}
	|	If bracket_left Expression bracket_right Statement	{sprintf($$,"%s %s %s %s %s",$1,$2,$3,$4,$5);}
	|	If bracket_left Expression bracket_right Statement Else Statement	{sprintf($$,"%s %s %s %s %s %s %s",$1,$2,$3,$4,$5,$6,$7);}
	|	While bracket_left Expression bracket_right Statement	{sprintf($$,"%s %s %s %s %s",$1,$2,$3,$4,$5);}
	|	Identifier bracket_left bracket_right semi_col		{if(strcmp(getval($1),"err")!=0){sprintf($$,"%s",getval($1));} else{sprintf($$,"%s %s %s %s",$1,$2,$3,$4);}}
	|	Identifier bracket_left Expression bracket_right semi_col	{if(strcmp(getval($1),"err")!=0){sprintf($$,"%s",str_replace(getval($1),getparams($1),$3));}else{sprintf($$,"%s %s %s %s %s",$1,$2,$3,$4,$5);}}
	|	Identifier bracket_left Expression STARFIVE bracket_right semi_col	
	| 	Type Identifier semi_col	{sprintf($$,"%s %s %s",$1,$2,$3);};

Expression: PrimaryExpression And PrimaryExpression	{sprintf($$,"%s %s %s",$1,$2,$3);}
	|	PrimaryExpression Or PrimaryExpression	{sprintf($$,"%s %s %s",$1,$2,$3);}
	|	PrimaryExpression Notequal PrimaryExpression	{sprintf($$,"%s %s %s",$1,$2,$3);}
	|	PrimaryExpression Lequal PrimaryExpression	{sprintf($$,"%s %s %s",$1,$2,$3);}
	|	PrimaryExpression Plus PrimaryExpression	{sprintf($$,"%s %s %s",$1,$2,$3);}
	|	PrimaryExpression Minus PrimaryExpression	{sprintf($$,"%s %s %s",$1,$2,$3);}
	|	PrimaryExpression Mul PrimaryExpression		{sprintf($$,"%s %s %s",$1,$2,$3);}
	|	PrimaryExpression Div PrimaryExpression		{sprintf($$,"%s %s %s",$1,$2,$3);}
	|	PrimaryExpression sqr_left PrimaryExpression sqr_right	{sprintf($$,"%s %s %s %s",$1,$2,$3,$4);}
	|	PrimaryExpression Length		{sprintf($$,"%s %s",$1,$2);}
	|	PrimaryExpression		{sprintf($$,"%s",$1);}
	|	PrimaryExpression dot Identifier bracket_left bracket_right	{if(strcmp(getval($3),"err")!=0){sprintf($$,"%s %s %s %s %s",$1,$2,$4,getval($3),$5);}else{sprintf($$,"%s %s %s %s %s",$1,$2,$3,$4,$5);}}
	|	Identifier bracket_left Expression bracket_right	{if(strcmp(getval($1),"err")!=0){sprintf($$,"%s %s %s",$2,str_replace(getval($1),getparams($1),$3),$4);}else{sprintf($$,"%s %s %s %s",$1,$2,$3,$4);}}

		

PrimaryExpression: Integer	{sprintf($$,"%s",$1);}
		|	True	{sprintf($$,"%s",$1);}
		|	False	{sprintf($$,"%s",$1);}
		|	Identifier	{sprintf($$,"%s",$1);}
		|	This	{sprintf($$,"%s",$1);}
		|	New Int sqr_left Expression sqr_right	 {sprintf($$,"%s %s %s %s %s",$1,$2,$3,$4,$5);}
		|	New Identifier bracket_left bracket_right	 {sprintf($$,"%s %s %s %s",$1,$2,$3,$4);}
		|	Notequal Expression		 {sprintf($$,"%s %s",$1,$2);}
		|	bracket_left Expression bracket_right	 {sprintf($$,"%s %s %s",$1,$2,$3);}	;

MacroDefinition: MacroDefExpression	{sprintf($$,"%s",$1);}
		|	MacroDefStatement	{sprintf($$,"%s",$1);}	;

MacroDefStatement: define_stmt0 Identifier bracket_left bracket_right curly_left helpthree curly_right	{stOre($2,$6,""); sprintf($$,"%s %s %s %s %s %s %s",$1,$2,$3,$4,$5,$6,$7);}
		|	define_stmt1 Identifier bracket_left Identifier bracket_right curly_left helpthree curly_right	{stOre($2,"",$4); sprintf($$,"%s %s %s %s %s %s %s",$1,$2,$3,$4,$5,$6,$7);}
		|	define_stmt2 Identifier bracket_left Identifier helpsix bracket_right curly_left helpthree curly_right	{char* temp=(char*)malloc(strlen($4)+strlen($5)+1);strcpy(temp,$4);strcat(temp,$5);stOre($2,"",temp);free(temp);sprintf($$,"%s %s %s %s %s %s %s %s",$1,$2,$3,$4,$5,$6,$7,$8);}
		|	define_stmt Identifier bracket_left Identifier helpsix helpsix bracket_left helpsix bracket_right CommaIdStar bracket_right curly_left helpthree curly_right	{char* temp=(char*)malloc(strlen($4)+strlen($5)+1);strcpy(temp,$4);strcat(temp,$5);stOre($2,$8,temp);free(temp);sprintf($$,"%s %s %s %s %s %s %s %s %s",$1,$2,$3,$4,$5,$6,$7,$8,$9);}	;

MacroDefExpression: define_expr Identifier bracket_left Identifier CommaIdStar bracket_right bracket_left Expression bracket_right {char* temp=(char*)malloc(strlen($4)+strlen($5)+1);strcpy(temp,$4);strcat(temp,$5);stOre($2,$8,temp);free(temp);sprintf($$,"%s %s %s %s %s %s %s %s %s",$1,$2,$3,$4,$5,$6,$7,$8,$9);}	;
		| define_expr0 Identifier bracket_left bracket_right bracket_left Expression bracket_right	{stOre($2,$6,""); sprintf($$,"%s %s %s %s %s %s %s",$1,$2,$3,$4,$5,$6,$7);}
		|	define_expr1 Identifier bracket_left Identifier bracket_right bracket_left Expression bracket_right	{stOre($2,$7,$4); sprintf($$,"%s %s %s %s %s %s %s %s",$1,$2,$3,$4,$5,$6,$7,$8);}
		|	define_expr2 Identifier bracket_left Identifier helpsix bracket_right bracket_left Expression bracket_right	{char* temp=(char*)malloc(strlen($4)+strlen($5)+1);strcpy(temp,$4);strcat(temp,$5);stOre($2,$8,temp);free(temp);sprintf($$,"%s %s %s %s %s %s %s %s %s",$1,$2,$3,$4,$5,$6,$7,$8,$9);}	;

Identifier: IDENTIFIER		{sprintf($$,"%s",$1);}	;
IDENTIFIER: 
			|;
Integer: Integer	{sprintf($$,"%s",$1);}	;
CommaIdStar: comma Identifier {sprintf($$, "%s %s", $1, $2);}
		| comma Identifier CommaIdStar {sprintf($$, "%s %s %s", $1, $2, $3);} ;
helpone: Type Identifier semi_col 	{sprintf($$,"%s %s %s",$1,$2,$3);}
	|	Type Identifier semi_col helpone	{sprintf($$,"%s %s %s %s",$1,$2,$3,$4);}		;
helptwo: MethodDeclaration 	{sprintf($$,"%s",$1);}
	|	MethodDeclaration helptwo	{sprintf($$,"%s %s",$1,$2);}		;
helpthree: Statement	{sprintf($$,"%s",$1);}
	|	Statement helpthree	{sprintf($$,"%s %s",$1,$2);}	;
helpfour: comma Type Identifier		{sprintf($$,"%s %s %s",$1,$2,$3);}
	|	comma Type Identifier helpfour	{sprintf($$,"%s %s %s %s",$1,$2,$3,$4);}	;
STARFIVE: comma Expression	{sprintf($$,"%s %s",$1,$2);}
	|	comma Expression STARFIVE	{sprintf($$,"%s %s %s",$1,$2,$3);}	;
helpsix: comma Identifier	{sprintf($$,"%s %s",$1,$2);}
	|	comma Identifier helpsix	{sprintf($$,"%s %s %s",$1,$2,$3);}	;
helpseven: MacroDefinition helpseven	{sprintf($$,"%s %s",$1,$2);}
	|	MacroDefinition		{sprintf($$,"%s",$1);}		;
helpeight: TypeDeclaration helpeight	{sprintf($$,"%s %s",$1,$2);}
	|	TypeDeclaration		{sprintf($$,"%s",$1);}		;
 
%%




