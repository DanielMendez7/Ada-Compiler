%{
/****** ada.l **************************************************************
 * Author: Daniel Mendez
 * Date Created: 10_01_2019
 * Date Last Modified: 11_ _2019
*********************************************************************/
#include "y.tab.h"
int lineno = 1;
char linebuf[500];
%}

%%
"is"                     {return IS;}
[ \t]*                   /* Ignore all whitespace and tabs */
"\n".*                   {/* Error checking */  strcpy(linebuf, yytext+1); lineno++; yyless(1);}
"--".*                   {/*ignore comment indicator*/}
"of"                     {return OF;       }
"begin"                  {return BEG;      }
".."                     {return DOTDOT;   }
"'"                      {return TICK;     }
"procedure"              {return PROCEDURE;}
"type"                   {return TYPE;     }
"array"                  {return ARRAY;    }
"record"                 {return RECORD;   }
"in"                     {return IN;       }
"out"                    {return OUT;      }
"range"                  {return RANGE;    }
"constant"               {return CONSTANT; }
":="                     {return ASSIGN;   }
"exception"              {return EXCEPTION;}
"null"                   {return NULLWORD; }
"loop"                   {return LOOP;     }
"if"                     {return IF;       }
"then"                   {return THEN;     }
"elsif"                  {return ELSEIF;   }
"else"                   {return ELSE;     }
"exit"                   {return EXIT;     }

"case"                   {return CASE;     }
"end case"               {return ENDCASE;  }


"when"                   {return WHEN;     }
"and"                    {return AND;      }
"or"                     {return OR;       }
"not"                    {return NOT;      }
"/="                     {return NEQ;      }
"=>"                     {return ARROW;    }
"="                      {return EQ;       }
"<="                     {return LTE;      }
">="                     {return GTE;      }
">"                      {return GT;       }
"<"                      {return LT;       }
"**"                     {return EXP;      }
"raise"                  {return RAISE;    }
"others"                 {return OTHERS;   }
"end if"                 {return ENDIF;    }
"end record"             {return ENDREC;   }
"end loop"               {return ENDLOOP;  }
"exit when"              {return EXITWHEN; }
"end"                    {return END;      }

[A-Za-z][A-Za-z0-9_]*    {yylval.var = strdup(yytext);   return ID;    }
[0-9]+                   {yylval.integer = atoi(yytext); return NUMBER;}

.                        {return yytext[0];}

%%
int yyerror(char *s)
{
printf("%d: %s at '%s' in the line:\n%s\n", lineno, s, yytext, linebuf);
return 0;
}
