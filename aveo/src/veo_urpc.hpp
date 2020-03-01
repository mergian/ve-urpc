#ifndef VEO_URPC_INCLUDE
#define VEO_URPC_INCLUDE

#include <urpc_common.h>

#ifndef __ve__
#include <CallArgs.hpp>
using veo::CallArgs;
#else
#include "ve_inst.h"
#endif

// reply timeout in us
#define REPLY_TIMEOUT 2000000

// multipart SEND/RECVFRAG transfer size
//#define PART_SENDFRAG ALIGN8B(URPC_DATA_BUFF_LEN >> 3)
#define PART_SENDFRAG (6*1024*1024)

namespace veo {

//
// URPC commands
//
enum veo_urpc_cmd
{
	URPC_CMD_NONE_         =  0,
	URPC_CMD_PING          =  1,
	URPC_CMD_EXIT          =  2,
	URPC_CMD_ACK           =  3, // ACK is a result with no (void) content
	URPC_CMD_RESULT        =  4, // result (int64_t) without stack frame
	URPC_CMD_RES_STK       =  5, // result with stack frame
        URPC_CMD_EXCEPTION     =  6, // notify about exception
	URPC_CMD_LOADLIB       =  7, // load .so
	URPC_CMD_UNLOADLIB     =  8, // unload .so
	URPC_CMD_GETSYM        =  9, // find symbol in .so
	URPC_CMD_ALLOC         = 10, // allocate buffer on VE
	URPC_CMD_FREE          = 11, // free buffer on VE
	URPC_CMD_SENDBUFF      = 12, 
	URPC_CMD_RECVBUFF      = 13,
	URPC_CMD_CALL          = 14, // simple call with no stack transfer
	URPC_CMD_CALL_STKIN    = 15, // call with stack "IN" only
	URPC_CMD_CALL_STKOUT   = 16, // call with stack "OUT" only
	URPC_CMD_CALL_STKINOUT = 17, // call with stack IN and OUT
	URPC_CMD_SLEEPING      = 18, // notify peer that we're going to sleep
	URPC_CMD_NEWPEER       = 19  // create new remote peer (AKA context) inside same proc
};

#ifndef __ve__
int64_t send_call_nolock(urpc_peer_t *up, uint64_t ve_sp, uint64_t addr,
                         CallArgs &arg);
int unpack_call_result(urpc_mb_t *m, CallArgs *arg, void *payload, size_t plen,
                       uint64_t *result);
int wait_req_result(urpc_peer_t *up, int64_t req, int64_t *result);
int wait_req_ack(urpc_peer_t *up, int64_t req);
#endif

} // namespace veo

extern "C" {
  void veo_urpc_register_handlers(urpc_peer_t *up);
#ifdef __ve__
  void veo_urpc_register_ve_handlers(urpc_peer_t *up);
#else
  void veo_urpc_register_vh_handlers(urpc_peer_t *up);
#endif
}

#endif /* VEO_URPC_INCLUDE */
