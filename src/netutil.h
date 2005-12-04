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

#ifndef __NETUTIL_H
#define __NETUTIL_H

struct addrinfo;

int getaddrinfo_helper(const char *host_and_port, int default_port,
                       const struct addrinfo *hints,
                       struct addrinfo **aip);

int setup_server_socket(uint32_t ip, uint16_t port);

int setup_client_socket(uint32_t ip, uint16_t port);

int socket_connect(uint32_t ip, uint16_t port);

#endif
