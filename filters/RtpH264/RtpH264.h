/* Copyright © 2016 Wiki Wang <wikiwang@live.com>
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * the COPYING file for more details. */

#pragma once

#include "BaseClasses/BaseBuffer.h"

namespace filters {

class SystemBuffer;

class RtpH264 : public Filter, public BaseObject {
public:
    RtpH264();
    ~RtpH264();

    long setSink(long id, Filter *f, long ii);
    long setListener(Notify *);

    long onReceive(long id, Buffer *data);

private:
    Filter *s;
    long i;
    SystemBuffer *pkt;
};

inline RtpH264::RtpH264() : pkt(new SystemBuffer) { pkt->setSize(0x80000); }

}
