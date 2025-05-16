#ifndef __MRB_H__
#define __MRB_H__

#include <stdint.h>

typedef struct mrb {
    unsigned long capacity;
    int isn_empty;
    unsigned long wIdx, rIdx;
    uint8_t *buffer;
}mrb_t;

int8_t rb_is_full(mrb_t *obj);
int8_t rb_is_empty(mrb_t *obj);
uint16_t rb_get_payload_size(mrb_t *obj);

int8_t rb_push_byte(mrb_t *obj, uint8_t byte);
int8_t rb_pop_byte(mrb_t *obj, uint8_t *byte);
int8_t rb_push_bytes(mrb_t *obj, const void *addr, unsigned long size);
int8_t rb_pop_bytes(mrb_t *obj, void *addr, unsigned long size);

int8_t rb_push(mrb_t *obj, const void *addr, unsigned long size);
int8_t rb_pop(mrb_t *obj, void *addr, unsigned long size);

int8_t rb_reset(mrb_t *obj);
int8_t rb_init(mrb_t *obj, uint8_t *buffer, unsigned long buffer_len);

#endif // !__MRB_H__

