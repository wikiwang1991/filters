/* Copyright © 2016 Wiki Wang <wikiwang@live.com>
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * the COPYING file for more details. */

#pragma once

#include <cstdint>

namespace filters {

struct Object {
    virtual long addRef() = 0;
    virtual long release() = 0;
};

struct Buffer : virtual Object {
    virtual const void *buffer() const = 0;
    virtual long prefix() const = 0;
    virtual long length() const = 0;
    virtual long timestamp() const = 0;
    virtual long size() const = 0;

    virtual void *buffer() = 0;
    virtual long setPrefix(long p) = 0;
    virtual long setLength(long l) = 0;
    virtual long setTimestamp(long t) = 0;
    virtual long setSize(long s) = 0;

    void *data();
};

inline void *Buffer::data()
{ return reinterpret_cast<char *>(buffer()) + prefix(); }

struct Notify;

struct Filter : virtual Object {
    virtual long setSink(long io, Filter *f, long ii) = 0;
    virtual long setListener(Notify *l) = 0;

    virtual long onReceive(long id, Buffer *data) = 0;
};

struct Notify { virtual long onNotify(Filter *sender, long msg, void *param) = 0; };

struct Controller : virtual Object {
    virtual long run() = 0;
    virtual long pause() = 0;
    virtual long stop() = 0;
};

}
