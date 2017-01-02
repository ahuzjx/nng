//
// Copyright 2016 Garrett D'Amore <garrett@damore.org>
//
// This software is supplied under the terms of the MIT License, a
// copy of which should be located in the distribution where this
// file was obtained (LICENSE.txt).  A copy of the license may also be
// found online at https://opensource.org/licenses/MIT.
//

#include <string.h>

#include "core/nng_impl.h"

// Protocol related stuff - generically.

// The list of protocols is hardwired.  This is reasonably unlikely to
// change, as adding new protocols is not something intended to be done
// outside of the core.
extern nni_proto nni_pair_proto;

static nni_proto *protocols[] = {
	&nni_pair_proto,
	NULL
};

nni_proto *
nni_proto_find(uint16_t num)
{
	int i;
	nni_proto *p;

	for (i = 0; (p = protocols[i]) != NULL; i++) {
		if (p->proto_self == num) {
			break;
		}
	}
	return (p);
}


const char *
nni_proto_name(uint16_t num)
{
	nni_proto *p;

	if ((p = nni_proto_find(num)) == NULL) {
		return (NULL);
	}
	return (p->proto_name);
}


uint16_t
nni_proto_number(const char *name)
{
	nni_proto *p;
	int i;

	for (i = 0; (p = protocols[i]) != NULL; i++) {
		if (strcmp(p->proto_name, name) == 0) {
			return (p->proto_self);
		}
	}
	return (NNG_PROTO_NONE);
}

uint16_t
nni_proto_peer(uint16_t num)
{
	nni_proto *p;

	if ((p = nni_proto_find(num)) == NULL) {
		return (NNG_PROTO_NONE);
	}
	return (p->proto_peer);
}

