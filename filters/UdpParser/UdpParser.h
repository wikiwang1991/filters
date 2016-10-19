/* Copyright © 2016 Wiki Wang <wikiwang@live.com>
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * the COPYING file for more details. */

#pragma once

#include "BaseClasses/BaseFilter.h"
#include "BaseClasses/BaseObject.h"

namespace filters {

class UdpParser : public BaseFilter, public BaseObject {
public:
    static constexpr long NOTIFY_ID = 0x84cf10aff0a8a152;
    struct Notify {
        uint16_t source;
        uint16_t dest;
        long id;
    };

    long onReceive(long id, Buffer *data);
};

}
