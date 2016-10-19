/* Copyright © 2016 Wiki Wang <wikiwang@live.com>
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * the COPYING file for more details. */

#include "BaseObject.h"

namespace filters {

long BaseObject::addRef()
{ ++count; return count; }

long BaseObject::release() {
    long c = --count;
    if (!c) delete this;
    return c;
}

BaseObject::~BaseObject() {}

}
