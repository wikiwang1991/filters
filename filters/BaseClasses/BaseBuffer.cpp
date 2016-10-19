/* Copyright © 2016 Wiki Wang <wikiwang@live.com>
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * the COPYING file for more details. */

#include "BaseBuffer.h"
#include <cstdlib>

namespace filters {

long ReferenceBuffer::addRef()
{ return 0; }

long ReferenceBuffer::release()
{ return 0; }

const void *ReferenceBuffer::buffer() const
{ return b; }

long ReferenceBuffer::prefix() const
{ return p; }

long ReferenceBuffer::length() const
{ return l; }

long ReferenceBuffer::timestamp() const
{ return t; }

long ReferenceBuffer::size() const
{ return s; }

void *ReferenceBuffer::buffer()
{ return b; }

long ReferenceBuffer::setPrefix(long _p)
{ p = _p; return p; }

long ReferenceBuffer::setLength(long _l)
{ l = _l; return l; }

long ReferenceBuffer::setTimestamp(long _t)
{ t = _t; return t; }

long ReferenceBuffer::setSize(long)
{ return -1; }

const void *SystemBuffer::buffer() const
{ return b; }

long SystemBuffer::prefix() const
{ return p; }

long SystemBuffer::length() const
{ return l; }

long SystemBuffer::timestamp() const
{ return t; }

long SystemBuffer::size() const
{ return s; }

void *SystemBuffer::buffer()
{ return b; }

long SystemBuffer::setPrefix(long _p)
{ p = _p; return p; }

long SystemBuffer::setLength(long _l)
{ l = _l; return l; }

long SystemBuffer::setTimestamp(long _t)
{ t = _t; return t; }

long SystemBuffer::setSize(long _s) {
    s = _s;
    b = realloc(b, s);
    return s;
}

SystemBuffer::~SystemBuffer()
{ free(b); }



}
