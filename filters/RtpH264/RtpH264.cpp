/* Copyright © 2016 Wiki Wang <wikiwang@live.com>
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * the COPYING file for more details. */

#include "RtpH264.h"
#include <cstring>
#include <assert.h>

namespace filters {

RtpH264::~RtpH264()
{ pkt->release(); }

long RtpH264::setSink(long id, Filter *f, long ii) {
    if (id) return -1;
    s = f;
    i = ii;
    return 0;
}

long RtpH264::setListener(Notify *)
{ return -1; }

long RtpH264::onReceive(long id, Buffer *data) {
    if (id) return -1;
    const uint8_t *buf = reinterpret_cast<uint8_t *>(data->data());
    long len = data->length();
    uint8_t nal = buf[0];
    uint8_t type = (nal & 0x1f);
    constexpr uint8_t start_sequence[] = { 0, 0, 1 };
    if (type >= 1 && type <= 23)
        type = 1;           // simplify the case. (these are all the nal types used internally by the h264 codec)
    switch (type) {
    case 0:                 // undefined;
        return -1;
    case 1: {
        data->setPrefix(data->prefix() - sizeof(start_sequence));
        data->setLength(len + sizeof(start_sequence));
        memcpy(data->data(), start_sequence, sizeof(start_sequence));
        return s->onReceive(i, data);
    } case 24:              // STAP-A (one packet, multiple nals)
        // consume the STAP-A NAL
        ++buf;
        --len;
        // first we are going to figure out the total size....
    {
        int pass = 0;
        int total_length = 0;
        uint8_t *dst = NULL;
        for (pass = 0; pass < 2; ++pass) {
            const uint8_t *src = buf;
            int src_len = len;
            do {
                uint16_t nal_size = (src[0] << 8) | src[1]; // this going to be a problem if unaligned (can it be?)
                // consume the length of the aggregate...
                src += 2;
                src_len -= 2;
                if (nal_size <= src_len) {
                    if (pass == 0) {
                        // counting...
                        total_length += sizeof(start_sequence) + nal_size;
                    } else {
                        // copying
                        assert(dst);
                        memcpy(dst, start_sequence, sizeof(start_sequence));
                        dst += sizeof(start_sequence);
                        memcpy(dst, src, nal_size);
                        dst += nal_size;
                    }
                } else return -1;
                // eat what we handled...
                src += nal_size;
                src_len -= nal_size;
                if (src_len < 0) return -1;
            } while (src_len > 2); // because there could be rtp padding..
            if (pass == 0) {
                // now we know the total size of the packet (with the start sequences added)
                if (total_length > pkt->size())
                    pkt->setSize(total_length);
                dst = reinterpret_cast<uint8_t *>(pkt->data());
            } else {
                assert(dst - reinterpret_cast<uint8_t *>(pkt->data()) == total_length);
                pkt->setLength(total_length);
            }
        }
    }
        pkt->setTimestamp(data->timestamp());
        return s->onReceive(i, pkt);
    case 25:                // STAP-B
    case 26:                // MTAP-16
    case 27:                // MTAP-24
    case 29:                // FU-B
        return -1;
    case 28:                // FU-A (fragmented nal)
        ++buf;
        --len;              // skip the fu_indicator
    {
        // these are the same as above, we just redo them here for clarity...
        uint8_t fu_indicator = nal;
        uint8_t fu_header = *buf; // read the fu_header.
        uint8_t start_bit = fu_header >> 7;
        uint8_t end_bit = (fu_header & 0x40) >> 6;
        uint8_t nal_type = (fu_header & 0x1f);
        uint8_t reconstructed_nal;
        // reconstruct this packet's true nal; only the data follows..
        reconstructed_nal = fu_indicator & (0xe0); // the original nal forbidden bit and NRI are stored in this packet's nal;
        reconstructed_nal |= nal_type;
        // skip the fu_header...
        ++buf;
        --len;
        if (start_bit) {
            pkt->setLength(0);
            // copy in the start sequence, and the reconstructed nal....
            int total_length = sizeof(start_sequence) + sizeof(nal) + len;
            if (total_length > pkt->size())
                pkt->setSize(total_length);
            memcpy(pkt->data(), start_sequence, sizeof(start_sequence));
            reinterpret_cast<uint8_t *>(pkt->data())[sizeof(start_sequence)]= reconstructed_nal;
            memcpy(reinterpret_cast<uint8_t *>(pkt->data()) + sizeof(start_sequence) + sizeof(nal), buf, len);
        } else {
            long pl = pkt->length();
            if (len > pkt->size() - pl)
                pkt->setSize(pl + len);
            memcpy(reinterpret_cast<uint8_t *>(pkt->data()) + pl, buf, len);
            pkt->setLength(pl + len);
            if (end_bit) {
                pkt->setTimestamp(data->timestamp());
                return s->onReceive(i, pkt);
            }
        }
    }
        return 0;
    case 30:                // undefined
    case 31:                // undefined
    default: return -1;
    }
}

}
