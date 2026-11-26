// SPDX-License-Identifier: BSD-2-Clause
/* Copyright (c) 2026 Authors of shirudo */

#include <stdbool.h>

#include "unit.h"
#include <shirudo/pin_grant.h>

static void unlink_grant_only_covers_one_directory(void)
{
	enum { root = 1, upatches, selected, sibling, maps, pin };

	EXPECT_EQ(pin_grant_delete(0, pin, selected, upatches, false), PIN_GRANT_DENY);
	EXPECT_EQ(pin_grant_delete(selected, pin, sibling, upatches, false), PIN_GRANT_DENY);
	EXPECT_EQ(pin_grant_delete(selected, pin, root, root, false), PIN_GRANT_DENY);
	EXPECT_EQ(pin_grant_delete(selected, upatches, root, root, true), PIN_GRANT_DENY);
	EXPECT_EQ(pin_grant_delete(selected, pin, selected, upatches, false), PIN_GRANT_ALLOW);
	EXPECT_EQ(pin_grant_delete(selected, pin, maps, selected, false), PIN_GRANT_ALLOW);
	EXPECT_EQ(pin_grant_delete(selected, maps, selected, upatches, true), PIN_GRANT_ALLOW);
	EXPECT_EQ(pin_grant_delete(selected, selected, upatches, root, true), PIN_GRANT_CONSUME);
}

static const struct unit_case cases[] = {
	UNIT_CASE(unlink_grant_only_covers_one_directory),
	{}
};

UNIT_SUITE(pin_grant, cases);
