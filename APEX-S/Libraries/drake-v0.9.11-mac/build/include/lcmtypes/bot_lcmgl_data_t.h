/** THIS IS AN AUTOMATICALLY GENERATED FILE.  DO NOT MODIFY
 * BY HAND!!
 *
 * Generated by lcm-gen
 **/

#include <stdint.h>
#include <stdlib.h>
#include <lcm/lcm_coretypes.h>
#include <lcm/lcm.h>

#ifndef _bot_lcmgl_data_t_h
#define _bot_lcmgl_data_t_h

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _bot_lcmgl_data_t bot_lcmgl_data_t;
struct _bot_lcmgl_data_t
{
    char*      name;
    int32_t    scene;
    int32_t    sequence;
    int32_t    datalen;
    uint8_t    *data;
};

bot_lcmgl_data_t   *bot_lcmgl_data_t_copy(const bot_lcmgl_data_t *p);
void bot_lcmgl_data_t_destroy(bot_lcmgl_data_t *p);

typedef struct _bot_lcmgl_data_t_subscription_t bot_lcmgl_data_t_subscription_t;
typedef void(*bot_lcmgl_data_t_handler_t)(const lcm_recv_buf_t *rbuf,
             const char *channel, const bot_lcmgl_data_t *msg, void *user);

int bot_lcmgl_data_t_publish(lcm_t *lcm, const char *channel, const bot_lcmgl_data_t *p);
bot_lcmgl_data_t_subscription_t* bot_lcmgl_data_t_subscribe(lcm_t *lcm, const char *channel, bot_lcmgl_data_t_handler_t f, void *userdata);
int bot_lcmgl_data_t_unsubscribe(lcm_t *lcm, bot_lcmgl_data_t_subscription_t* hid);
int bot_lcmgl_data_t_subscription_set_queue_capacity(bot_lcmgl_data_t_subscription_t* subs,
                              int num_messages);


int  bot_lcmgl_data_t_encode(void *buf, int offset, int maxlen, const bot_lcmgl_data_t *p);
int  bot_lcmgl_data_t_decode(const void *buf, int offset, int maxlen, bot_lcmgl_data_t *p);
int  bot_lcmgl_data_t_decode_cleanup(bot_lcmgl_data_t *p);
int  bot_lcmgl_data_t_encoded_size(const bot_lcmgl_data_t *p);

// LCM support functions. Users should not call these
int64_t __bot_lcmgl_data_t_get_hash(void);
int64_t __bot_lcmgl_data_t_hash_recursive(const __lcm_hash_ptr *p);
int     __bot_lcmgl_data_t_encode_array(void *buf, int offset, int maxlen, const bot_lcmgl_data_t *p, int elements);
int     __bot_lcmgl_data_t_decode_array(const void *buf, int offset, int maxlen, bot_lcmgl_data_t *p, int elements);
int     __bot_lcmgl_data_t_decode_array_cleanup(bot_lcmgl_data_t *p, int elements);
int     __bot_lcmgl_data_t_encoded_array_size(const bot_lcmgl_data_t *p, int elements);
int     __bot_lcmgl_data_t_clone_array(const bot_lcmgl_data_t *p, bot_lcmgl_data_t *q, int elements);

#ifdef __cplusplus
}
#endif

#endif
