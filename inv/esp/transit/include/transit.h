/*
 * transit.h - Common headers for the Transit program.
 *
 * Copyright (C) 2003 Patricio Rojo (pato@astro.cornell.edu)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */

#ifndef _TRANSIT_H
#define _TRANSIT_H

#define TRANSIT

#include <stdarg.h>
#include <math.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <util/sampling.h>
#include <util/profile.h>
#include <util/iomisc.h>
#include <util/numerical.h>
#include <util/xmalloc.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#ifdef _USE_GSL
#include <gsl/gsl_spline.h>
#endif

#define compattwiiversion 2

#include <transit_flags.h>

/*****   Types     *****/
#define PREC_NSAMP int		/* Type for radius and wavelength
				   indices */
#define PREC_NREC long		/* Type for record indices */
#define PREC_ZREC double	/* Type for the partition info  */
#define PREC_LNDATA double	/* Type for the line data output */
#define PREC_RES double     	/* Type for every partial result */
#define PREC_ATM double		/* Type for atmospheric data */
#define PREC_CS  double		/* Type for cross-section */

/*****   Macros   *****/
#define stateeqnford(q,m,p,t) (AMU*(q)*(m)*(p)/(KB*(t)))

#define transitassert(a,...) if(a) transiterror(TERR_CRITICAL,__VA_ARGS__)
#define transitprint(thislevel, verblevel, ...) if(thislevel <= verblevel)  \
        fprintf(stderr,__VA_ARGS__)
#define transitacceptflag(transit,hint,flag) do{                            \
        transit|=hint&flag;hint&=~(flag);}while(0)
#define transitaccepthint(transit,hint,flags,flagvalue) do{                 \
        transit=hint;                    }while(0)
#define transitallocerror(nmb)                                              \
        transiterror(TERR_CRITICAL,                                         \
	             "transit:: %s: Allocation failed for %i allocation\n"  \
	             "units in line %i. Impossible to continue.\n"          \
	             ,__FILE__,nmb,__LINE__)


#ifdef NODEBUG_TRANSIT
#define transitDEBUG(...) ((void)0)
#define transitASSERT(...) ((void)0)
#else
#define free(x) do{free(x);x=NULL;}while(0)
#define transitASSERT(a,...) if(a) transiterror(TERR_CRITICAL,__VA_ARGS__)
#define transitDEBUG(...) transitprint(__VA_ARGS__)
#endif

#include <transit_constants.h>

extern const int maxeisoname;
extern int transit_nowarn;
extern int verblevel;
extern int maxline;

enum isodo {unclear=0,atmfile,ignore,fixed};

#include <transit_structures.h>

/***** Prototypes *****/
#include <transit_proto.h>
#include <readlineinfo_proto.h>
#include <transitstd_proto.h>
#include <readatminfo_proto.h>
#include <makesample_proto.h>
#include <extinction_proto.h>
#include <idxrefraction_proto.h>
#include <tau_proto.h>


#endif /* _TRANSIT_H */
