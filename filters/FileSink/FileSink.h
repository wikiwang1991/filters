/* Copyright © 2016 Wiki Wang <wikiwang@live.com>
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * the COPYING file for more details. */

#pragma once

#include "BaseClasses/BaseObject.h"
#include <fstream>

namespace filters {

class FileSink : public Filter, public BaseObject {
public:
    FileSink(const char *file);

    long setSink(long, Filter *, long);
    long setListener(Notify *);

    long onReceive(long id, Buffer *data);

private:
    std::ofstream f;
};

inline FileSink::FileSink(const char *file)
{ f.open(file, std::ofstream::out | std::ofstream::binary); }

}
