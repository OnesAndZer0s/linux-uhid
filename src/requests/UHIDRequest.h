#pragma once

#include "napi.h"

#include <linux/uhid.h>

struct UHIDRequest {
    Napi::External< uhid_event > event;
    struct uhid_event ev;
};