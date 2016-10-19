/* Copyright © 2016 Wiki Wang <wikiwang@live.com>
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * the COPYING file for more details. */

#pragma once

#include "BaseClasses/BaseFilter.h"
#include "BaseClasses/Thread.h"
#include "BaseClasses/BaseObject.h"
#include "BaseClasses/BaseBuffer.h"

namespace filters {

class PcapParser : public Filter, public Thread, public BaseObject {
public:
    PcapParser();
    long setSource(Filter *s, long port);

    long setSink(long io, Filter *f, long ii);
    long setListener(Notify *);

    long run();

    long onReceive(long id, Buffer *data);

protected:
    ~PcapParser();

    long proc();

private:
    Filter *src;
    long srcI;
    Filter *sink;
    long sinkI;
    SystemBuffer *b;
};

inline PcapParser::PcapParser() : b(new SystemBuffer) {}

inline long PcapParser::setSource(Filter *s, long port) {
    src = s;
    srcI = port;
    return 0;
}

}
