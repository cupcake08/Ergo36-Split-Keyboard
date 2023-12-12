// Copyright 2023 Ankit Bhankharia (@cupcake08)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
#define PERMISSIVE_HOLD
#define TAPPING_TERM_PER_KEY

#define SPLIT_USB_DETECT

#define EE_HANDS