/* doc.h -- Structures associating function pointers with documentation.
   $Id: doc.h,v 1.1 2002/12/05 21:07:15 earnie Exp $

   Copyright (C) 1993, 2001 Free Software Foundation, Inc.

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
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

   Written by Brian Fox (bfox@ai.mit.edu). */

#if !defined (DOC_H)
#define DOC_H

#include "info.h" /* for NAMED_FUNCTIONS, VFunction, etc.  */

#if defined (INFOKEY)
/* For each function, we keep track of the first defined key sequence
   which invokes that function, for each different map.  This is so that
   the dynamic documentation generation in infodoc.c (a) doesn't have to
   search through copious KEYMAP_ENTRYs, and, more importantly, (b) the
   user and programmer can choose the preferred key sequence that is
   printed for any given function -- it's just the first one that
   appears in the user's infokey file or the default keymaps in
   infomap.c.

   Each FUNCTION_DOC has a linked list of FUNCTION_KEYSEQ structs
   hanging off it, which are created on startup when the user and/or
   default keymaps are being parsed.  */
typedef struct function_keyseq
{
  struct function_keyseq *next;
  struct keymap_entry *map;
  char *keyseq;
} FUNCTION_KEYSEQ;

#endif /* INFOKEY */


/* An array of FUNCTION_DOC structures is defined in doc.c, which is
   automagically generated by the makedoc utility, whose job is to scan
   through the source files for command function declarations and
   compile a list of all the ones it finds.  This saves tedious
   housekeeping and avoids errors of omission.  */
typedef struct
{
  VFunction *func;
#if defined (NAMED_FUNCTIONS)
  char *func_name;
#endif /* NAMED_FUNCTIONS */
#if defined (INFOKEY)
  FUNCTION_KEYSEQ *keys;
#endif /* INFOKEY */
   char *doc;
} FUNCTION_DOC;

extern FUNCTION_DOC function_doc_array[];

extern char *function_documentation ();
extern char *key_documentation ();
extern char *pretty_keyname ();
extern char *pretty_keyseq ();
extern char *where_is ();
extern char *replace_in_documentation ();
extern void info_document_key ();
extern void dump_map_to_message_buffer ();

/* Under the old key-binding system, an info command is specified by
   the pointer to its function.  Under the new INFOKEY binding system, 
   it is specified by a pointer to the command's FUNCTION_DOC structure,
   defined in doc.c, from which the pointer to the function can be
   easily divined using the InfoFunction() extractor.  */
#if defined(INFOKEY)
typedef FUNCTION_DOC InfoCommand;
#define InfoFunction(ic) ((ic) ? (ic)->func : NULL)
#define InfoCmd(fn) (&function_doc_array[A_##fn])
#define DocInfoCmd(fd) ((fd) && (fd)->func ? (fd) : NULL)
#else /* !INFOKEY */
typedef VFunction InfoCommand;
#define InfoFunction(vf) ((vf))
#define InfoCmd(fn) fn
#define DocInfoCmd(fd) ((fd)->func)
#endif /* !INFOKEY */

#if defined (NAMED_FUNCTIONS)
extern char *function_name ();
extern InfoCommand *named_function ();
#endif /* NAMED_FUNCTIONS */
#endif /* !DOC_H */
