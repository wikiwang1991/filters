/* Copyright © 2016 Wiki Wang <wikiwang@live.com>
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * the COPYING file for more details. */

#include "BaseFilter.h"

namespace filters {

long BaseFilter::setSink(long io, Filter *f, long ii) {
    const auto &it = sinks.find(io);
    if (it == sinks.end())
        sinks.emplace(io, Pin(f, ii));
    else {
        auto &p = it->second;
        p.f = f;
        p.i = ii;
    }
    return 0;
}

long BaseFilter::setListener(Notify *l)
{ listener = l; return 0; }

}
