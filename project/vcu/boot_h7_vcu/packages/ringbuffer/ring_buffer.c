#include <string.h>
#include "ring_buffer.h"

/** Notes:
 *      Just for present.  refuse to write when buffer is full (i.e no overwrite) (maybe it can be configured in the future)
 *  Choices: 
 *      overwrite happend: 
 *          choice 1: when getting read request, still read from the origin start.
 *          choice 2: when getting read request, read from write-index
 */


int8_t rb_is_full(mrb_t *obj)
{
    return ((obj->isn_empty) && (obj->wIdx == obj->rIdx));
}

int8_t rb_is_empty(mrb_t *obj)
{
    return !obj->isn_empty;
}

uint16_t rb_get_payload_size(mrb_t *obj)
{
    unsigned long _wIdx = obj->wIdx;
    unsigned long _rIdx = obj->rIdx;
    int _isn_empty = obj->isn_empty;

    if (_wIdx > _rIdx) {
        return _wIdx - _rIdx;
    }
    else if (_wIdx < _rIdx) {
        return obj->capacity + _wIdx - _rIdx;
    }
    else {
        if (_isn_empty) 
            return obj->capacity;
        else 
            return 0;
    }
}

int8_t rb_push_byte(mrb_t *obj, uint8_t byte)
{
    if (rb_is_full(obj)) {
        return -1;
    }

    obj->buffer[obj->wIdx] = byte;

    obj->wIdx = (obj->wIdx + 1) % obj->capacity;

    obj->isn_empty = 1;

    return 0;
}

int8_t rb_pop_byte(mrb_t *obj, uint8_t *byte)
{
    if (rb_is_empty(obj)) {
        return -1;
    }

    *byte = obj->buffer[obj->rIdx];

    obj->rIdx = (obj->rIdx + 1) % obj->capacity;

    if (obj->rIdx == obj->wIdx) {
        obj->isn_empty = 0;
    }

    return 0;
}

int8_t rb_push_bytes(mrb_t *obj, const void *addr, unsigned long size)
{
    if (size > (obj->capacity - rb_get_payload_size(obj))) {
        return -1;
    }

    uint8_t *idx = (uint8_t *)addr;

    while(size--) {
        rb_push_byte(obj, *idx++);
    }

    return 0;
}

int8_t rb_pop_bytes(mrb_t *obj, void *addr, unsigned long size)
{
    if (size > rb_get_payload_size(obj)) {
        return -1;
    }

    uint8_t *idx = (uint8_t *)addr;

    while(size--) {
        rb_pop_byte(obj, idx++);
    }

    return 0;
}

static void __memcpy(void * dst, const void * src, unsigned long size)
{
    uint8_t * _dst = (uint8_t *)dst;
    uint8_t * _src = (uint8_t *)src;

    while (size--) {
        *_dst++ = *_src++;
    }
}

int8_t rb_push(mrb_t *obj, const void *addr, unsigned long len)
{
    // TODO
    if (len > (obj->capacity - rb_get_payload_size(obj))) {
        return -1;
    }

    unsigned long tail_len;
    unsigned long head_len;
    unsigned long _wIdx;

    uint8_t *data = (uint8_t *)addr;

    tail_len = (obj->wIdx + len) % obj->capacity;
    head_len = len - tail_len;
    _wIdx = obj->wIdx;

    // note: use std library function or do by hand (considering performance it needs to care copying by cpu-data-width and address alignment)
    __memcpy(&obj->buffer[_wIdx], &data[0], head_len);

    if (tail_len > 0) {
        __memcpy(&obj->buffer[0], &data[head_len], tail_len);
        obj->wIdx = tail_len;
    }
    else {
        obj->wIdx = _wIdx + len;
        if (obj->wIdx >= obj->capacity) {
            obj->wIdx = 0;
        }
    }

    // obj->count += len;

    return 0;
}

int8_t rb_pop(mrb_t *obj, void *addr, unsigned long len)
{
    // TODO;
    if (len > rb_get_payload_size(obj)) {
        return -1;
    }

    unsigned long tail_len;
    unsigned long head_len;
    unsigned long _rIdx;

    uint8_t *data = (uint8_t *)addr;

    tail_len = (obj->rIdx + len) % obj->capacity;
    head_len = len - tail_len;
    _rIdx = obj->rIdx;
    
    // note: use std library function or do by hand (considering performance it needs to care copying by cpu-data-width and address alignment)
    __memcpy(&data[0], &obj->buffer[_rIdx], head_len);
    
    if (tail_len > 0) {
        __memcpy(&data[head_len], &obj->buffer[0], tail_len);
        obj->rIdx = tail_len;
    }
    else {
        obj->rIdx = _rIdx + len;
        if (obj->rIdx >= obj->capacity) {
            obj->rIdx = 0;
        }
    }

    // obj->count -= len;

    return 0;
}


// static int _check_buffer(uint8_t *buffer, unsigned long buffer_len)
// {

// }

int8_t rb_reset(mrb_t *obj)
{
    obj->isn_empty = 0;
    obj->wIdx = 0;
    obj->rIdx = 0;

    return 0;
}

int8_t rb_init(mrb_t *obj, uint8_t *buffer, unsigned long buffer_len)
{
    if (buffer == NULL) return -1;

    obj->buffer = buffer;
    obj->capacity = buffer_len;
    obj->isn_empty = 0;
    obj->wIdx = 0;
    obj->rIdx = 0;

    return 0;
}


