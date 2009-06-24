#ifndef _LIBSLIRP_H
#define _LIBSLIRP_H

#include <qemu-common.h>

#ifdef CONFIG_SLIRP

struct Slirp;
typedef struct Slirp Slirp;

void slirp_init(int restricted, struct in_addr vnetwork,
                struct in_addr vnetmask, struct in_addr vhost,
                const char *vhostname, const char *tftp_path,
                const char *bootfile, struct in_addr vdhcp_start,
                struct in_addr vnameserver);

void slirp_select_fill(int *pnfds, fd_set *readfds, fd_set *writefds,
                       fd_set *xfds);

void slirp_select_poll(fd_set *readfds, fd_set *writefds, fd_set *xfds,
                       int select_error);

void slirp_input(const uint8_t *pkt, int pkt_len);

/* you must provide the following functions: */
int slirp_can_output(void);
void slirp_output(const uint8_t *pkt, int pkt_len);

int slirp_add_hostfwd(int is_udp, struct in_addr host_addr, int host_port,
                      struct in_addr guest_addr, int guest_port);
int slirp_remove_hostfwd(int is_udp, struct in_addr host_addr, int host_port);
int slirp_add_exec(int do_pty, const void *args, struct in_addr guest_addr,
                   int guest_port);

void slirp_connection_info(Monitor *mon);

void slirp_socket_recv(struct in_addr guest_addr, int guest_port,
                       const uint8_t *buf, int size);
size_t slirp_socket_can_recv(struct in_addr guest_addr, int guest_port);

#else /* !CONFIG_SLIRP */

static inline void slirp_select_fill(int *pnfds, fd_set *readfds,
                                     fd_set *writefds, fd_set *xfds)
{
}

static inline void slirp_select_poll(fd_set *readfds, fd_set *writefds,
                                     fd_set *xfds, int select_error)
{
}
#endif /* !CONFIG_SLIRP */

#endif
