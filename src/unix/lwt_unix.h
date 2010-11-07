/* Lightweight thread library for Objective Caml
 * http://www.ocsigen.org/lwt
 * Header lwt_unix
 * Copyright (C) 2010 Jérémie Dimino
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, with linking exceptions;
 * either version 2.1 of the License, or (at your option) any later
 * version. See COPYING file for details.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */

#ifndef __LWT_UNIX_H
#define __LWT_UNIX_H

#include <caml/mlvalues.h>
#include <caml/unixsupport.h>
#include <ev.h>

/* Detect the target OS */
#if defined(_WIN32) || defined(_WIN64)
#  define LWT_ON_WINDOWS
#endif

/* The macro to get the file-descriptor from a value. */
#if defined(LWT_ON_WINDOWS)
#  define FD_val(value) win_CRT_fd_of_filedescr(value)
#else
#  define FD_val(value) Int_val(value)
#endif

/* Sends a notification for the given id. */
void lwt_unix_send_notification(int id);

/* Launch a thread in detached mode with the minimum amount of stack. */
void lwt_unix_launch_thread(void* (*start)(void*), void* data);

/* The libev main loop. */
extern struct ev_loop *lwt_unix_main_loop;

/* Flag which tells whether we are in a blocking section or not. */
extern int lwt_unix_in_blocking_section;

/* Macro to add in libev callbacks. See the manual for
   explanations. */
#define LWT_UNIX_CHECK                          \
  if (lwt_unix_in_blocking_section) {           \
    lwt_unix_in_blocking_section = 0;           \
    caml_leave_blocking_section();              \
  }

#endif /* __LWT_UNIX_H */
