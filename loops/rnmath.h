// R source code.
// 04/05/2023.
// Email: arifle@163.com

#ifndef RNMATH_H
#define RNMATH_H

#include <iostream>
#include <vector>
#include <cmath>

double unif_rand(void);

#define ISNAN(x) (isnan(x)!=0)


int R_finite(double);

#ifndef R_FINITE
#ifdef HAVE_WORKING_ISFINITE
/* isfinite is defined in <math.h> according to C99 */
# define R_FINITE(x)    isfinite(x)
#else
# define R_FINITE(x)    R_finite(x)
#endif
#endif


#define MATHLIB_WARNING(fmt,x)		printf(fmt,x)
#define MATHLIB_ERROR(fmt,x)	{ printf(fmt,x); exit(1); }

#ifdef HAVE_VISIBILITY_ATTRIBUTE
# define attribute_hidden __attribute__ ((visibility ("hidden")))
#else
# define attribute_hidden
#endif

// Random.h
typedef enum {
	WICHMANN_HILL,
	MARSAGLIA_MULTICARRY,
	SUPER_DUPER,
	MERSENNE_TWISTER,
	KNUTH_TAOCP,
	USER_UNIF,
	KNUTH_TAOCP2,
	LECUYER_CMRG
} RNGtype;

/* Different kinds of "N(0,1)" generators :*/
typedef enum {
	BUGGY_KINDERMAN_RAMAGE,
	AHRENS_DIETER,
	BOX_MULLER,
	USER_NORM,
	INVERSION,
	KINDERMAN_RAMAGE
} N01type;

// nmath.h
#define ML_POSINF	INFINITY
#define ML_NEGINF	-INFINITY
#define ML_NAN		NAN

#define ME_NONE		0
/*	no error */
#define ME_DOMAIN	1
/*	argument out of domain */
#define ME_RANGE	2
/*	value out of range */
#define ME_NOCONV	4
/*	process did not converge */
#define ME_PRECISION	8
/*	does not have "full" precision */
#define ME_UNDERFLOW	16
/*	and underflow occured (important for IEEE)*/

/* For a long time prior to R 2.3.0 ML_WARNING did nothing.
We don't report ME_DOMAIN errors as the callers collect ML_NANs into
a single warning.
*/
#define ML_WARNING(x, s) { \
   if(x > ME_DOMAIN) { \
       char *msg = ""; \
       switch(x) { \
       case ME_DOMAIN: \
	   msg = ("argument out of domain in '%s'\n");	\
	   break; \
       case ME_RANGE: \
	   msg = ("value out of range in '%s'\n");	\
	   break; \
       case ME_NOCONV: \
	   msg = ("convergence failed in '%s'\n");	\
	   break; \
       case ME_PRECISION: \
	   msg = ("full precision may not have been achieved in '%s'\n"); \
	   break; \
       case ME_UNDERFLOW: \
	   msg = ("underflow occurred in '%s'\n");	\
	   break; \
	       } \
       MATHLIB_WARNING(msg, s); \
      } \
}

#define ML_WARN_return_NAN { ML_WARNING(ME_DOMAIN, ""); return ML_NAN; }

#endif