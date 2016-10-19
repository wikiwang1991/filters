/* Copyright © 2016 Wiki Wang <wikiwang@live.com>
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * the COPYING file for more details. */

#pragma once

#include "Filter.h"

namespace filters {

class BaseObject : virtual Object {
public:
    BaseObject();

    long addRef();
    long release();

protected:
    virtual ~BaseObject();

    long count;
};

inline BaseObject::BaseObject() : count(1) {}

}
