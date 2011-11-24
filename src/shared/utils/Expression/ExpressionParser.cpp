/* A Bison parser, made by GNU Bison 1.875b.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUMBER = 258,
     NAME = 259,
     STATE = 260,
     SIGNAL_ = 261,
     NEG = 262
   };
#endif
#define NUMBER 258
#define NAME 259
#define STATE 260
#define SIGNAL_ 261
#define NEG 262




/* Copy the first part of user declarations.  */
#line 3 "ExpressionParser.y"

////////////////////////////////////////////////////////////////////////
// $Id$
// Author:      juergen.mellinger@uni-tuebingen.de
// Description: Bison grammar file for a simple expression parser.
//
// $BEGIN_BCI2000_LICENSE$
// 
// This file is part of BCI2000, a platform for real-time bio-signal research.
// [ Copyright (C) 2000-2011: BCI2000 team and many external contributors ]
// 
// BCI2000 is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
// 
// BCI2000 is distributed in the hope that it will be useful, but
//                         WITHOUT ANY WARRANTY
// - without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along with
// this program.  If not, see <http://www.gnu.org/licenses/>.
// 
// $END_BCI2000_LICENSE$
////////////////////////////////////////////////////////////////////////
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <cstring>
#include <cstdio>
#include "ArithmeticExpression.h"
#include "BCIError.h"

// Disable compiler warnings for generated code.
#ifdef __BORLANDC__
# pragma warn -8004
#elif defined( _MSC_VER )
# pragma warning (disable:4065)
#endif


using namespace std;



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 54 "ExpressionParser.y"
typedef union YYSTYPE {
  double               value;
  std::string*         str;
  std::vector<double>* list;
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 143 "ExpressionParser.cpp"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */
#line 61 "ExpressionParser.y"

namespace ExpressionParser
{


/* Line 214 of yacc.c.  */
#line 159 "ExpressionParser.cpp"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  22
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   231

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  29
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  8
/* YYNRULES -- Number of rules. */
#define YYNRULES  44
/* YYNRULES -- Number of states. */
#define YYNSTATES  103

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   262

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    13,    27,     2,     2,     2,     9,    28,
      24,    25,    18,    17,    26,    16,    22,    19,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     8,    23,
      15,    11,    14,     7,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    21,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    10,     2,    12,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,    20
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned char yyprhs[] =
{
       0,     0,     3,     4,     6,     8,    12,    14,    18,    22,
      26,    30,    33,    37,    42,    47,    52,    57,    62,    66,
      70,    75,    80,    83,    86,    90,    96,    98,   102,   107,
     114,   119,   126,   130,   134,   136,   139,   141,   143,   145,
     146,   148,   152,   157,   164
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      30,     0,    -1,    -1,    31,    -1,    36,    -1,    30,    23,
      30,    -1,     3,    -1,    31,    17,    31,    -1,    31,    16,
      31,    -1,    31,    18,    31,    -1,    31,    19,    31,    -1,
      16,    31,    -1,    31,    21,    31,    -1,    31,     9,     9,
      31,    -1,    31,    10,    10,    31,    -1,    31,    11,    11,
      31,    -1,    31,    13,    11,    31,    -1,    31,    12,    11,
      31,    -1,    31,    14,    31,    -1,    31,    15,    31,    -1,
      31,    14,    11,    31,    -1,    31,    15,    11,    31,    -1,
      12,    31,    -1,    13,    31,    -1,    24,    31,    25,    -1,
      31,     7,    31,     8,    31,    -1,     4,    -1,    31,    22,
       4,    -1,     4,    24,    35,    25,    -1,    31,    22,     4,
      24,    35,    25,    -1,     5,    24,    34,    25,    -1,     6,
      24,    33,    26,    33,    25,    -1,    27,     4,    27,    -1,
      28,     4,    28,    -1,    31,    -1,    31,     4,    -1,    32,
      -1,     4,    -1,    32,    -1,    -1,    31,    -1,    35,    26,
      31,    -1,     4,     8,    11,    31,    -1,    31,    22,     4,
       8,    11,    31,    -1,     5,    24,    34,    25,     8,    11,
      31,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned char yyrline[] =
{
       0,    84,    84,    85,    86,    87,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   111,   112,   113,   114,
     116,   117,   121,   122,   125,   126,   127,   131,   132,   135,
     136,   137,   141,   142,   143
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "NAME", "STATE", "SIGNAL_", 
  "'?'", "':'", "'&'", "'|'", "'='", "'~'", "'!'", "'>'", "'<'", "'-'", 
  "'+'", "'*'", "'/'", "NEG", "'^'", "'.'", "';'", "'('", "')'", "','", 
  "'\"'", "'''", "$accept", "input", "exp", "quoted", "addr", "statename", 
  "list", "assignment", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,    63,    58,    38,
     124,    61,   126,    33,    62,    60,    45,    43,    42,    47,
     262,    94,    46,    59,    40,    41,    44,    34,    39
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    29,    30,    30,    30,    30,    31,    31,    31,    31,
      31,    31,    31,    31,    31,    31,    31,    31,    31,    31,
      31,    31,    31,    31,    31,    31,    31,    31,    31,    31,
      31,    31,    32,    32,    33,    33,    33,    34,    34,    35,
      35,    35,    36,    36,    36
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     0,     1,     1,     3,     1,     3,     3,     3,
       3,     2,     3,     4,     4,     4,     4,     4,     3,     3,
       4,     4,     2,     2,     3,     5,     1,     3,     4,     6,
       4,     6,     3,     3,     1,     2,     1,     1,     1,     0,
       1,     3,     4,     6,     7
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       2,     6,    26,     0,     0,     0,     0,     0,     0,     0,
       3,     4,     0,    39,     0,     0,    26,     0,    22,    23,
      11,     0,     1,     2,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    40,
       0,    37,     0,     0,    38,     0,    34,    36,     0,     0,
       0,    24,     5,     0,     0,     0,     0,     0,     0,     0,
      18,     0,    19,     8,     7,     9,    10,    12,    27,    42,
      28,     0,     0,     0,    30,    35,     0,     0,    27,     0,
      13,    14,    15,    17,    16,    20,    21,     0,    39,    41,
      32,    33,     0,     0,    30,    25,     0,     0,     0,    31,
      43,    29,    44
};

/* YYDEFGOTO[NTERM-NUM]. */
static const yysigned_char yydefgoto[] =
{
      -1,     9,    10,    44,    48,    45,    40,    11
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -20
static const short yypact[] =
{
      95,   -20,    -2,   -19,   -15,   100,   100,   100,   100,    17,
     167,   -20,     5,   100,    11,     8,    -6,    10,    36,    36,
      36,   116,   -20,    95,   100,    28,    35,    37,    44,    59,
      56,    73,   100,   100,   100,   100,   100,    69,   100,   183,
      38,   -20,    71,    77,   -20,    57,   135,   -20,    64,    11,
      88,   -20,   -20,   151,   100,   100,   100,   100,   100,   100,
      25,   100,    25,    96,    96,    36,    36,    36,    -1,   183,
     -20,   100,    67,    68,    87,   -20,     8,    84,    78,   100,
     209,   209,    25,    25,    25,    25,    25,    99,   100,   183,
     -20,   -20,   109,    97,   -20,   197,   100,    62,   100,   -20,
     183,   -20,   183
};

/* YYPGOTO[NTERM-NUM].  */
static const yysigned_char yypgoto[] =
{
     -20,    98,    -5,   -11,    60,    91,    55,   -20
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned char yytable[] =
{
      18,    19,    20,    21,    47,    14,    12,    87,    39,    15,
      46,     1,    16,    17,     4,    41,    38,    22,    13,    53,
       5,     6,    13,    88,     7,    60,    62,    63,    64,    65,
      66,    67,     8,    69,    49,    42,    43,    54,    42,    43,
      23,    32,    33,    34,    35,    55,    36,    50,    56,    80,
      81,    82,    83,    84,    85,    57,    86,    36,    50,     1,
      16,    17,     4,    70,    71,    47,    89,    59,     5,     6,
      58,    46,     7,    68,    95,    72,     1,    16,    17,     4,
       8,    73,    74,    39,    61,     5,     6,   101,    71,     7,
      76,   100,    78,   102,    90,    92,    91,     8,     1,     2,
       3,     4,    88,     1,    16,    17,     4,     5,     6,    94,
      96,     7,     5,     6,    34,    35,     7,    36,    50,     8,
      98,    52,    99,    24,     8,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    93,    36,    50,    75,
      77,    51,    24,    97,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,     0,    36,    50,    24,    79,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,     0,    36,    50,    24,     0,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,     0,    36,    37,
      24,     0,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,     0,    36,    50,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,     0,    36,    50,
      27,    28,    29,    30,    31,    32,    33,    34,    35,     0,
      36,    50
};

static const yysigned_char yycheck[] =
{
       5,     6,     7,     8,    15,    24,     8,     8,    13,    24,
      15,     3,     4,     5,     6,     4,    11,     0,    24,    24,
      12,    13,    24,    24,    16,    30,    31,    32,    33,    34,
      35,    36,    24,    38,    24,    27,    28,     9,    27,    28,
      23,    16,    17,    18,    19,    10,    21,    22,    11,    54,
      55,    56,    57,    58,    59,    11,    61,    21,    22,     3,
       4,     5,     6,    25,    26,    76,    71,    11,    12,    13,
      11,    76,    16,     4,    79,     4,     3,     4,     5,     6,
      24,     4,    25,    88,    11,    12,    13,    25,    26,    16,
      26,    96,     4,    98,    27,     8,    28,    24,     3,     4,
       5,     6,    24,     3,     4,     5,     6,    12,    13,    25,
      11,    16,    12,    13,    18,    19,    16,    21,    22,    24,
      11,    23,    25,     7,    24,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    76,    21,    22,     4,
      49,    25,     7,    88,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,     7,    -1,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
       7,    -1,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     3,     4,     5,     6,    12,    13,    16,    24,    30,
      31,    36,     8,    24,    24,    24,     4,     5,    31,    31,
      31,    31,     0,    23,     7,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    21,    22,    11,    31,
      35,     4,    27,    28,    32,    34,    31,    32,    33,    24,
      22,    25,    30,    31,     9,    10,    11,    11,    11,    11,
      31,    11,    31,    31,    31,    31,    31,    31,     4,    31,
      25,    26,     4,     4,    25,     4,    26,    34,     4,     8,
      31,    31,    31,    31,    31,    31,    31,     8,    24,    31,
      27,    28,     8,    33,    25,    31,    11,    35,    11,    25,
      31,    25,    31
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrlab1


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror (pInstance, "syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)         \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, pInstance)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (cinluded).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse ( ::ArithmeticExpression* pInstance );
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */






/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse ( ::ArithmeticExpression* pInstance )
#else
int
yyparse (pInstance)
     ::ArithmeticExpression* pInstance ;
#endif
#endif
{
  /* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 84 "ExpressionParser.y"
    { pInstance->mValue = 0; ;}
    break;

  case 3:
#line 85 "ExpressionParser.y"
    { pInstance->mValue = yyvsp[0].value; ;}
    break;

  case 4:
#line 86 "ExpressionParser.y"
    { pInstance->mValue = yyvsp[0].value; ;}
    break;

  case 5:
#line 87 "ExpressionParser.y"
    { pInstance->mValue = yyvsp[0].value; ;}
    break;

  case 6:
#line 90 "ExpressionParser.y"
    { yyval.value = yyvsp[0].value;       ;}
    break;

  case 7:
#line 91 "ExpressionParser.y"
    { yyval.value = yyvsp[-2].value + yyvsp[0].value;  ;}
    break;

  case 8:
#line 92 "ExpressionParser.y"
    { yyval.value = yyvsp[-2].value - yyvsp[0].value;  ;}
    break;

  case 9:
#line 93 "ExpressionParser.y"
    { yyval.value = yyvsp[-2].value * yyvsp[0].value;  ;}
    break;

  case 10:
#line 94 "ExpressionParser.y"
    { yyval.value = yyvsp[-2].value / yyvsp[0].value;  ;}
    break;

  case 11:
#line 95 "ExpressionParser.y"
    { yyval.value = -yyvsp[0].value;      ;}
    break;

  case 12:
#line 96 "ExpressionParser.y"
    { yyval.value = ::pow( yyvsp[-2].value, yyvsp[0].value ); ;}
    break;

  case 13:
#line 97 "ExpressionParser.y"
    { yyval.value = yyvsp[-3].value && yyvsp[0].value; ;}
    break;

  case 14:
#line 98 "ExpressionParser.y"
    { yyval.value = yyvsp[-3].value || yyvsp[0].value; ;}
    break;

  case 15:
#line 99 "ExpressionParser.y"
    { yyval.value = yyvsp[-3].value == yyvsp[0].value; ;}
    break;

  case 16:
#line 100 "ExpressionParser.y"
    { yyval.value = yyvsp[-3].value != yyvsp[0].value; ;}
    break;

  case 17:
#line 101 "ExpressionParser.y"
    { yyval.value = yyvsp[-3].value != yyvsp[0].value; ;}
    break;

  case 18:
#line 102 "ExpressionParser.y"
    { yyval.value = yyvsp[-2].value > yyvsp[0].value;  ;}
    break;

  case 19:
#line 103 "ExpressionParser.y"
    { yyval.value = yyvsp[-2].value < yyvsp[0].value;  ;}
    break;

  case 20:
#line 104 "ExpressionParser.y"
    { yyval.value = yyvsp[-3].value >= yyvsp[0].value; ;}
    break;

  case 21:
#line 105 "ExpressionParser.y"
    { yyval.value = yyvsp[-3].value <= yyvsp[0].value; ;}
    break;

  case 22:
#line 106 "ExpressionParser.y"
    { yyval.value = !yyvsp[0].value;      ;}
    break;

  case 23:
#line 107 "ExpressionParser.y"
    { yyval.value = !yyvsp[0].value;      ;}
    break;

  case 24:
#line 108 "ExpressionParser.y"
    { yyval.value = yyvsp[-1].value;       ;}
    break;

  case 25:
#line 109 "ExpressionParser.y"
    { yyval.value = yyvsp[-4].value ? yyvsp[-2].value : yyvsp[0].value ;}
    break;

  case 26:
#line 111 "ExpressionParser.y"
    { yyval.value = pInstance->Variable( *yyvsp[0].str ); ;}
    break;

  case 27:
#line 112 "ExpressionParser.y"
    { yyval.value = pInstance->MemberVariable( yyvsp[-2].value, *yyvsp[0].str ); ;}
    break;

  case 28:
#line 113 "ExpressionParser.y"
    { yyval.value = pInstance->Function( *yyvsp[-3].str, *yyvsp[-1].list ); ;}
    break;

  case 29:
#line 114 "ExpressionParser.y"
    { yyval.value = pInstance->MemberFunction( yyvsp[-5].value, *yyvsp[-3].str, *yyvsp[-1].list ); ;}
    break;

  case 30:
#line 116 "ExpressionParser.y"
    { yyval.value = pInstance->State( *yyvsp[-1].str ); ;}
    break;

  case 31:
#line 117 "ExpressionParser.y"
    { yyval.value = pInstance->Signal( *yyvsp[-3].str, *yyvsp[-1].str ); ;}
    break;

  case 32:
#line 121 "ExpressionParser.y"
    { yyval.str = yyvsp[-1].str; ;}
    break;

  case 33:
#line 122 "ExpressionParser.y"
    { yyval.str = yyvsp[-1].str; ;}
    break;

  case 34:
#line 125 "ExpressionParser.y"
    { ostringstream oss; oss << yyvsp[0].value; yyval.str = pInstance->Allocate( &oss.str() ); ;}
    break;

  case 35:
#line 126 "ExpressionParser.y"
    { ostringstream oss; oss << yyvsp[-1].value << *yyvsp[0].str; yyval.str = pInstance->Allocate( &oss.str() ); ;}
    break;

  case 36:
#line 127 "ExpressionParser.y"
    { yyval.str = yyvsp[0].str; ;}
    break;

  case 37:
#line 131 "ExpressionParser.y"
    { yyval.str = yyvsp[0].str; ;}
    break;

  case 38:
#line 132 "ExpressionParser.y"
    { yyval.str = yyvsp[0].str; ;}
    break;

  case 39:
#line 135 "ExpressionParser.y"
    { yyval.list = pInstance->Allocate< vector<double> >(); ;}
    break;

  case 40:
#line 136 "ExpressionParser.y"
    { yyval.list = pInstance->Allocate< vector<double> >(); yyval.list->push_back( yyvsp[0].value ); ;}
    break;

  case 41:
#line 137 "ExpressionParser.y"
    { yyval.list = yyvsp[-2].list; yyval.list->push_back( yyvsp[0].value ); ;}
    break;

  case 42:
#line 141 "ExpressionParser.y"
    { yyval.value = yyvsp[0].value; pInstance->VariableAssignment( *yyvsp[-3].str, yyvsp[0].value ); ;}
    break;

  case 43:
#line 142 "ExpressionParser.y"
    { yyval.value = yyvsp[0].value; pInstance->MemberVariableAssignment( yyvsp[-5].value, *yyvsp[-3].str, yyvsp[0].value ); ;}
    break;

  case 44:
#line 144 "ExpressionParser.y"
    { yyval.value = yyvsp[0].value; pInstance->StateAssignment( *yyvsp[-4].str, yyvsp[0].value ); ;}
    break;


    }

/* Line 999 of yacc.c.  */
#line 1350 "ExpressionParser.cpp"

  yyvsp -= yylen;
  yyssp -= yylen;


  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
		      }
		}
	      yyerror (pInstance, yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror (pInstance, "syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror (pInstance, "syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
	  /* Pop the error token.  */
          YYPOPSTACK;
	  /* Pop the rest of the stack.  */
	  while (yyss < yyssp)
	    {
	      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
	      yydestruct (yystos[*yyssp], yyvsp);
	      YYPOPSTACK;
	    }
	  YYABORT;
        }

      YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
      yydestruct (yytoken, &yylval);
      yychar = YYEMPTY;

    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      yyvsp--;
      yystate = *--yyssp;

      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror (pInstance, "parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 147 "ExpressionParser.y"


  int
  yylex( YYSTYPE* pLval, ArithmeticExpression* pInstance )
  {
    int token = -1;

    pInstance->mInput >> ws;
    int c = pInstance->mInput.peek();
    if( c == EOF )
      token = 0;
    else if( ::isdigit( c ) )
    {
      if( pInstance->mInput >> pLval->value )
        token = NUMBER;
    }
    else if( ::isalnum( c ) )
    {
      pLval->str = pInstance->Allocate<string>();
      while( ::isalnum( c ) )
      {
        *pLval->str += c;
        pInstance->mInput.ignore();
        c = pInstance->mInput.peek();
      }
      if( ::stricmp( pLval->str->c_str(), "state" ) == 0 )
        token = STATE;
      else if( ::stricmp( pLval->str->c_str(), "signal" ) == 0 )
        token = SIGNAL_;
      else
        token = NAME;
    }
    else
    {
      pInstance->mInput.ignore();
      token = c;
    }
    return token;
  }

  void
  yyerror( ArithmeticExpression* pInstance, const char* pError )
  {
    pInstance->mErrors << pError << endl;
  }

} // namespace ExpressionParser



