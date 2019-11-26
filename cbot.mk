#
#  This makefile adapted from the pubnub provided makefile, so that the application
#  specific files can be compiled in a new directory at the same level as c-core (which
#  has been copied without changes from c-core-master).
#
#  Hal Breidenbach   9/27/2019

SOURCEFILES = ../c-core/core/pubnub_pubsubapi.c \
              ../c-core/core/pubnub_coreapi.c \
              ../c-core/core/pubnub_coreapi_ex.c \
              ../c-core/core/pubnub_ccore_pubsub.c \
              ../c-core/core/pubnub_ccore.c \
              ../c-core/core/pubnub_netcore.c  \
              ../c-core/lib/sockets/pbpal_sockets.c \
              ../c-core/lib/sockets/pbpal_resolv_and_connect_sockets.c \
              ../c-core/lib/sockets/pbpal_handle_socket_error.c \
              ../c-core/core/pubnub_alloc_std.c \
              ../c-core/core/pubnub_assert_std.c \
              ../c-core/core/pubnub_generate_uuid.c \
              ../c-core/core/pubnub_blocking_io.c \
              ../c-core/posix/posix_socket_blocking_io.c \
              ../c-core/core/pubnub_timers.c \
              ../c-core/core/pubnub_json_parse.c \
              ../c-core/lib/md5/md5.c \
              ../c-core/lib/base64/pbbase64.c \
              ../c-core/lib/pb_strnlen_s.c \
              ../c-core/core/pubnub_helper.c \
              ../c-core/cpp/pubnub_version_posix.cpp \
              ../c-core/posix/pubnub_generate_uuid_posix.c \
              ../c-core/posix/pbpal_posix_blocking_io.c \
              ../c-core/core/pubnub_free_with_timeout_std.c \
              ../c-core/cpp/pubnub_subloop.cpp \
              ../c-core/posix/msstopwatch_monotonic_clock.c \
              ../c-core/core/pubnub_url_encode.c 

# source file for message procesing           
MESSAGESOURCE = ../lib/messages.cpp

# source files for CordieBot main app              
CBOTSOURCEFILES = ../lib/wiringPiMCP3002.cpp \
                  ../lib/wiringPiTLC59711.cpp


ifndef ONLY_PUBSUB_API
ONLY_PUBSUB_API = 0
endif

ifndef USE_PROXY
USE_PROXY = 1
endif

ifndef USE_GZIP_COMPRESSION
USE_GZIP_COMPRESSION = 1
endif

ifndef RECEIVE_GZIP_RESPONSE
RECEIVE_GZIP_RESPONSE = 1
endif

ifndef USE_SUBSCRIBE_V2
USE_SUBSCRIBE_V2 = 1
endif

ifndef USE_ADVANCED_HISTORY
USE_ADVANCED_HISTORY = 1
endif

ifndef USE_OBJECTS_API
USE_OBJECTS_API = 1
endif

ifndef DO_CORDIEBOT
DO_CORDIEBOT = 1
endif

ifeq ($(DO_CORDIEBOT), 3)            
SOURCEFILES +=  pubnublisten.cpp \
                pubnubprocess.cpp \
                cb_sync.cpp \
                subscribe_publish_callback.cpp
endif


ifeq ($(USE_PROXY), 1)
SOURCEFILES += ../c-core/core/pubnub_proxy.c \
               ../c-core/core/pubnub_proxy_core.c \
               ../c-core/core/pbhttp_digest.c \
               ../c-core/core/pbntlm_core.c \
               ../c-core/core/pbntlm_packer_std.c
endif

ifeq ($(USE_GZIP_COMPRESSION), 1)
SOURCEFILES += ../c-core/lib/miniz/miniz_tdef.c \
               ../c-core/lib/miniz/miniz.c \
               ../c-core/lib/pbcrc32.c \
               ../c-core/core/pbgzip_compress.c
OBJFILES += miniz_tdef.o miniz.o pbcrc32.o pbgzip_compress.o
endif

ifeq ($(RECEIVE_GZIP_RESPONSE), 1)
SOURCEFILES += ../c-core/lib/miniz/miniz_tinfl.c \
               ../c-core/core/pbgzip_decompress.c
OBJFILES += miniz_tinfl.o pbgzip_decompress.o
endif

ifeq ($(USE_SUBSCRIBE_V2), 1)
SOURCEFILES += ../c-core/core/pbcc_subscribe_v2.c \
               ../c-core/core/pubnub_subscribe_v2.c 
OBJFILES += pbcc_subscribe_v2.o pubnub_subscribe_v2.o
endif

ifeq ($(USE_ADVANCED_HISTORY), 1)
SOURCEFILES += ../c-core/core/pbcc_advanced_history.c \
               ../c-core/core/pubnub_advanced_history.c
OBJFILES += pbcc_advanced_history.o pubnub_advanced_history.o
endif

ifeq ($(USE_OBJECTS_API), 1)
SOURCEFILES += ../c-core/core/pbcc_objects_api.c \
               ../c-core/core/pubnub_objects_api.c
OBJFILES += pbcc_objects_api.o pubnub_objects_api.o
endif

OS := $(shell uname)
ifeq ($(OS),Darwin)
SOURCEFILES += ../c-core/posix/monotonic_clock_get_time_darwin.c
LDLIBS=-lpthread
else
SOURCEFILES += ../c-core/posix/monotonic_clock_get_time_posix.c
LDLIBS=-lrt -lpthread
endif

CFLAGS =-g -I .. -I . \
                 -I ../c-core \
                 -I ../c-core/cpp \
                 -I ../c-core/core \
                 -I ../c-core/posix \
                 -I ../lib \
                 -Wall \
                 -D PUBNUB_THREADSAFE \
                 -D PUBNUB_LOG_LEVEL=PUBNUB_LOG_LEVEL_WARNING \
                 -D PUBNUB_ONLY_PUBSUB_API=$(ONLY_PUBSUB_API) \
                 -D PUBNUB_PROXY_API=$(USE_PROXY) \
                 -D PUBNUB_USE_GZIP_COMPRESSION=$(USE_GZIP_COMPRESSION) \
                 -D PUBNUB_RECEIVE_GZIP_RESPONSE=$(RECEIVE_GZIP_RESPONSE) \
                 -D PUBNUB_USE_SUBSCRIBE_V2=$(USE_SUBSCRIBE_V2) \
                 -D PUBNUB_USE_OBJECTS_API=$(USE_OBJECTS_API)
# -g enables debugging, remove to get a smaller executable


#all: cpp11 cpp98
all: cpp11 

ifeq ($(DO_CORDIEBOT), 1)

#cpp98:      cordiebot_pubnubpipe \

#cpp98:      subscribe_publish_callback_sample
            
cpp11:      cordiebot_process \
            cordiebot
else
#cpp98: pubnub_sync_sample \
#       pubnub_callback_sample \
#       cancel_subscribe_sync_sample \
#       subscribe_publish_callback_sample \
#       futres_nesting_sync \
#       futres_nesting_callback \
#       pubnub_sync_subloop_sample \
#       pubnub_callback_subloop_sample
       
#cpp11: pubnub_callback_cpp11_sample \
#       futres_nesting_callback_cpp11 \
#       fntest_runner \
#       pubnub_callback_cpp11_subloop_sample 

endif

ifeq ("x","y")
pubnub_sync_sample: ../c-core/cpp/samples/pubnub_sample.cpp \
                $(SOURCEFILES) ../c-core/core/pubnub_ntf_sync.c \
                               ../c-core/cpp/pubnub_futres_sync.cpp
	$(CXX) -o $@ $(CFLAGS)  -x c++ ../c-core/cpp/samples/pubnub_sample.cpp \
	                               ../c-core/core/pubnub_ntf_sync.c \
	                               ../c-core/cpp/pubnub_futres_sync.cpp \
	                               $(SOURCEFILES) $(LDLIBS)
	                               


cancel_subscribe_sync_sample: ../c-core/cpp/samples/cancel_subscribe_sync_sample.cpp \
                $(SOURCEFILES) ../c-core/core/pubnub_ntf_sync.c \
                                ../c-core/cpp/pubnub_futres_sync.cpp
	$(CXX) -o $@ $(CFLAGS)  -x c++ ../c-core/cpp/samples/cancel_subscribe_sync_sample.cpp \
	                               ../c-core/core/pubnub_ntf_sync.c \
	                               ../c-core/cpp/pubnub_futres_sync.cpp \
	                               $(SOURCEFILES) $(LDLIBS)

futres_nesting_sync: ../c-core/cpp/samples/futres_nesting.cpp \
               $(SOURCEFILES) ../c-core/core/pubnub_ntf_sync.c \
                              ../c-core/cpp/pubnub_futres_sync.cpp
	$(CXX) -o $@ $(CFLAGS)  -x c++ ../c-core/cpp/samples/futres_nesting.cpp \
	                              ../c-core/core/pubnub_ntf_sync.c \
	                               ../c-core/cpp/pubnub_futres_sync.cpp \
	                               $(SOURCEFILES) $(LDLIBS)

pubnub_sync_subloop_sample: ../c-core/cpp/samples/pubnub_subloop_sample.cpp \
               $(SOURCEFILES) ../c-core/core/pubnub_ntf_sync.c \
                              ../c-core/cpp/pubnub_futres_sync.cpp
	$(CXX) -o $@ $(CFLAGS)  -x c++ ../c-core/cpp/samples/pubnub_subloop_sample.cpp \
	                               ../c-core/core/pubnub_ntf_sync.c \
	                               ../c-core/cpp/pubnub_futres_sync.cpp \
	                               $(SOURCEFILES) $(LDLIBS)
endif
##
# The socket poller module to use. You should use the `poll` poller, it
# doesn't have the weird restrictions of `select` poller. OTOH,
# select() on Windows is compatible w/BSD sockets select(), while
# WSAPoll() has some weird differences to poll().  The names are the
# same until the last `_`, then it's `poll` vs `select`.
SOCKET_POLLER_C=../c-core/lib/sockets/pbpal_ntf_callback_poller_poll.c
SOCKET_POLLER_OBJ=pbpal_ntf_callback_poller_poll.o

CALLBACK_INTF_SOURCEFILES= ../c-core/posix/pubnub_ntf_callback_posix.c \
                           ../c-core/posix/pubnub_get_native_socket.c \
                           ../c-core/core/pubnub_timer_list.c \
                           ../c-core/lib/sockets/pbpal_adns_sockets.c \
                           ../c-core/lib/pubnub_dns_codec.c $(SOCKET_POLLER_C)  \
                           ../c-core/core/pbpal_ntf_callback_queue.c \
                           ../c-core/core/pbpal_ntf_callback_admin.c \
                           ../c-core/core/pbpal_ntf_callback_handle_timer_list.c  \
                           ../c-core/core/pubnub_callback_subscribe_loop.c
CALLBACK_INTF_OBJFILES=pubnub_ntf_callback_posix.o \
                       pubnub_get_native_socket.o \
                       pubnub_timer_list.o \
                       pbpal_adns_sockets.o \
                       pubnub_dns_codec.o \
                       $(SOCKET_POLLER_OBJ) \
                       pbpal_ntf_callback_queue.o \
                       pbpal_ntf_callback_admin.o \
                       pbpal_ntf_callback_handle_timer_list.o \
                       pubnub_callback_subscribe_loop.o

ifndef USE_DNS_SERVERS
USE_DNS_SERVERS = 1
endif

ifndef USE_IPV6
USE_IPV6 = 1
endif

ifeq ($(USE_DNS_SERVERS), 1)
CALLBACK_INTF_SOURCEFILES += ../c-core/core/pubnub_dns_servers.c \
                             ../c-core/posix/pubnub_dns_system_servers.c \
                             ../c-core/lib/pubnub_parse_ipv4_addr.c
CALLBACK_INTF_OBJFILES += pubnub_dns_servers.o \
                          pubnub_dns_system_servers.o \
                          pubnub_parse_ipv4_addr.o
endif

ifeq ($(USE_IPV6), 1)
CALLBACK_INTF_SOURCEFILES += ../c-core/lib/pubnub_parse_ipv6_addr.c
CALLBACK_INTF_OBJFILES += pubnub_parse_ipv6_addr.o
endif

CFLAGS_CALLBACK = -D PUBNUB_USE_IPV6=$(USE_IPV6) -D PUBNUB_SET_DNS_SERVERS=$(USE_DNS_SERVERS)

#ifeq ($(DO_CORDIEBOT), 1)
ifeq ("x","y")
subscribe_publish_callback_sample: subscribe_publish_callback_sample.cpp \
            $(SOURCEFILES) $(CALLBACK_INTF_SOURCEFILES) \
            ../c-core/cpp/pubnub_futres_posix.cpp
	$(CXX) -o $@ -ljsoncpp -D PUBNUB_CALLBACK_API $(CFLAGS) $(CFLAGS_CALLBACK) \
	             -x c++ subscribe_publish_callback_sample.cpp \
	                    $(CALLBACK_INTF_SOURCEFILES) \
	                    ../c-core/cpp/pubnub_futres_posix.cpp \
	                    $(SOURCEFILES) $(LDLIBS)
endif



ifeq ($(DO_CORDIEBOT), 1)
	                        
#cordiebot: cordiebot.cpp  $(CBOTSOURCEFILES) $(MESSAGESOURCE)
cordiebot: cordiebot.cpp  $(MESSAGESOURCE)
	$(CXX) -o $@ -std=c++11 -ljsoncpp \
	                   $(CFLAGS)  \
	                -x c++  cordiebot.cpp \
	                        $(MESSAGESOURCE)
#	                        $(CBOTSOURCEFILES) $(MESSAGESOURCE)
	                        
cordiebot_process: pubnubprocess.cpp \
                                      $(SOURCEFILES) $(MESSAGESOURCE) \
                                       $(CALLBACK_INTF_SOURCEFILES) \
                                      ../c-core/cpp/pubnub_futres_cpp11.cpp
	$(CXX) -o $@ -std=c++11 -ljsoncpp \
	                   -D PUBNUB_CALLBACK_API $(CFLAGS) $(CFLAGS_CALLBACK) \
	                -x c++  pubnubprocess.cpp \
	                        $(CALLBACK_INTF_SOURCEFILES) \
	                        ../c-core/cpp/pubnub_futres_cpp11.cpp \
	                        $(SOURCEFILES) $(LDLIBS) $(MESSAGESOURCE)
endif



clean:
	rm cordibot \
	    cordibot_process \
	   ../c-core/fntest_runner \
	   ../c-core/*.dSYM
