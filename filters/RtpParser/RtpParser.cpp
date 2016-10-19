/* Copyright © 2016 Wiki Wang <wikiwang@live.com>
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * the COPYING file for more details. */

#include "RtpParser.h"
#include <bitstream/ietf/rtp.h>

namespace filters {

long RtpParser::onReceive(long id, Buffer *data) {
    if (id) return -1;
    uint8_t *rtp = reinterpret_cast<uint8_t *>(data->data());
    if (!rtp_check_hdr(rtp)) return -1;
    uint8_t *payload = rtp_payload(rtp);
    long is = payload - rtp;
    data->setTimestamp(rtp_get_timestamp(rtp));
    data->setPrefix(data->prefix() + is);
    data->setLength(data->length() - is);
    Notify n;
    rtp_get_ssrc(rtp, reinterpret_cast<uint8_t *>(&n.ssrc));
    n.type = rtp_get_type(rtp);
    auto it = set.find(n);
    if (it == set.end()) {
        n.id = i;
        if (!listener->onNotify(this, NOTIFY_ID, &n)) {
            it = set.emplace(n).first;
            ++i;
        } else return 0;
    }
    const auto &it1 = sinks.find(it->id);
    if (it1 == sinks.end()) return 0;
    const auto &pin = it1->second;
    return pin.f->onReceive(pin.i, data);
}

}
