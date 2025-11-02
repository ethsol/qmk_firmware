#pragma once

// Configure the global tapping term (default: 200ms, reduced for faster typing)
#define TAPPING_TERM 200  // Increased to allow tap&hold detection

// Make layer tap more reliable
#define PERMISSIVE_HOLD  // If another key is pressed before timeout, first key will tap

// Enable per-key configuration for tapping and quick tap
#define TAPPING_TERM_PER_KEY
#define QUICK_TAP_TERM_PER_KEY  // Per-key quick tap term (200ms for numbers in get_quick_tap_term)
