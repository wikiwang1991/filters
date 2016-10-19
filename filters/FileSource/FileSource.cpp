/* Copyright © 2016 Wiki Wang <wikiwang@live.com>
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * the COPYING file for more details. */

#include "FileSource.h"

#include <iostream>

namespace filters {

FileSource::FileSource(const char *f) : sink(0)
{ s.open(f, std::ifstream::in | std::ifstream::binary); }

long FileSource::setSink(long id, Filter *f, long ii) {
    if (id) return -1;
    sink = f;
    i = ii;
    return 0;
}

long FileSource::setListener(Notify *)
{ return -1; }

long FileSource::onReceive(long id, Buffer *data) {
    if (id) return -1;
    s.read(reinterpret_cast<std::ifstream::char_type *>(data->buffer()), data->length());
    if (!s) return -1;
    if (sink) sink->onReceive(i, data);
    return 0;
}

}
