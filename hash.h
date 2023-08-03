/*
 * Copyright (C) 2023. Roger Doss. All Rights Reserved.
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
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * References: Jave string hash.
 *
 */
#ifndef _HASH_H
#define _HASH_H

#include <string.h>
#include <stdlib.h>

// 32 seconds for 10million inserts
// -O3 build required
unsigned hash3(const char *str)
{
    unsigned val_tab[] = {0x6938d27,
                          0x929dd4cb,
                          0xd05819e3,
                          0xb2a035fb,
                          0xa3988717};

    unsigned val  = val_tab[*str % 5];

    for(; *str; str++) {
        val += *str;
        if(val % 2) {
            val <<= 1;
        } else {
            val >>= 1;
        }
        val ^= val_tab[*str % 5];
    }

    return val;
}

unsigned inthash(unsigned val)
{
    static char str[1024]={0};
    unsigned bytes = sprintf(str,"%d",val);
    str[bytes] = '\0';
    return hash3(str);
}

#endif

