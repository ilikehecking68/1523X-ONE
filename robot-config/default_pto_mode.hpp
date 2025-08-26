#pragma once

enum {
    pto_mode_intake,
    pto_mode_dt
};

using pto_mode = bool;

constexpr pto_mode pto_default_selected_mode = pto_mode_intake;