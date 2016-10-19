/* Copyright © 2016 Wiki Wang <wikiwang@live.com>
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * the COPYING file for more details. */

#include "FecReceiver.h"
#include <webrtc/modules/rtp_rtcp/source/byte_io.h>
#include <webrtc/base/logging.h>
#include <bitstream/ietf/rtp.h>
#include "BaseClasses/BaseBuffer.h"

static constexpr size_t kMaxExtensionHeaders = 14;
static constexpr size_t kFixedHeaderSize = 12;
static constexpr uint8_t kRtpVersion = 2;
static constexpr uint16_t kOneByteExtensionId = 0xBEDE;
static constexpr size_t kOneByteHeaderSize = 1;

static inline bool RtpPacketParseBufferAndGetHeader(const uint8_t* buffer, size_t size, webrtc::RTPHeader* header) {
    if (size < kFixedHeaderSize) {
        return false;
    }
    const uint8_t version = buffer[0] >> 6;
    if (version != kRtpVersion) {
        return false;
    }
    const bool has_padding = (buffer[0] & 0x20) != 0;
    const bool has_extension = (buffer[0] & 0x10) != 0;
    const uint8_t number_of_crcs = buffer[0] & 0x0f;
    header->markerBit = (buffer[1] & 0x80) != 0;
    header->payloadType = buffer[1] & 0x7f;

    header->sequenceNumber = webrtc::ByteReader<uint16_t>::ReadBigEndian(&buffer[2]);
    header->timestamp = webrtc::ByteReader<uint32_t>::ReadBigEndian(&buffer[4]);
    header->ssrc = webrtc::ByteReader<uint32_t>::ReadBigEndian(&buffer[8]);
    if (size < kFixedHeaderSize + number_of_crcs * 4) {
        return false;
    }
    header->headerLength = kFixedHeaderSize + number_of_crcs * 4;

    if (has_padding) {
        header->paddingLength = buffer[size - 1];
        if (header->paddingLength == 0) {
            LOG(LS_WARNING) << "Padding was set, but padding size is zero";
            return false;
        }
    } else {
        header->paddingLength = 0;
    }

    uint8_t num_extensions_ = 0;
    uint16_t extensions_size_ = 0;
    if (has_extension) {
        /* RTP header extension, RFC 3550.
     0                   1                   2                   3
     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |      defined by profile       |           length              |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |                        header extension                       |
    |                             ....                              |
    */
        size_t extension_offset = header->headerLength + 4;
        if (extension_offset > size) {
            return false;
        }
        uint16_t profile =
                webrtc::ByteReader<uint16_t>::ReadBigEndian(&buffer[header->headerLength]);
        size_t extensions_capacity =
                webrtc::ByteReader<uint16_t>::ReadBigEndian(&buffer[header->headerLength + 2]);
        extensions_capacity *= 4;
        if (extension_offset + extensions_capacity > size) {
            return false;
        }
        if (profile != kOneByteExtensionId) {
            LOG(LS_WARNING) << "Unsupported rtp extension " << profile;
        } else {
            constexpr uint8_t kPaddingId = 0;
            constexpr uint8_t kReservedId = 15;
            while (extensions_size_ + kOneByteHeaderSize < extensions_capacity) {
                uint8_t id = buffer[extension_offset + extensions_size_] >> 4;
                if (id == kReservedId) {
                    break;
                } else if (id == kPaddingId) {
                    extensions_size_++;
                    continue;
                }
                uint8_t length =
                        1 + (buffer[extension_offset + extensions_size_] & 0xf);
                extensions_size_ += kOneByteHeaderSize;
                if (num_extensions_ >= kMaxExtensionHeaders) {
                    LOG(LS_WARNING) << "Too many extensions.";
                    return false;
                }

                num_extensions_++;
                extensions_size_ += length;
            }
        }
        header->headerLength = extension_offset + extensions_capacity;
    }

    if (header->headerLength + header->paddingLength > size) {
        return false;
    }

    header->payload_type_frequency = 0;
    header->extension.hasTransmissionTimeOffset = false;
    header->extension.hasAbsoluteSendTime = false;
    header->extension.hasTransportSequenceNumber = false;
    header->extension.hasAudioLevel = false;
    header->extension.hasVideoRotation = false;

    return true;
}

namespace filters {

FecReceiver::~FecReceiver()
{ delete receiver; }

long FecReceiver::setSink(long id, Filter *f, long ii) {
    if (id) return -1;
    s = f;
    i = ii;
    return 0;
}

long filters::FecReceiver::setListener(filters::Notify *)
{ return -1; }

long FecReceiver::onReceive(long id, Buffer *data) {
    webrtc::RTPHeader rtpHeader;
    bool ret = RtpPacketParseBufferAndGetHeader((uint8_t *)data->data() - 12, data->length() + 12, &rtpHeader);
    if (!ret) return -1;
    ++fix;
    receiver->AddReceivedRedPacket(rtpHeader, (uint8_t *)data->data() - 12, data->length() + 12, 99); // TODO: config red.
    receiver->ProcessReceivedFec();
    return 0;
}

int32_t FecReceiver::OnReceivedPayloadData(const uint8_t *, const size_t, const webrtc::WebRtcRTPHeader *) {}

bool FecReceiver::OnRecoveredPacket(const uint8_t *packet, size_t packet_length) {
    uint8_t *rtp = const_cast<uint8_t *>(packet);
    rtp_set_seqnum(rtp, rtp_get_seqnum(rtp) - --fix);
    ReferenceBuffer data(rtp, packet_length);
    data.setTimestamp(rtp_get_timestamp(rtp));
    data.setPrefix(12);
    data.setLength(packet_length - 12);
    s->onReceive(i, &data);
    return true;
}

}
