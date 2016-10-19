/* Copyright © 2016 Wiki Wang <wikiwang@live.com>
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * the COPYING file for more details. */

#pragma once

#include "BaseClasses/BaseFilter.h"
#include "BaseClasses/BaseObject.h"
#include <unordered_set>

namespace filters {

class IpParser : public BaseFilter, public BaseObject {
public:
    static constexpr long NOTIFY_ID = 0x919e4b62515a10b4;
    struct Notify {
        char version;
        union {
            struct {
                uint8_t protocol;
                uint32_t saddr;
                uint32_t daddr;
            };
        };
        long id;

        struct hash
        { size_t operator()(const Notify &n) const; };

        bool operator==(const Notify &n) const;
    };

    long onReceive(long id, Buffer *data);

private:
    long i;
    std::unordered_set<Notify, Notify::hash> set;
};

}
