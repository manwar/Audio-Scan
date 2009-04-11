/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
 
// Enable for debug output
//#define DEBUG

#ifdef DEBUG
# define DEBUG_TRACE(...) PerlIO_printf(PerlIO_stderr(), __VA_ARGS__)
#else
# define DEBUG_TRACE(...)
#endif

#ifndef __APPLE__
#  include <endian.h>
#else
#  include <machine/endian.h>
#  define __LITTLE_ENDIAN  LITTLE_ENDIAN
#  define __BIG_ENDIAN     BIG_ENDIAN
#  define __BYTE_ORDER     BYTE_ORDER
#endif

#if __BYTE_ORDER == __LITTLE_ENDIAN
#define SWAP32(l) (l)
#define SWAP16(w) (w)
#else
#define SWAP32(l) ( (((l)>>24)&0x000000ff) | (((l)>>8)&0x0000ff00) | (((l)<<8)&0x00ff0000) | (((l)<<24)&0xff000000) )
#define SWAP16(w) ( (((w)>>8)&0x00ff) | (((w)<<8)&0xff00) )
#endif

#if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ > 4)
# define _PACKED __attribute((packed))
#else
# define _PACKED
#endif

 typedef struct _GUID {
   uint32_t l;
   uint16_t w[2];
   uint8_t  b[8];
 } _PACKED GUID;

/* for PRIu64 */
#ifdef _MSC_VER
#include "pinttypes.h"
#else
#include <inttypes.h>
#endif

#include "buffer.h"

#ifdef _MSC_VER
# define stat _stat
#endif

/* strlen the length automatically */
#define my_hv_store(a,b,c)     hv_store(a,b,strlen(b),c,0)
#define my_hv_store_ent(a,b,c) hv_store_ent(a,b,c,0)
#define my_hv_fetch(a,b)       hv_fetch(a,b,strlen(b),0)
#define my_hv_exists(a,b)      hv_exists(a,b,strlen(b))
#define my_hv_exists_ent(a,b)  hv_exists_ent(a,b,0)

#define GET_INT32BE(b) \
(i = (b[0] << 24) | (b[1] << 16) | b[2] << 8 | b[3], b += 4, i)

#define GET_INT16BE(b) \
(i = (b[0] << 8) | b[1], b += 2, i)

#define CONVERT_INT32LE(b) \
(i = (b[3] << 24) | (b[2] << 16) | b[1] << 8 | b[0], i)

extern int _check_buf(PerlIO *infile, Buffer *buf, int size, int min_size);
extern void _split_vorbis_comment(char* comment, HV* tags);
