/* Copyright © 2016 Wiki Wang <wikiwang@live.com>
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * the COPYING file for more details. */

#pragma once

#include "BaseClasses/BaseObject.h"
#include <webrtc/modules/rtp_rtcp/include/rtp_rtcp_defines.h>
#include <webrtc/modules/rtp_rtcp/include/fec_receiver.h>

namespace filters {

class FecReceiver : public Filter, public BaseObject, public webrtc::RtpData {
public:
    FecReceiver();
    ~FecReceiver();

    long setSink(long id, Filter *f, long ii);
    long setListener(Notify *);

    long onReceive(long id, Buffer *data);

    int32_t OnReceivedPayloadData(const uint8_t *, const size_t, const webrtc::WebRtcRTPHeader *);
    bool OnRecoveredPacket(const uint8_t* packet, size_t packet_length);

private:
    Filter *s;
    long i;
    webrtc::FecReceiver *receiver;
    uint16_t fix;
};

inline FecReceiver::FecReceiver()
    : receiver(webrtc::FecReceiver::Create(this)) {}

}
