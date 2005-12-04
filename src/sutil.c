/*
 * uoproxy
 * $Id$
 *
 * (c) 2005 Max Kellermann <max@duempel.org>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; version 2 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>

#include "server.h"
#include "packets.h"

static void write_fixed_string(char *dest, size_t max_length,
                               const char *src) {
    size_t length = strlen(src);

    if (length >= max_length) {
        memcpy(dest, src, max_length);
    } else {
        memcpy(dest, src, length);
        memset(dest + length, 0, max_length - length);
    }
}

void uo_server_speak_ascii(struct uo_server *server,
                           u_int32_t serial,
                           int16_t graphic,
                           u_int8_t type,
                           u_int16_t hue, u_int16_t font,
                           const char *name,
                           const char *text) {
    struct uo_packet_speak_ascii *p;
    size_t length;

    length = sizeof(*p) + strlen(text);

    p = malloc(length);
    if (p == NULL)
        return;

    p->cmd = PCK_SpeakAscii;
    p->length = htons(length);
    p->serial = serial;
    p->graphic = graphic;
    p->type = type;
    p->hue = hue;
    p->font = font;
    write_fixed_string(p->name, sizeof(p->name), name);
    strcpy(p->text, text);

    uo_server_send(server, p, length);

    free(p);
}

void uo_server_speak_console(struct uo_server *server,
                             const char *text) {
    uo_server_speak_ascii(server,
                          htonl(0xffffffff),
                          htons(-1),
                          0x01,
                          htons(0x35),
                          htons(3),
                          "uoproxy", text);
}
