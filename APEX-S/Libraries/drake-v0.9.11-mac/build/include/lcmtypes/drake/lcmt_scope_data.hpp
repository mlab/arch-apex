/** THIS IS AN AUTOMATICALLY GENERATED FILE.  DO NOT MODIFY
 * BY HAND!!
 *
 * Generated by lcm-gen
 **/

#include <lcm/lcm_coretypes.h>

#ifndef __drake_lcmt_scope_data_hpp__
#define __drake_lcmt_scope_data_hpp__

#include <string>

namespace drake
{

class lcmt_scope_data
{
    public:
        int64_t    scope_id;
        int32_t    num_points;
        std::string linespec;
        int8_t     resetOnXval;
        double     xdata;
        double     ydata;

    public:
        inline int encode(void *buf, int offset, int maxlen) const;
        inline int getEncodedSize() const;
        inline int decode(const void *buf, int offset, int maxlen);
        inline static int64_t getHash();
        inline static const char* getTypeName();

        // LCM support functions. Users should not call these
        inline int _encodeNoHash(void *buf, int offset, int maxlen) const;
        inline int _getEncodedSizeNoHash() const;
        inline int _decodeNoHash(const void *buf, int offset, int maxlen);
        inline static int64_t _computeHash(const __lcm_hash_ptr *p);
};

int lcmt_scope_data::encode(void *buf, int offset, int maxlen) const
{
    int pos = 0, tlen;
    int64_t hash = getHash();

    tlen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, &hash, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = this->_encodeNoHash(buf, offset + pos, maxlen - pos);
    if (tlen < 0) return tlen; else pos += tlen;

    return pos;
}

int lcmt_scope_data::decode(const void *buf, int offset, int maxlen)
{
    int pos = 0, thislen;

    int64_t msg_hash;
    thislen = __int64_t_decode_array(buf, offset + pos, maxlen - pos, &msg_hash, 1);
    if (thislen < 0) return thislen; else pos += thislen;
    if (msg_hash != getHash()) return -1;

    thislen = this->_decodeNoHash(buf, offset + pos, maxlen - pos);
    if (thislen < 0) return thislen; else pos += thislen;

    return pos;
}

int lcmt_scope_data::getEncodedSize() const
{
    return 8 + _getEncodedSizeNoHash();
}

int64_t lcmt_scope_data::getHash()
{
    static int64_t hash = _computeHash(NULL);
    return hash;
}

const char* lcmt_scope_data::getTypeName()
{
    return "lcmt_scope_data";
}

int lcmt_scope_data::_encodeNoHash(void *buf, int offset, int maxlen) const
{
    int pos = 0, tlen;

    tlen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, &this->scope_id, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int32_t_encode_array(buf, offset + pos, maxlen - pos, &this->num_points, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    char* linespec_cstr = (char*) this->linespec.c_str();
    tlen = __string_encode_array(buf, offset + pos, maxlen - pos, &linespec_cstr, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __boolean_encode_array(buf, offset + pos, maxlen - pos, &this->resetOnXval, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __double_encode_array(buf, offset + pos, maxlen - pos, &this->xdata, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __double_encode_array(buf, offset + pos, maxlen - pos, &this->ydata, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    return pos;
}

int lcmt_scope_data::_decodeNoHash(const void *buf, int offset, int maxlen)
{
    int pos = 0, tlen;

    tlen = __int64_t_decode_array(buf, offset + pos, maxlen - pos, &this->scope_id, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &this->num_points, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    int32_t __linespec_len__;
    tlen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &__linespec_len__, 1);
    if(tlen < 0) return tlen; else pos += tlen;
    if(__linespec_len__ > maxlen - pos) return -1;
    this->linespec.assign(((const char*)buf) + offset + pos, __linespec_len__ - 1);
    pos += __linespec_len__;

    tlen = __boolean_decode_array(buf, offset + pos, maxlen - pos, &this->resetOnXval, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __double_decode_array(buf, offset + pos, maxlen - pos, &this->xdata, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __double_decode_array(buf, offset + pos, maxlen - pos, &this->ydata, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    return pos;
}

int lcmt_scope_data::_getEncodedSizeNoHash() const
{
    int enc_size = 0;
    enc_size += __int64_t_encoded_array_size(NULL, 1);
    enc_size += __int32_t_encoded_array_size(NULL, 1);
    enc_size += this->linespec.size() + 4 + 1;
    enc_size += __boolean_encoded_array_size(NULL, 1);
    enc_size += __double_encoded_array_size(NULL, 1);
    enc_size += __double_encoded_array_size(NULL, 1);
    return enc_size;
}

int64_t lcmt_scope_data::_computeHash(const __lcm_hash_ptr *)
{
    int64_t hash = 0xce3bf247025afc2fLL;
    return (hash<<1) + ((hash>>63)&1);
}

}

#endif
