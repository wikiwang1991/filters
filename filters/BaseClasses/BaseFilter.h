/* Copyright © 2016 Wiki Wang <wikiwang@live.com>
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * the COPYING file for more details. */

#pragma once

#include "Filter.h"
#include <unordered_map>

namespace filters {

class BaseFilter : public Filter {
public:
    BaseFilter();

    long setSink(long io, Filter *f, long ii);
    long setListener(Notify *l);

protected:
    struct Pin {
        Filter *f;
        long i;

        inline Pin(Filter *f, long i) : f(f), i(i) {}
    };

    std::unordered_map<long, Pin> sinks;
    Notify *listener;
};

inline BaseFilter::BaseFilter() : listener(0) {}

}
