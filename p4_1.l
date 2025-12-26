%option noyywrap

%{
int c=0,v=0;
%}

%%

[aeiouAEIOU] v++;
[a-zA-Z] c++;
\n {printf("No of vowels: %d\nNo of consonent:%d\n",v,c);v=0;c=0;}
.
%%

void main(){
    yylex();
}