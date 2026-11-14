#include "tss.h"
#include "gdt.h"

static struct tss_entry tss;

void init_tss(uint64_t rsp0) {
    uint8_t *ptr = (uint8_t *)&tss;
    for (uint32_t i = 0; i < sizeof(struct tss_entry); i++) {
        ptr[i] = 0;
    }

    tss.rsp0 = rsp0;
    tss.iomap_base = sizeof(struct tss_entry);

    encode_gdt_system_entry(5, (uint64_t)&tss, sizeof(struct tss_entry) - 1, 0x89, 0x00);

    __asm__ volatile("ltr %%ax" : : "a"((uint16_t)0x28));
}

void set_kernel_stack(uint64_t stack) {
    tss.rsp0 = stack;
}