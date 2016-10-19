/* Copyright © 2016 Wiki Wang <wikiwang@live.com>
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * the COPYING file for more details. */

#pragma once

#include "BaseObject.h"

namespace filters {

class ReferenceBuffer : public virtual Buffer {
public:
    ReferenceBuffer(void *b, long s);

    long addRef();
    long release();

    const void *buffer() const;
    long prefix() const;
    long length() const;
    long timestamp() const;
    long size() const;

    void *buffer();
    long setPrefix(long p);
    long setLength(long l);
    long setTimestamp(long t);
    long setSize(long);

private:
    void *b;
    long p, l, t, s;
};

class SystemBuffer : public virtual Buffer, public BaseObject {
public:
    SystemBuffer();

    const void *buffer() const;
    long prefix() const;
    long length() const;
    long timestamp() const;
    long size() const;

    void *buffer();
    long setPrefix(long p);
    long setLength(long l);
    long setTimestamp(long t);
    long setSize(long s);

protected:
    ~SystemBuffer();

private:
    void *b;
    long p, l, t, s;
};

inline ReferenceBuffer::ReferenceBuffer(void *b, long s) : b(b), p(0), l(0), t(0), s(s) {}

inline SystemBuffer::SystemBuffer(): b(0), p(0), l(0), t(0), s(0) {}

}
