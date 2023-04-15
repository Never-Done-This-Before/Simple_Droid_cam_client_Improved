#include <gio/gio.h>

#if defined (__ELF__) && ( __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 6))
# define SECTION __attribute__ ((section (".gresource.simple_droidcam_client_db"), aligned (8)))
#else
# define SECTION
#endif

static const SECTION union { const guint8 data[501]; const double alignment; void * const ptr;}  simple_droidcam_client_db_resource_data = {
  "\107\126\141\162\151\141\156\164\000\000\000\000\000\000\000\000"
  "\030\000\000\000\344\000\000\000\000\000\000\050\007\000\000\000"
  "\000\000\000\000\003\000\000\000\003\000\000\000\006\000\000\000"
  "\006\000\000\000\006\000\000\000\007\000\000\000\234\123\131\337"
  "\002\000\000\000\344\000\000\000\063\000\166\000\030\001\000\000"
  "\237\001\000\000\063\232\107\316\005\000\000\000\237\001\000\000"
  "\022\000\114\000\264\001\000\000\270\001\000\000\101\154\126\361"
  "\004\000\000\000\270\001\000\000\003\000\114\000\274\001\000\000"
  "\300\001\000\000\324\265\002\000\377\377\377\377\300\001\000\000"
  "\001\000\114\000\304\001\000\000\310\001\000\000\214\221\245\207"
  "\001\000\000\000\310\001\000\000\027\000\114\000\340\001\000\000"
  "\344\001\000\000\304\053\021\024\006\000\000\000\344\001\000\000"
  "\004\000\114\000\350\001\000\000\354\001\000\000\326\200\170\174"
  "\003\000\000\000\354\001\000\000\003\000\114\000\360\001\000\000"
  "\364\001\000\000\163\151\155\160\154\145\137\144\162\157\151\144"
  "\143\141\155\137\143\154\151\145\156\164\137\142\141\163\145\137"
  "\144\145\137\144\141\164\157\163\137\144\145\146\151\156\151\143"
  "\151\157\156\056\163\161\154\000\206\000\000\000\001\000\000\000"
  "\170\332\155\315\101\012\302\100\014\000\300\263\171\105\216\372"
  "\206\305\103\132\322\045\270\233\135\142\074\364\044\210\253\024"
  "\241\205\026\004\177\257\017\360\001\303\124\243\230\011\037\313"
  "\332\246\347\174\175\265\317\166\054\303\020\240\343\050\212\156"
  "\244\147\352\135\212\006\350\215\311\031\235\272\304\170\277\341"
  "\036\166\357\266\156\323\062\243\250\163\144\103\055\216\172\111"
  "\011\253\111\046\033\361\304\043\034\176\264\344\054\036\240\376"
  "\353\064\174\001\127\241\047\055\000\050\165\165\141\171\051\163"
  "\157\146\164\167\141\162\145\160\145\162\157\156\151\163\164\141"
  "\057\000\000\000\004\000\000\000\144\142\057\000\000\000\000\000"
  "\057\000\000\000\006\000\000\000\163\151\155\160\154\145\137\144"
  "\162\157\151\144\143\141\155\137\143\154\151\145\156\164\057\000"
  "\002\000\000\000\143\157\155\057\001\000\000\000\141\162\057\000"
  "\005\000\000\000" };

static GStaticResource static_resource = { simple_droidcam_client_db_resource_data.data, sizeof (simple_droidcam_client_db_resource_data.data) - 1 /* nul terminator */, NULL, NULL, NULL };

G_GNUC_INTERNAL
GResource *simple_droidcam_client_db_get_resource (void);
GResource *simple_droidcam_client_db_get_resource (void)
{
  return g_static_resource_get_resource (&static_resource);
}
/* GLIB - Library of useful routines for C programming
 * Copyright (C) 1995-1997  Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Modified by the GLib Team and others 1997-2000.  See the AUTHORS
 * file for a list of people on the GLib Team.  See the ChangeLog
 * files for a list of changes.  These files are distributed with
 * GLib at ftp://ftp.gtk.org/pub/gtk/.
 */

#ifndef __G_CONSTRUCTOR_H__
#define __G_CONSTRUCTOR_H__

/*
  If G_HAS_CONSTRUCTORS is true then the compiler support *both* constructors and
  destructors, in a usable way, including e.g. on library unload. If not you're on
  your own.

  Some compilers need #pragma to handle this, which does not work with macros,
  so the way you need to use this is (for constructors):

  #ifdef G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA
  #pragma G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(my_constructor)
  #endif
  G_DEFINE_CONSTRUCTOR(my_constructor)
  static void my_constructor(void) {
   ...
  }

*/

#ifndef __GTK_DOC_IGNORE__

#if  __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 7)

#define G_HAS_CONSTRUCTORS 1

#define G_DEFINE_CONSTRUCTOR(_func) static void __attribute__((constructor)) _func (void);
#define G_DEFINE_DESTRUCTOR(_func) static void __attribute__((destructor)) _func (void);

#elif defined (_MSC_VER) && (_MSC_VER >= 1500)
/* Visual studio 2008 and later has _Pragma */

/*
 * Only try to include gslist.h if not already included via glib.h,
 * so that items using gconstructor.h outside of GLib (such as
 * GResources) continue to build properly.
 */
#ifndef __G_LIB_H__
#include "gslist.h"
#endif

#include <stdlib.h>

#define G_HAS_CONSTRUCTORS 1

/* We do some weird things to avoid the constructors being optimized
 * away on VS2015 if WholeProgramOptimization is enabled. First we
 * make a reference to the array from the wrapper to make sure its
 * references. Then we use a pragma to make sure the wrapper function
 * symbol is always included at the link stage. Also, the symbols
 * need to be extern (but not dllexport), even though they are not
 * really used from another object file.
 */

/* We need to account for differences between the mangling of symbols
 * for x86 and x64/ARM/ARM64 programs, as symbols on x86 are prefixed
 * with an underscore but symbols on x64/ARM/ARM64 are not.
 */
#ifdef _M_IX86
#define G_MSVC_SYMBOL_PREFIX "_"
#else
#define G_MSVC_SYMBOL_PREFIX ""
#endif

#define G_DEFINE_CONSTRUCTOR(_func) G_MSVC_CTOR (_func, G_MSVC_SYMBOL_PREFIX)
#define G_DEFINE_DESTRUCTOR(_func) G_MSVC_DTOR (_func, G_MSVC_SYMBOL_PREFIX)

#define G_MSVC_CTOR(_func,_sym_prefix) \
  static void _func(void); \
  extern int (* _array ## _func)(void);              \
  int _func ## _wrapper(void) { _func(); g_slist_find (NULL,  _array ## _func); return 0; } \
  __pragma(comment(linker,"/include:" _sym_prefix # _func "_wrapper")) \
  __pragma(section(".CRT$XCU",read)) \
  __declspec(allocate(".CRT$XCU")) int (* _array ## _func)(void) = _func ## _wrapper;

#define G_MSVC_DTOR(_func,_sym_prefix) \
  static void _func(void); \
  extern int (* _array ## _func)(void);              \
  int _func ## _constructor(void) { atexit (_func); g_slist_find (NULL,  _array ## _func); return 0; } \
   __pragma(comment(linker,"/include:" _sym_prefix # _func "_constructor")) \
  __pragma(section(".CRT$XCU",read)) \
  __declspec(allocate(".CRT$XCU")) int (* _array ## _func)(void) = _func ## _constructor;

#elif defined (_MSC_VER)

#define G_HAS_CONSTRUCTORS 1

/* Pre Visual studio 2008 must use #pragma section */
#define G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA 1
#define G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA 1

#define G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(_func) \
  section(".CRT$XCU",read)
#define G_DEFINE_CONSTRUCTOR(_func) \
  static void _func(void); \
  static int _func ## _wrapper(void) { _func(); return 0; } \
  __declspec(allocate(".CRT$XCU")) static int (*p)(void) = _func ## _wrapper;

#define G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(_func) \
  section(".CRT$XCU",read)
#define G_DEFINE_DESTRUCTOR(_func) \
  static void _func(void); \
  static int _func ## _constructor(void) { atexit (_func); return 0; } \
  __declspec(allocate(".CRT$XCU")) static int (* _array ## _func)(void) = _func ## _constructor;

#elif defined(__SUNPRO_C)

/* This is not tested, but i believe it should work, based on:
 * http://opensource.apple.com/source/OpenSSL098/OpenSSL098-35/src/fips/fips_premain.c
 */

#define G_HAS_CONSTRUCTORS 1

#define G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA 1
#define G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA 1

#define G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(_func) \
  init(_func)
#define G_DEFINE_CONSTRUCTOR(_func) \
  static void _func(void);

#define G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(_func) \
  fini(_func)
#define G_DEFINE_DESTRUCTOR(_func) \
  static void _func(void);

#else

/* constructors not supported for this compiler */

#endif

#endif /* __GTK_DOC_IGNORE__ */
#endif /* __G_CONSTRUCTOR_H__ */

#ifdef G_HAS_CONSTRUCTORS

#ifdef G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA
#pragma G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(simple_droidcam_client_dbresource_constructor)
#endif
G_DEFINE_CONSTRUCTOR(simple_droidcam_client_dbresource_constructor)
#ifdef G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA
#pragma G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(simple_droidcam_client_dbresource_destructor)
#endif
G_DEFINE_DESTRUCTOR(simple_droidcam_client_dbresource_destructor)

#else
#warning "Constructor not supported on this compiler, linking in resources will not work"
#endif

static void simple_droidcam_client_dbresource_constructor (void)
{
  g_static_resource_init (&static_resource);
}

static void simple_droidcam_client_dbresource_destructor (void)
{
  g_static_resource_fini (&static_resource);
}
