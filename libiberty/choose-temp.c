/* Utility to pick a temporary filename prefix.
   Copyright (C) 1996, 1997, 1998 Free Software Foundation, Inc.

This file is part of the libiberty library.
Libiberty is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

Libiberty is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with libiberty; see the file COPYING.LIB.  If not,
write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>	/* May get P_tmpdir.  */
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#ifdef HAVE_STRING_H
#include <string.h>
#endif

#include "libiberty.h"
extern char *choose_tmpdir PARAMS ((void));

/* Name of temporary file.
   mktemp requires 6 trailing X's.  */
#define TEMP_FILE "ccXXXXXX"
#define TEMP_FILE_LEN (sizeof(TEMP_FILE) - 1)

/* Return a prefix for temporary file names or NULL if unable to find one.
   The current directory is chosen if all else fails so the program is
   exited if a temporary directory can't be found (mktemp fails).
   The buffer for the result is obtained with xmalloc. 

   This function is provided for backwards compatability only.  It use
   is not recommended.  */

char *
choose_temp_base ()
{
  const char *base = choose_tmpdir ();
  char *temp_filename;
  int len;

  len = strlen (base);
  temp_filename = xmalloc (len + TEMP_FILE_LEN + 1);
  strcpy (temp_filename, base);
  strcpy (temp_filename + len, TEMP_FILE);

  mktemp (temp_filename);
  if (strlen (temp_filename) == 0)
    abort ();
  return temp_filename;
}