/* Copyright © 2016 Wiki Wang <wikiwang@live.com>
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * the COPYING file for more details. */

#include "UdpParser.h"
#include <netinet/udp.h>
#include <arpa/inet.h>

namespace filters {

long UdpParser::onReceive(long id, Buffer *data) {
    if (id) return -1;
    udphdr *h = reinterpret_cast<udphdr *>(data->data());
    long i = *reinterpret_cast<uint32_t *>(h);
    auto it = sinks.find(i);
    if (it == sinks.end()) {
        if (listener) {
            Notify n;
            n.source = h->source;
            n.dest = h->dest;
            n.id = i;
            if (listener->onNotify(this, NOTIFY_ID, &n)) return 0;
            it = sinks.find(i);
            if (it == sinks.end()) return 0;
        }
    }
    long hl = sizeof(udphdr);
    data->setPrefix(data->prefix() + hl);
    data->setLength(ntohs(h->len) - hl);
    return it->second.f->onReceive(it->second.i, data);
}

}
