/*
 *	BIRD Internet Routing Daemon -- BIRD Unit Testing Framework
 *
 *	(c) 2015 Ondrej Zajicek <santiago@crfreenet.org>
 *	(c) 2015 CZ.NIC z.s.p.o.
 *
 *	Can be freely distributed and used under the terms of the GNU GPL.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>


extern int bt_verbose;
extern const char *bt_filename;
extern const char *bt_test_id;

void bt_init(int argc, char **argv);
void bt_test_case2(int (*fn)(void), const char *id, const char *dsc, int forked, int timeout);

#define bt_test_case(fn,dsc,f,t) \
    bt_test_case2(fn, #fn, dsc, f, t)

#define bt_log(format, ...) \
    fprintf(stderr, "%s: " format "\n", bt_filename, ##__VA_ARGS__)

#define bt_note(format, ...) \
    do { if (bt_verbose) bt_log(format, ##__VA_ARGS__); } while (0)

#define bt_abort() \
    bt_abort_msg("Aborted at %s:%d", __FILE__, __LINE__)

#define bt_abort_msg(format, ...) \
    do { bt_log(format, ##__VA_ARGS__); abort(); } while (0)

#define bt_assert(test) \
    bt_assert_msg(test, "Assertion (%s) failed at %s:%d", #test, __FILE__, __LINE__)

#define bt_assert_msg(test,format, ...) \
    do { if (!(test)) bt_abort_msg(format, ##__VA_ARGS__); } while (0)

#define bt_syscall(test,format, ...)			\
    do { if (test) { bt_log(format ": %s", ##__VA_ARGS__, strerror(errno)); exit(3); } } while (0)