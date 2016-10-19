/* Copyright © 2016 Wiki Wang <wikiwang@live.com>
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * the COPYING file for more details. */

#include "LinuxSllParser.h"

namespace filters {

long LinuxSllParser::setSink(long io, Filter *f, long ii) {
    if (io) return -1;
    s = f;
    si = ii;
    return 0;
}

long LinuxSllParser::setListener(filters::Notify *l)
{ return -1; }

long LinuxSllParser::onReceive(long id, Buffer *data) {
    if (id) return -1;
    data->setPrefix(16);
    data->setLength(data->length() - 16);
    return s->onReceive(si, data);
}

}
