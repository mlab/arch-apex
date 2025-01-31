/** THIS IS AN AUTOMATICALLY GENERATED FILE.  DO NOT MODIFY
 * BY HAND!!
 *
 * Generated by lcm-gen
 **/

#include <string.h>
#include "lcmtypes/bot_procman_command2_t.h"

static int __bot_procman_command2_t_hash_computed;
static int64_t __bot_procman_command2_t_hash;

int64_t __bot_procman_command2_t_hash_recursive(const __lcm_hash_ptr *p)
{
    const __lcm_hash_ptr *fp;
    for (fp = p; fp != NULL; fp = fp->parent)
        if (fp->v == __bot_procman_command2_t_get_hash)
            return 0;

    const __lcm_hash_ptr cp = { p, (void*)__bot_procman_command2_t_get_hash };
    (void) cp;

    int64_t hash = 0xfc82ea7fd014c086LL
         + __string_hash_recursive(&cp)
         + __string_hash_recursive(&cp)
         + __string_hash_recursive(&cp)
         + __boolean_hash_recursive(&cp)
         + __int8_t_hash_recursive(&cp)
         + __float_hash_recursive(&cp)
         + __int32_t_hash_recursive(&cp)
         + __string_hash_recursive(&cp)
         + __string_hash_recursive(&cp)
        ;

    return (hash<<1) + ((hash>>63)&1);
}

int64_t __bot_procman_command2_t_get_hash(void)
{
    if (!__bot_procman_command2_t_hash_computed) {
        __bot_procman_command2_t_hash = __bot_procman_command2_t_hash_recursive(NULL);
        __bot_procman_command2_t_hash_computed = 1;
    }

    return __bot_procman_command2_t_hash;
}

int __bot_procman_command2_t_encode_array(void *buf, int offset, int maxlen, const bot_procman_command2_t *p, int elements)
{
    int pos = 0, thislen, element;

    for (element = 0; element < elements; element++) {

        thislen = __string_encode_array(buf, offset + pos, maxlen - pos, &(p[element].exec_str), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __string_encode_array(buf, offset + pos, maxlen - pos, &(p[element].command_name), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __string_encode_array(buf, offset + pos, maxlen - pos, &(p[element].group), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __boolean_encode_array(buf, offset + pos, maxlen - pos, &(p[element].auto_respawn), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __int8_t_encode_array(buf, offset + pos, maxlen - pos, &(p[element].stop_signal), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __float_encode_array(buf, offset + pos, maxlen - pos, &(p[element].stop_time_allowed), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __int32_t_encode_array(buf, offset + pos, maxlen - pos, &(p[element].num_options), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __string_encode_array(buf, offset + pos, maxlen - pos, p[element].option_names, p[element].num_options);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __string_encode_array(buf, offset + pos, maxlen - pos, p[element].option_values, p[element].num_options);
        if (thislen < 0) return thislen; else pos += thislen;

    }
    return pos;
}

int bot_procman_command2_t_encode(void *buf, int offset, int maxlen, const bot_procman_command2_t *p)
{
    int pos = 0, thislen;
    int64_t hash = __bot_procman_command2_t_get_hash();

    thislen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, &hash, 1);
    if (thislen < 0) return thislen; else pos += thislen;

    thislen = __bot_procman_command2_t_encode_array(buf, offset + pos, maxlen - pos, p, 1);
    if (thislen < 0) return thislen; else pos += thislen;

    return pos;
}

int __bot_procman_command2_t_encoded_array_size(const bot_procman_command2_t *p, int elements)
{
    int size = 0, element;
    for (element = 0; element < elements; element++) {

        size += __string_encoded_array_size(&(p[element].exec_str), 1);

        size += __string_encoded_array_size(&(p[element].command_name), 1);

        size += __string_encoded_array_size(&(p[element].group), 1);

        size += __boolean_encoded_array_size(&(p[element].auto_respawn), 1);

        size += __int8_t_encoded_array_size(&(p[element].stop_signal), 1);

        size += __float_encoded_array_size(&(p[element].stop_time_allowed), 1);

        size += __int32_t_encoded_array_size(&(p[element].num_options), 1);

        size += __string_encoded_array_size(p[element].option_names, p[element].num_options);

        size += __string_encoded_array_size(p[element].option_values, p[element].num_options);

    }
    return size;
}

int bot_procman_command2_t_encoded_size(const bot_procman_command2_t *p)
{
    return 8 + __bot_procman_command2_t_encoded_array_size(p, 1);
}

int __bot_procman_command2_t_decode_array(const void *buf, int offset, int maxlen, bot_procman_command2_t *p, int elements)
{
    int pos = 0, thislen, element;

    for (element = 0; element < elements; element++) {

        thislen = __string_decode_array(buf, offset + pos, maxlen - pos, &(p[element].exec_str), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __string_decode_array(buf, offset + pos, maxlen - pos, &(p[element].command_name), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __string_decode_array(buf, offset + pos, maxlen - pos, &(p[element].group), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __boolean_decode_array(buf, offset + pos, maxlen - pos, &(p[element].auto_respawn), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __int8_t_decode_array(buf, offset + pos, maxlen - pos, &(p[element].stop_signal), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __float_decode_array(buf, offset + pos, maxlen - pos, &(p[element].stop_time_allowed), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &(p[element].num_options), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        p[element].option_names = (char**) lcm_malloc(sizeof(char*) * p[element].num_options);
        thislen = __string_decode_array(buf, offset + pos, maxlen - pos, p[element].option_names, p[element].num_options);
        if (thislen < 0) return thislen; else pos += thislen;

        p[element].option_values = (char**) lcm_malloc(sizeof(char*) * p[element].num_options);
        thislen = __string_decode_array(buf, offset + pos, maxlen - pos, p[element].option_values, p[element].num_options);
        if (thislen < 0) return thislen; else pos += thislen;

    }
    return pos;
}

int __bot_procman_command2_t_decode_array_cleanup(bot_procman_command2_t *p, int elements)
{
    int element;
    for (element = 0; element < elements; element++) {

        __string_decode_array_cleanup(&(p[element].exec_str), 1);

        __string_decode_array_cleanup(&(p[element].command_name), 1);

        __string_decode_array_cleanup(&(p[element].group), 1);

        __boolean_decode_array_cleanup(&(p[element].auto_respawn), 1);

        __int8_t_decode_array_cleanup(&(p[element].stop_signal), 1);

        __float_decode_array_cleanup(&(p[element].stop_time_allowed), 1);

        __int32_t_decode_array_cleanup(&(p[element].num_options), 1);

        __string_decode_array_cleanup(p[element].option_names, p[element].num_options);
        if (p[element].option_names) free(p[element].option_names);

        __string_decode_array_cleanup(p[element].option_values, p[element].num_options);
        if (p[element].option_values) free(p[element].option_values);

    }
    return 0;
}

int bot_procman_command2_t_decode(const void *buf, int offset, int maxlen, bot_procman_command2_t *p)
{
    int pos = 0, thislen;
    int64_t hash = __bot_procman_command2_t_get_hash();

    int64_t this_hash;
    thislen = __int64_t_decode_array(buf, offset + pos, maxlen - pos, &this_hash, 1);
    if (thislen < 0) return thislen; else pos += thislen;
    if (this_hash != hash) return -1;

    thislen = __bot_procman_command2_t_decode_array(buf, offset + pos, maxlen - pos, p, 1);
    if (thislen < 0) return thislen; else pos += thislen;

    return pos;
}

int bot_procman_command2_t_decode_cleanup(bot_procman_command2_t *p)
{
    return __bot_procman_command2_t_decode_array_cleanup(p, 1);
}

int __bot_procman_command2_t_clone_array(const bot_procman_command2_t *p, bot_procman_command2_t *q, int elements)
{
    int element;
    for (element = 0; element < elements; element++) {

        __string_clone_array(&(p[element].exec_str), &(q[element].exec_str), 1);

        __string_clone_array(&(p[element].command_name), &(q[element].command_name), 1);

        __string_clone_array(&(p[element].group), &(q[element].group), 1);

        __boolean_clone_array(&(p[element].auto_respawn), &(q[element].auto_respawn), 1);

        __int8_t_clone_array(&(p[element].stop_signal), &(q[element].stop_signal), 1);

        __float_clone_array(&(p[element].stop_time_allowed), &(q[element].stop_time_allowed), 1);

        __int32_t_clone_array(&(p[element].num_options), &(q[element].num_options), 1);

        q[element].option_names = (char**) lcm_malloc(sizeof(char*) * q[element].num_options);
        __string_clone_array(p[element].option_names, q[element].option_names, p[element].num_options);

        q[element].option_values = (char**) lcm_malloc(sizeof(char*) * q[element].num_options);
        __string_clone_array(p[element].option_values, q[element].option_values, p[element].num_options);

    }
    return 0;
}

bot_procman_command2_t *bot_procman_command2_t_copy(const bot_procman_command2_t *p)
{
    bot_procman_command2_t *q = (bot_procman_command2_t*) malloc(sizeof(bot_procman_command2_t));
    __bot_procman_command2_t_clone_array(p, q, 1);
    return q;
}

void bot_procman_command2_t_destroy(bot_procman_command2_t *p)
{
    __bot_procman_command2_t_decode_array_cleanup(p, 1);
    free(p);
}

int bot_procman_command2_t_publish(lcm_t *lc, const char *channel, const bot_procman_command2_t *p)
{
      int max_data_size = bot_procman_command2_t_encoded_size (p);
      uint8_t *buf = (uint8_t*) malloc (max_data_size);
      if (!buf) return -1;
      int data_size = bot_procman_command2_t_encode (buf, 0, max_data_size, p);
      if (data_size < 0) {
          free (buf);
          return data_size;
      }
      int status = lcm_publish (lc, channel, buf, data_size);
      free (buf);
      return status;
}

struct _bot_procman_command2_t_subscription_t {
    bot_procman_command2_t_handler_t user_handler;
    void *userdata;
    lcm_subscription_t *lc_h;
};
static
void bot_procman_command2_t_handler_stub (const lcm_recv_buf_t *rbuf,
                            const char *channel, void *userdata)
{
    int status;
    bot_procman_command2_t p;
    memset(&p, 0, sizeof(bot_procman_command2_t));
    status = bot_procman_command2_t_decode (rbuf->data, 0, rbuf->data_size, &p);
    if (status < 0) {
        fprintf (stderr, "error %d decoding bot_procman_command2_t!!!\n", status);
        return;
    }

    bot_procman_command2_t_subscription_t *h = (bot_procman_command2_t_subscription_t*) userdata;
    h->user_handler (rbuf, channel, &p, h->userdata);

    bot_procman_command2_t_decode_cleanup (&p);
}

bot_procman_command2_t_subscription_t* bot_procman_command2_t_subscribe (lcm_t *lcm,
                    const char *channel,
                    bot_procman_command2_t_handler_t f, void *userdata)
{
    bot_procman_command2_t_subscription_t *n = (bot_procman_command2_t_subscription_t*)
                       malloc(sizeof(bot_procman_command2_t_subscription_t));
    n->user_handler = f;
    n->userdata = userdata;
    n->lc_h = lcm_subscribe (lcm, channel,
                                 bot_procman_command2_t_handler_stub, n);
    if (n->lc_h == NULL) {
        fprintf (stderr,"couldn't reg bot_procman_command2_t LCM handler!\n");
        free (n);
        return NULL;
    }
    return n;
}

int bot_procman_command2_t_subscription_set_queue_capacity (bot_procman_command2_t_subscription_t* subs,
                              int num_messages)
{
    return lcm_subscription_set_queue_capacity (subs->lc_h, num_messages);
}

int bot_procman_command2_t_unsubscribe(lcm_t *lcm, bot_procman_command2_t_subscription_t* hid)
{
    int status = lcm_unsubscribe (lcm, hid->lc_h);
    if (0 != status) {
        fprintf(stderr,
           "couldn't unsubscribe bot_procman_command2_t_handler %p!\n", hid);
        return -1;
    }
    free (hid);
    return 0;
}

