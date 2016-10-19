/* Copyright © 2016 Wiki Wang <wikiwang@live.com>
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * the COPYING file for more details. */

#pragma once

#include "BaseClasses/BaseObject.h"

namespace filters {

class LinuxSllParser : public Filter, public BaseObject {
public:
    long setSink(long io, Filter *f, long ii);
    long setListener(Notify *l);

    long onReceive(long id, Buffer *data);

private:
    Filter *s;
    long si;
};

}
