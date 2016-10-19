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

class RtpParser : public BaseFilter, public BaseObject {
public:
    static constexpr long NOTIFY_ID = 0x68ec39f5cea759c1;
    struct Notify {
        uint32_t ssrc;
        uint8_t type;
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

inline size_t RtpParser::Notify::hash::operator()(const RtpParser::Notify &n) const {
    size_t res = 17;
    res = res * 31 + n.ssrc;
    res = res * 31 + n.type;
    return res;
}

inline bool RtpParser::Notify::operator==(const RtpParser::Notify &n) const
{ return n.type == type && n.ssrc == ssrc; }

}
