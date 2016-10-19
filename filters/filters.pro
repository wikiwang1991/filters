#-------------------------------------------------
#
# Project created by QtCreator 2016-10-13T10:37:36
#
#-------------------------------------------------

QT       -= core gui

TARGET = filters
TEMPLATE = lib
CONFIG += staticlib

DEFINES += WEBRTC_POSIX

INCLUDEPATH += FecReceiver

SOURCES += \
    BaseClasses/BaseFilter.cpp \
    FileSource/FileSource.cpp \
    BaseClasses/BaseBuffer.cpp \
    BaseClasses/BaseObject.cpp \
    PcapParser/PcapParser.cpp \
    BaseClasses/Thread.cpp \
    LinuxSllParser/LinuxSllParser.cpp \
    IpParser/IpParser.cpp \
    UdpParser/UdpParser.cpp \
    RtpParser/RtpParser.cpp \
    FileSink/FileSink.cpp \
    FecReceiver/FecReceiver.cpp \
    FecReceiver/webrtc/common_types.cc \
    FecReceiver/webrtc/base/checks.cc \
    FecReceiver/webrtc/base/criticalsection.cc \
    FecReceiver/webrtc/base/event.cc \
    FecReceiver/webrtc/base/logging.cc \
    FecReceiver/webrtc/base/platform_thread.cc \
    FecReceiver/webrtc/base/stringencode.cc \
    FecReceiver/webrtc/base/thread_checker_impl.cc \
    FecReceiver/webrtc/base/timeutils.cc \
    FecReceiver/webrtc/modules/rtp_rtcp/source/fec_receiver_impl.cc \
    FecReceiver/webrtc/modules/rtp_rtcp/source/forward_error_correction_internal.cc \
    FecReceiver/webrtc/modules/rtp_rtcp/source/forward_error_correction.cc \
    RtpH264/RtpH264.cpp

HEADERS += \
    Filter.h \
    BaseClasses/BaseFilter.h \
    FileSource/FileSource.h \
    BaseClasses/BaseBuffer.h \
    BaseClasses/BaseObject.h \
    PcapParser/PcapParser.h \
    BaseClasses/Thread.h \
    LinuxSllParser/LinuxSllParser.h \
    IpParser/IpParser.h \
    UdpParser/UdpParser.h \
    RtpParser/RtpParser.h \
    FileSink/FileSink.h \
    FecReceiver/FecReceiver.h \
    FecReceiver/webrtc/common_types.h \
    FecReceiver/webrtc/typedefs.h \
    FecReceiver/webrtc/base/atomicops.h \
    FecReceiver/webrtc/base/basictypes.h \
    FecReceiver/webrtc/base/checks.h \
    FecReceiver/webrtc/base/constructormagic.h \
    FecReceiver/webrtc/base/criticalsection.h \
    FecReceiver/webrtc/base/event.h \
    FecReceiver/webrtc/base/logging.h \
    FecReceiver/webrtc/base/platform_thread_types.h \
    FecReceiver/webrtc/base/platform_thread.h \
    FecReceiver/webrtc/base/refcount.h \
    FecReceiver/webrtc/base/scoped_ptr.h \
    FecReceiver/webrtc/base/scoped_ref_ptr.h \
    FecReceiver/webrtc/base/stringencode.h \
    FecReceiver/webrtc/base/stringutils.h \
    FecReceiver/webrtc/base/template_util.h \
    FecReceiver/webrtc/base/thread_annotations.h \
    FecReceiver/webrtc/base/thread_checker_impl.h \
    FecReceiver/webrtc/base/thread_checker.h \
    FecReceiver/webrtc/base/timeutils.h \
    FecReceiver/webrtc/common_video/rotation.h \
    FecReceiver/webrtc/modules/include/module_common_types.h \
    FecReceiver/webrtc/modules/rtp_rtcp/include/fec_receiver.h \
    FecReceiver/webrtc/modules/rtp_rtcp/include/rtp_rtcp_defines.h \
    FecReceiver/webrtc/modules/rtp_rtcp/source/byte_io.h \
    FecReceiver/webrtc/modules/rtp_rtcp/source/fec_private_tables_bursty.h \
    FecReceiver/webrtc/modules/rtp_rtcp/source/fec_private_tables_random.h \
    FecReceiver/webrtc/modules/rtp_rtcp/source/fec_receiver_impl.h \
    FecReceiver/webrtc/modules/rtp_rtcp/source/forward_error_correction_internal.h \
    FecReceiver/webrtc/modules/rtp_rtcp/source/forward_error_correction.h \
    FecReceiver/webrtc/system_wrappers/include/clock.h \
    FecReceiver/webrtc/system_wrappers/include/rw_lock_wrapper.h \
    RtpH264/RtpH264.h
