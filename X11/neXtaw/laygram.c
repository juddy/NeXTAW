
/*  A Bison parser, made from laygram.y
 by  GNU Bison version 1.27
  */

#define YYBISON 1  /* Identify Bison output.  */

#define	OC	257
#define	CC	258
#define	OA	259
#define	CA	260
#define	OP	261
#define	CP	262
#define	NAME	263
#define	NUMBER	264
#define	INFINITY	265
#define	VERTICAL	266
#define	HORIZONTAL	267
#define	EQUAL	268
#define	DOLLAR	269
#define	PLUS	270
#define	MINUS	271
#define	TIMES	272
#define	DIVIDE	273
#define	PERCENTOF	274
#define	PERCENT	275
#define	WIDTH	276
#define	HEIGHT	277
#define	UMINUS	278
#define	UPLUS	279

#line 1 "laygram.y"

#include    <X11/Xlib.h>
#include    <X11/Xresource.h>
#include    <stdio.h>
#include    <X11/IntrinsicP.h>
#include    <X11/cursorfont.h>
#include    <X11/StringDefs.h>

#include    <X11/Xmu/Misc.h>
#include    <X11/Xmu/Converters.h>
#include    "LayoutP.h"

static LayoutPtr    *dest;


#line 17 "laygram.y"
typedef union {
    int		    ival;
    XrmQuark	    qval;
    BoxPtr	    bval;
    BoxParamsPtr    pval;
    GlueRec	    gval;
    LayoutDirection lval;
    ExprPtr	    eval;
    Operator	    oval;
} YYSTYPE;
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		68
#define	YYFLAG		-32768
#define	YYNTBASE	26

#define YYTRANSLATE(x) ((unsigned)(x) <= 279 ? LayYYtranslate[x] : 39)

static const char LayYYtranslate[] = {     0,
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
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     3,     4,     5,     6,
     7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
    17,    18,    19,    20,    21,    22,    23,    24,    25
};

#if YYDEBUG != 0
static const short LayYYprhs[] = {     0,
     0,     2,     5,     8,    12,    14,    19,    22,    24,    32,
    33,    38,    39,    42,    43,    46,    47,    50,    52,    54,
    57,    60,    62,    65,    68,    72,    75,    77,    80,    84,
    88,    92,    96,   100,   103,   106,   108,   110
};

static const short LayYYrhs[] = {    28,
     0,     9,    30,     0,    35,    31,     0,     9,    14,    35,
     0,    28,     0,    38,     3,    29,     4,     0,    27,    29,
     0,    27,     0,     5,    32,    33,    18,    32,    33,     6,
     0,     0,     5,    32,    33,     6,     0,     0,    16,    34,
     0,     0,    17,    34,     0,     0,    36,    11,     0,    36,
     0,    11,     0,    17,    36,     0,    16,    36,     0,    36,
     0,    22,     9,     0,    23,     9,     0,     7,    37,     8,
     0,    36,    21,     0,    10,     0,    15,     9,     0,    37,
    16,    37,     0,    37,    17,    37,     0,    37,    18,    37,
     0,    37,    19,    37,     0,    37,    20,    37,     0,    17,
    37,     0,    16,    37,     0,    36,     0,    12,     0,    13,
     0
};

#endif

#if YYDEBUG != 0
static const short LayYYrline[] = { 0,
    49,    52,    62,    72,    81,    86,   112,   117,   120,   130,
   141,   151,   162,   164,   167,   169,   172,   174,   176,   179,
   186,   188,   190,   195,   200,   202,   209,   214,   220,   228,
   230,   232,   234,   236,   243,   245,   247,   249
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const LayYYtname[] = {   "$","error","$undefined.","OC","CC",
"OA","CA","OP","CP","NAME","NUMBER","INFINITY","VERTICAL","HORIZONTAL","EQUAL",
"DOLLAR","PLUS","MINUS","TIMES","DIVIDE","PERCENTOF","PERCENT","WIDTH","HEIGHT",
"UMINUS","UPLUS","layout","box","compositebox","boxes","bothparams","oneparams",
"opStretch","opShrink","glue","signedExpr","simpleExpr","expr","orientation", NULL
};
#endif

static const short LayYYr1[] = {     0,
    26,    27,    27,    27,    27,    28,    29,    29,    30,    30,
    31,    31,    32,    32,    33,    33,    34,    34,    34,    35,
    35,    35,    36,    36,    36,    36,    36,    36,    37,    37,
    37,    37,    37,    37,    37,    37,    38,    38
};

static const short LayYYr2[] = {     0,
     1,     2,     2,     3,     1,     4,     2,     1,     7,     0,
     4,     0,     2,     0,     2,     0,     2,     1,     1,     2,
     2,     1,     2,     2,     3,     2,     1,     2,     3,     3,
     3,     3,     3,     2,     2,     1,     1,     1
};

static const short LayYYdefact[] = {     0,
    37,    38,     1,     0,     0,     0,    10,    27,     0,     0,
     0,     0,     0,     8,     5,     0,    12,    22,     0,     0,
    36,     0,    14,     0,     2,    28,    21,    20,    23,    24,
     7,     6,    14,     3,    26,    35,    34,    25,     0,     0,
     0,     0,     0,     0,    16,     4,    16,    29,    30,    31,
    32,    33,    19,    13,    18,     0,     0,     0,    17,    15,
    14,    11,    16,     0,     9,     0,     0,     0
};

static const short LayYYdefgoto[] = {    66,
    14,    15,    16,    25,    34,    45,    57,    54,    17,    21,
    22,     4
};

static const short LayYYpact[] = {    -2,
-32768,-32768,-32768,     5,    21,    25,     7,-32768,     4,    43,
    43,     6,     9,    21,-32768,    10,    11,    24,    25,    25,
    24,    61,    36,    39,-32768,-32768,    24,    24,-32768,-32768,
-32768,-32768,    36,-32768,-32768,-32768,-32768,-32768,    25,    25,
    25,    25,    25,    53,    40,-32768,    40,    52,    52,-32768,
-32768,-32768,-32768,-32768,    -4,    53,    41,    67,-32768,-32768,
    36,-32768,    40,    68,-32768,    27,    82,-32768
};

static const short LayYYpgoto[] = {-32768,
-32768,    83,    70,-32768,-32768,   -32,   -43,    29,    62,    -5,
   -17,-32768
};


#define	YYLAST		86


static const short LayYYtable[] = {    18,
    47,    36,    37,    58,    27,    28,    59,     5,    18,     1,
     2,    23,    26,    32,    29,    33,    35,    30,    18,    64,
    24,    48,    49,    50,    51,    52,    67,     6,    63,     7,
     8,     6,     1,     2,     8,     9,    10,    11,    55,     9,
    19,    20,    12,    13,    35,     6,    12,    13,     8,     6,
    55,    44,     8,     9,    10,    11,    56,     9,    61,     6,
    12,    13,     8,    53,    12,    13,     0,     9,    38,    41,
    42,    43,    62,    65,    12,    13,    39,    40,    41,    42,
    43,    68,     3,    31,    60,    46
};

static const short LayYYcheck[] = {     5,
    33,    19,    20,    47,    10,    11,    11,     3,    14,    12,
    13,     5,     9,     4,     9,     5,    21,     9,    24,    63,
    14,    39,    40,    41,    42,    43,     0,     7,    61,     9,
    10,     7,    12,    13,    10,    15,    16,    17,    44,    15,
    16,    17,    22,    23,    21,     7,    22,    23,    10,     7,
    56,    16,    10,    15,    16,    17,    17,    15,    18,     7,
    22,    23,    10,    11,    22,    23,    -1,    15,     8,    18,
    19,    20,     6,     6,    22,    23,    16,    17,    18,    19,
    20,     0,     0,    14,    56,    24
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison.simple"
/* This file comes from bison-1.27.  */

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

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

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

#ifndef YYSTACK_USE_ALLOCA
#ifdef alloca
#define YYSTACK_USE_ALLOCA
#else /* alloca not defined */
#ifdef __GNUC__
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi) || (defined (__sun) && defined (__i386))
#define YYSTACK_USE_ALLOCA
#include <alloca.h>
#else /* not sparc */
/* We think this test detects Watcom and Microsoft C.  */
/* This used to test MSDOS, but that is a bad idea
   since that symbol is in the user namespace.  */
#if (defined (_MSDOS) || defined (_MSDOS_)) && !defined (__TURBOC__)
#if 0 /* No need for malloc.h, which pollutes the namespace;
	 instead, just don't use alloca.  */
#include <malloc.h>
#endif
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
/* I don't know what this was needed for, but it pollutes the namespace.
   So I turned it off.   rms, 2 May 1997.  */
/* #include <malloc.h>  */
 #pragma alloca
#define YYSTACK_USE_ALLOCA
#else /* not MSDOS, or __TURBOC__, or _AIX */
#if 0
#ifdef __hpux /* haible@ilog.fr says this works for HPUX 9.05 and up,
		 and on HPUX 10.  Eventually we can turn this on.  */
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#endif /* __hpux */
#endif
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc */
#endif /* not GNU C */
#endif /* alloca not defined */
#endif /* YYSTACK_USE_ALLOCA not defined */

#ifdef YYSTACK_USE_ALLOCA
#define YYSTACK_ALLOC alloca
#else
#define YYSTACK_ALLOC malloc
#endif

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define LayYYerrok		(LayYYerrstatus = 0)
#define LayYYclearin	(LayYYchar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto LayYYacceptlab
#define YYABORT 	goto LayYYabortlab
#define YYERROR		goto LayYYerrlab1
/* Like YYERROR except do call LayYYerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto LayYYerrlab
#define YYRECOVERING()  (!!LayYYerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (LayYYchar == YYEMPTY && LayYYlen == 1)				\
    { LayYYchar = (token), LayYYlval = (value);			\
      LayYYchar1 = YYTRANSLATE (LayYYchar);				\
      YYPOPSTACK;						\
      goto LayYYbackup;						\
    }								\
  else								\
    { LayYYerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		LayYYlex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		LayYYlex(&LayYYlval, &LayYYlloc, YYLEX_PARAM)
#else
#define YYLEX		LayYYlex(&LayYYlval, &LayYYlloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		LayYYlex(&LayYYlval, YYLEX_PARAM)
#else
#define YYLEX		LayYYlex(&LayYYlval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	LayYYchar;			/*  the lookahead symbol		*/
YYSTYPE	LayYYlval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE LayYYlloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int LayYYnerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int LayYYdebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Define __LayYY_memcpy.  Note that the size argument
   should be passed with type unsigned int, because that is what the non-GCC
   definitions require.  With GCC, __builtin_memcpy takes an arg
   of type size_t, but it can handle unsigned int.  */

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __LayYY_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__LayYY_memcpy (to, from, count)
     char *to;
     char *from;
     unsigned int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__LayYY_memcpy (char *to, char *from, unsigned int count)
{
  register char *t = to;
  register char *f = from;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 216 "/usr/share/bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into LayYYparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
#ifdef YYPARSE_PARAM
int LayYYparse (void *);
#else
int LayYYparse (void);
#endif
#endif

int
LayYYparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int LayYYstate;
  register int LayYYn;
  register short *LayYYssp;
  register YYSTYPE *LayYYvsp;
  int LayYYerrstatus;	/*  number of tokens to shift before error messages enabled */
  int LayYYchar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	LayYYssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE LayYYvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *LayYYss = LayYYssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *LayYYvs = LayYYvsa;	/*  to allow LayYYoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE LayYYlsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *LayYYls = LayYYlsa;
  YYLTYPE *LayYYlsp;

#define YYPOPSTACK   (LayYYvsp--, LayYYssp--, LayYYlsp--)
#else
#define YYPOPSTACK   (LayYYvsp--, LayYYssp--)
#endif

  int LayYYstacksize = YYINITDEPTH;
  int LayYYfree_stacks = 0;

#ifdef YYPURE
  int LayYYchar;
  YYSTYPE LayYYlval;
  int LayYYnerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE LayYYlloc;
#endif
#endif

  YYSTYPE LayYYval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int LayYYlen;

#if YYDEBUG != 0
  if (LayYYdebug)
    fprintf(stderr, "Starting parse\n");
#endif

  LayYYstate = 0;
  LayYYerrstatus = 0;
  LayYYnerrs = 0;
  LayYYchar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  LayYYssp = LayYYss - 1;
  LayYYvsp = LayYYvs;
#ifdef YYLSP_NEEDED
  LayYYlsp = LayYYls;
#endif

/* Push a new state, which is found in  LayYYstate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
LayYYnewstate:

  *++LayYYssp = LayYYstate;

  if (LayYYssp >= LayYYss + LayYYstacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *LayYYvs1 = LayYYvs;
      short *LayYYss1 = LayYYss;
#ifdef YYLSP_NEEDED
      YYLTYPE *LayYYls1 = LayYYls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = LayYYssp - LayYYss + 1;

#ifdef LayYYoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if LayYYoverflow is a macro.  */
      LayYYoverflow("parser stack overflow",
		 &LayYYss1, size * sizeof (*LayYYssp),
		 &LayYYvs1, size * sizeof (*LayYYvsp),
		 &LayYYls1, size * sizeof (*LayYYlsp),
		 &LayYYstacksize);
#else
      LayYYoverflow("parser stack overflow",
		 &LayYYss1, size * sizeof (*LayYYssp),
		 &LayYYvs1, size * sizeof (*LayYYvsp),
		 &LayYYstacksize);
#endif

      LayYYss = LayYYss1; LayYYvs = LayYYvs1;
#ifdef YYLSP_NEEDED
      LayYYls = LayYYls1;
#endif
#else /* no LayYYoverflow */
      /* Extend the stack our own way.  */
      if (LayYYstacksize >= YYMAXDEPTH)
	{
	  LayYYerror("parser stack overflow");
	  if (LayYYfree_stacks)
	    {
	      free (LayYYss);
	      free (LayYYvs);
#ifdef YYLSP_NEEDED
	      free (LayYYls);
#endif
	    }
	  return 2;
	}
      LayYYstacksize *= 2;
      if (LayYYstacksize > YYMAXDEPTH)
	LayYYstacksize = YYMAXDEPTH;
#ifndef YYSTACK_USE_ALLOCA
      LayYYfree_stacks = 1;
#endif
      LayYYss = (short *) YYSTACK_ALLOC (LayYYstacksize * sizeof (*LayYYssp));
      __LayYY_memcpy ((char *)LayYYss, (char *)LayYYss1,
		   size * (unsigned int) sizeof (*LayYYssp));
      LayYYvs = (YYSTYPE *) YYSTACK_ALLOC (LayYYstacksize * sizeof (*LayYYvsp));
      __LayYY_memcpy ((char *)LayYYvs, (char *)LayYYvs1,
		   size * (unsigned int) sizeof (*LayYYvsp));
#ifdef YYLSP_NEEDED
      LayYYls = (YYLTYPE *) YYSTACK_ALLOC (LayYYstacksize * sizeof (*LayYYlsp));
      __LayYY_memcpy ((char *)LayYYls, (char *)LayYYls1,
		   size * (unsigned int) sizeof (*LayYYlsp));
#endif
#endif /* no LayYYoverflow */

      LayYYssp = LayYYss + size - 1;
      LayYYvsp = LayYYvs + size - 1;
#ifdef YYLSP_NEEDED
      LayYYlsp = LayYYls + size - 1;
#endif

#if YYDEBUG != 0
      if (LayYYdebug)
	fprintf(stderr, "Stack size increased to %d\n", LayYYstacksize);
#endif

      if (LayYYssp >= LayYYss + LayYYstacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (LayYYdebug)
    fprintf(stderr, "Entering state %d\n", LayYYstate);
#endif

  goto LayYYbackup;
 LayYYbackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* LayYYresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  LayYYn = LayYYpact[LayYYstate];
  if (LayYYn == YYFLAG)
    goto LayYYdefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* LayYYchar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (LayYYchar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (LayYYdebug)
	fprintf(stderr, "Reading a token: ");
#endif
      LayYYchar = YYLEX;
    }

  /* Convert token to internal form (in LayYYchar1) for indexing tables with */

  if (LayYYchar <= 0)		/* This means end of input. */
    {
      LayYYchar1 = 0;
      LayYYchar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (LayYYdebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      LayYYchar1 = YYTRANSLATE(LayYYchar);

#if YYDEBUG != 0
      if (LayYYdebug)
	{
	  fprintf (stderr, "Next token is %d (%s", LayYYchar, LayYYtname[LayYYchar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, LayYYchar, LayYYlval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  LayYYn += LayYYchar1;
  if (LayYYn < 0 || LayYYn > YYLAST || LayYYcheck[LayYYn] != LayYYchar1)
    goto LayYYdefault;

  LayYYn = LayYYtable[LayYYn];

  /* LayYYn is what to do for this token type in this state.
     Negative => reduce, -LayYYn is rule number.
     Positive => shift, LayYYn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (LayYYn < 0)
    {
      if (LayYYn == YYFLAG)
	goto LayYYerrlab;
      LayYYn = -LayYYn;
      goto LayYYreduce;
    }
  else if (LayYYn == 0)
    goto LayYYerrlab;

  if (LayYYn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (LayYYdebug)
    fprintf(stderr, "Shifting token %d (%s), ", LayYYchar, LayYYtname[LayYYchar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (LayYYchar != YYEOF)
    LayYYchar = YYEMPTY;

  *++LayYYvsp = LayYYlval;
#ifdef YYLSP_NEEDED
  *++LayYYlsp = LayYYlloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (LayYYerrstatus) LayYYerrstatus--;

  LayYYstate = LayYYn;
  goto LayYYnewstate;

/* Do the default action for the current state.  */
LayYYdefault:

  LayYYn = LayYYdefact[LayYYstate];
  if (LayYYn == 0)
    goto LayYYerrlab;

/* Do a reduction.  LayYYn is the number of a rule to reduce with.  */
LayYYreduce:
  LayYYlen = LayYYr2[LayYYn];
  if (LayYYlen > 0)
    LayYYval = LayYYvsp[1-LayYYlen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (LayYYdebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       LayYYn, LayYYrline[LayYYn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = LayYYprhs[LayYYn]; LayYYrhs[i] > 0; i++)
	fprintf (stderr, "%s ", LayYYtname[LayYYrhs[i]]);
      fprintf (stderr, " -> %s\n", LayYYtname[LayYYr1[LayYYn]]);
    }
#endif


  switch (LayYYn) {

case 1:
#line 50 "laygram.y"
{ *dest = LayYYvsp[0].bval; ;
    break;}
case 2:
#line 53 "laygram.y"
{
			BoxPtr	box = New(LBoxRec);
			box->nextSibling = 0;
			box->type = WidgetBox;
			box->params = *LayYYvsp[0].pval;
			Dispose (LayYYvsp[0].pval);
			box->u.widget.quark = LayYYvsp[-1].qval;
			LayYYval.bval = box;
		    ;
    break;}
case 3:
#line 63 "laygram.y"
{
			BoxPtr	box = New(LBoxRec);
			box->nextSibling = 0;
			box->type = GlueBox;
			box->params = *LayYYvsp[0].pval;
			Dispose (LayYYvsp[0].pval);
			box->u.glue.expr = LayYYvsp[-1].eval;
			LayYYval.bval = box;
		    ;
    break;}
case 4:
#line 73 "laygram.y"
{
			BoxPtr	box = New(LBoxRec);
			box->nextSibling = 0;
			box->type = VariableBox;
			box->u.variable.quark = LayYYvsp[-2].qval;
			box->u.variable.expr = LayYYvsp[0].eval;
			LayYYval.bval = box;
		    ;
    break;}
case 5:
#line 82 "laygram.y"
{
			LayYYval.bval = LayYYvsp[0].bval;
		    ;
    break;}
case 6:
#line 87 "laygram.y"
{
			BoxPtr	box = New(LBoxRec);
			BoxPtr	child;

			box->nextSibling = 0;
			box->parent = 0;
			box->type = BoxBox;
			box->u.box.dir = LayYYvsp[-3].lval;
			box->u.box.firstChild = LayYYvsp[-1].bval;
			for (child = LayYYvsp[-1].bval; child; child = child->nextSibling) 
			{
			    if (child->type == GlueBox) 
			    {
				child->params.stretch[!LayYYvsp[-3].lval].expr = 0;
				child->params.shrink[!LayYYvsp[-3].lval].expr = 0;
				child->params.stretch[!LayYYvsp[-3].lval].order = 100000;
				child->params.shrink[!LayYYvsp[-3].lval].order = 100000;
				child->params.stretch[!LayYYvsp[-3].lval].value = 1;
				child->params.shrink[!LayYYvsp[-3].lval].value = 1;
			    }
			    child->parent = box;
			}
			LayYYval.bval = box;
		    ;
    break;}
case 7:
#line 113 "laygram.y"
{ 
			LayYYvsp[-1].bval->nextSibling = LayYYvsp[0].bval;
			LayYYval.bval = LayYYvsp[-1].bval;
		    ;
    break;}
case 8:
#line 118 "laygram.y"
{	LayYYval.bval = LayYYvsp[0].bval; ;
    break;}
case 9:
#line 121 "laygram.y"
{	
			BoxParamsPtr	p = New(BoxParamsRec);
			
			p->stretch[LayoutHorizontal] = LayYYvsp[-5].gval;
			p->shrink[LayoutHorizontal] = LayYYvsp[-4].gval;
			p->stretch[LayoutVertical] = LayYYvsp[-2].gval;
			p->shrink[LayoutVertical] = LayYYvsp[-1].gval;
			LayYYval.pval = p;
		    ;
    break;}
case 10:
#line 131 "laygram.y"
{	
			BoxParamsPtr	p = New(BoxParamsRec);
			
			ZeroGlue (p->stretch[LayoutHorizontal]);
			ZeroGlue (p->shrink[LayoutHorizontal]);
			ZeroGlue (p->stretch[LayoutVertical]);
			ZeroGlue (p->shrink[LayoutVertical]);
			LayYYval.pval = p;
		    ;
    break;}
case 11:
#line 142 "laygram.y"
{	
			BoxParamsPtr	p = New(BoxParamsRec);
			
			p->stretch[LayoutHorizontal] = LayYYvsp[-2].gval;
			p->shrink[LayoutHorizontal] = LayYYvsp[-1].gval;
			p->stretch[LayoutVertical] = LayYYvsp[-2].gval;
			p->shrink[LayoutVertical] = LayYYvsp[-1].gval;
			LayYYval.pval = p;
		    ;
    break;}
case 12:
#line 152 "laygram.y"
{	
			BoxParamsPtr	p = New(BoxParamsRec);
			
			ZeroGlue (p->stretch[LayoutHorizontal]);
			ZeroGlue (p->shrink[LayoutHorizontal]);
			ZeroGlue (p->stretch[LayoutVertical]);
			ZeroGlue (p->shrink[LayoutVertical]);
			LayYYval.pval = p;
		    ;
    break;}
case 13:
#line 163 "laygram.y"
{ LayYYval.gval = LayYYvsp[0].gval; ;
    break;}
case 14:
#line 165 "laygram.y"
{ ZeroGlue (LayYYval.gval); ;
    break;}
case 15:
#line 168 "laygram.y"
{ LayYYval.gval = LayYYvsp[0].gval; ;
    break;}
case 16:
#line 170 "laygram.y"
{ ZeroGlue (LayYYval.gval); ;
    break;}
case 17:
#line 173 "laygram.y"
{ LayYYval.gval.order = LayYYvsp[0].ival; LayYYval.gval.expr = LayYYvsp[-1].eval; ;
    break;}
case 18:
#line 175 "laygram.y"
{ LayYYval.gval.order = 0; LayYYval.gval.expr = LayYYvsp[0].eval; ;
    break;}
case 19:
#line 177 "laygram.y"
{ LayYYval.gval.order = LayYYvsp[0].ival; LayYYval.gval.expr = 0; LayYYval.gval.value = 1; ;
    break;}
case 20:
#line 180 "laygram.y"
{
			LayYYval.eval = New(ExprRec);
			LayYYval.eval->type = Unary;
			LayYYval.eval->u.unary.op = LayYYvsp[-1].oval;
			LayYYval.eval->u.unary.down = LayYYvsp[0].eval;
		    ;
    break;}
case 21:
#line 187 "laygram.y"
{ LayYYval.eval = LayYYvsp[0].eval; ;
    break;}
case 23:
#line 191 "laygram.y"
{	LayYYval.eval = New(ExprRec);
			LayYYval.eval->type = Width;
			LayYYval.eval->u.width = LayYYvsp[0].qval;
		    ;
    break;}
case 24:
#line 196 "laygram.y"
{	LayYYval.eval = New(ExprRec);
			LayYYval.eval->type = Height;
			LayYYval.eval->u.height = LayYYvsp[0].qval;
		    ;
    break;}
case 25:
#line 201 "laygram.y"
{ LayYYval.eval = LayYYvsp[-1].eval; ;
    break;}
case 26:
#line 203 "laygram.y"
{
			LayYYval.eval = New(ExprRec);
			LayYYval.eval->type = Unary;
			LayYYval.eval->u.unary.op = LayYYvsp[0].oval;
			LayYYval.eval->u.unary.down = LayYYvsp[-1].eval;
		    ;
    break;}
case 27:
#line 210 "laygram.y"
{	LayYYval.eval = New(ExprRec);
			LayYYval.eval->type = Constant;
			LayYYval.eval->u.constant = LayYYvsp[0].ival;
		    ;
    break;}
case 28:
#line 215 "laygram.y"
{	LayYYval.eval = New(ExprRec);
			LayYYval.eval->type = Variable;
			LayYYval.eval->u.variable = LayYYvsp[0].qval;
		    ;
    break;}
case 29:
#line 221 "laygram.y"
{ binary: ;
			LayYYval.eval = New(ExprRec);
			LayYYval.eval->type = Binary;
			LayYYval.eval->u.binary.op = LayYYvsp[-1].oval;
			LayYYval.eval->u.binary.left = LayYYvsp[-2].eval;
			LayYYval.eval->u.binary.right = LayYYvsp[0].eval;
		    ;
    break;}
case 30:
#line 229 "laygram.y"
{ goto binary; ;
    break;}
case 31:
#line 231 "laygram.y"
{ goto binary; ;
    break;}
case 32:
#line 233 "laygram.y"
{ goto binary; ;
    break;}
case 33:
#line 235 "laygram.y"
{ goto binary; ;
    break;}
case 34:
#line 237 "laygram.y"
{ unary: ;
			LayYYval.eval = New(ExprRec);
			LayYYval.eval->type = Unary;
			LayYYval.eval->u.unary.op = LayYYvsp[-1].oval;
			LayYYval.eval->u.unary.down = LayYYvsp[0].eval;
		    ;
    break;}
case 35:
#line 244 "laygram.y"
{ LayYYval.eval = LayYYvsp[0].eval; ;
    break;}
case 37:
#line 248 "laygram.y"
{   LayYYval.lval = LayoutVertical; ;
    break;}
case 38:
#line 250 "laygram.y"
{   LayYYval.lval = LayoutHorizontal; ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 542 "/usr/share/bison.simple"

  LayYYvsp -= LayYYlen;
  LayYYssp -= LayYYlen;
#ifdef YYLSP_NEEDED
  LayYYlsp -= LayYYlen;
#endif

#if YYDEBUG != 0
  if (LayYYdebug)
    {
      short *ssp1 = LayYYss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != LayYYssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++LayYYvsp = LayYYval;

#ifdef YYLSP_NEEDED
  LayYYlsp++;
  if (LayYYlen == 0)
    {
      LayYYlsp->first_line = LayYYlloc.first_line;
      LayYYlsp->first_column = LayYYlloc.first_column;
      LayYYlsp->last_line = (LayYYlsp-1)->last_line;
      LayYYlsp->last_column = (LayYYlsp-1)->last_column;
      LayYYlsp->text = 0;
    }
  else
    {
      LayYYlsp->last_line = (LayYYlsp+LayYYlen-1)->last_line;
      LayYYlsp->last_column = (LayYYlsp+LayYYlen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  LayYYn = LayYYr1[LayYYn];

  LayYYstate = LayYYpgoto[LayYYn - YYNTBASE] + *LayYYssp;
  if (LayYYstate >= 0 && LayYYstate <= YYLAST && LayYYcheck[LayYYstate] == *LayYYssp)
    LayYYstate = LayYYtable[LayYYstate];
  else
    LayYYstate = LayYYdefgoto[LayYYn - YYNTBASE];

  goto LayYYnewstate;

LayYYerrlab:   /* here on detecting error */

  if (! LayYYerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++LayYYnerrs;

#ifdef YYERROR_VERBOSE
      LayYYn = LayYYpact[LayYYstate];

      if (LayYYn > YYFLAG && LayYYn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -LayYYn if nec to avoid negative indexes in LayYYcheck.  */
	  for (x = (LayYYn < 0 ? -LayYYn : 0);
	       x < (sizeof(LayYYtname) / sizeof(char *)); x++)
	    if (LayYYcheck[x + LayYYn] == x)
	      size += strlen(LayYYtname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (LayYYn < 0 ? -LayYYn : 0);
		       x < (sizeof(LayYYtname) / sizeof(char *)); x++)
		    if (LayYYcheck[x + LayYYn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, LayYYtname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      LayYYerror(msg);
	      free(msg);
	    }
	  else
	    LayYYerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	LayYYerror("parse error");
    }

  goto LayYYerrlab1;
LayYYerrlab1:   /* here on error raised explicitly by an action */

  if (LayYYerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (LayYYchar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (LayYYdebug)
	fprintf(stderr, "Discarding token %d (%s).\n", LayYYchar, LayYYtname[LayYYchar1]);
#endif

      LayYYchar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  LayYYerrstatus = 3;		/* Each real token shifted decrements this */

  goto LayYYerrhandle;

LayYYerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  LayYYn = LayYYdefact[LayYYstate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (LayYYn) goto LayYYdefault;
#endif

LayYYerrpop:   /* pop the current state because it cannot handle the error token */

  if (LayYYssp == LayYYss) YYABORT;
  LayYYvsp--;
  LayYYstate = *--LayYYssp;
#ifdef YYLSP_NEEDED
  LayYYlsp--;
#endif

#if YYDEBUG != 0
  if (LayYYdebug)
    {
      short *ssp1 = LayYYss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != LayYYssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

LayYYerrhandle:

  LayYYn = LayYYpact[LayYYstate];
  if (LayYYn == YYFLAG)
    goto LayYYerrdefault;

  LayYYn += YYTERROR;
  if (LayYYn < 0 || LayYYn > YYLAST || LayYYcheck[LayYYn] != YYTERROR)
    goto LayYYerrdefault;

  LayYYn = LayYYtable[LayYYn];
  if (LayYYn < 0)
    {
      if (LayYYn == YYFLAG)
	goto LayYYerrpop;
      LayYYn = -LayYYn;
      goto LayYYreduce;
    }
  else if (LayYYn == 0)
    goto LayYYerrpop;

  if (LayYYn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (LayYYdebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++LayYYvsp = LayYYlval;
#ifdef YYLSP_NEEDED
  *++LayYYlsp = LayYYlloc;
#endif

  LayYYstate = LayYYn;
  goto LayYYnewstate;

 LayYYacceptlab:
  /* YYACCEPT comes here.  */
  if (LayYYfree_stacks)
    {
      free (LayYYss);
      free (LayYYvs);
#ifdef YYLSP_NEEDED
      free (LayYYls);
#endif
    }
  return 0;

 LayYYabortlab:
  /* YYABORT comes here.  */
  if (LayYYfree_stacks)
    {
      free (LayYYss);
      free (LayYYvs);
#ifdef YYLSP_NEEDED
      free (LayYYls);
#endif
    }
  return 1;
}
#line 252 "laygram.y"


int LayYYwrap ()
{
    return 1;
}

void LayYYsetdest (c)
    LayoutPtr	*c;
{
    dest = c;
}
