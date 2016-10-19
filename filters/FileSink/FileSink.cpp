/* Copyright © 2016 Wiki Wang <wikiwang@live.com>
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * the COPYING file for more details. */

#include "FileSink.h"

namespace filters {

long FileSink::setSink(long, Filter *, long)
{ return -1; }

long FileSink::setListener(Notify *)
{ return -1; }

long FileSink::onReceive(long id, Buffer *data) {
    if (id) return -1;
    f.write(reinterpret_cast<std::ofstream::char_type *>(data->data()), data->length());
    return 0;
}

}
