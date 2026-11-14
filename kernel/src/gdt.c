#include "gdt.h"
#include <stdint.h>

struct gdt_entry gdt[7];
struct gdt_ptr gdt_ptr;

extern void gdt_flush(uint64_t gdt_ptr_address);

void encode_gdt_entry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = ((base >> 16) & 0xFF);
    gdt[num].base_high = ((base >> 24) & 0xFF);

    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].limit_high = ((limit >> 16) & 0x0F);

    gdt[num].granularity = ((granularity >> 4) & 0x0F);
    gdt[num].access = access;
}

void encode_gdt_system_entry(int num, uint64_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
    struct gdt_system_entry *entry = (struct gdt_system_entry *)&gdt[num];

    entry->limit_low = (limit & 0xFFFF);
    entry->base_low = (base & 0xFFFF);
    entry->base_middle = ((base >> 16) & 0xFF);
    entry->access = access;
    entry->limit_high = ((limit >> 16) & 0x0F);
    entry->granularity = ((granularity >> 4) & 0x0F);
    entry->base_high = ((base >> 24) & 0xFF);
    entry->base_upper = ((base >> 32) & 0xFFFFFFFF);
    entry->reserved = 0;
}

void init_gdt() {
    gdt_ptr.limit = (sizeof(struct gdt_entry) * 7) - 1;
    gdt_ptr.base = (uint64_t)&gdt;

    encode_gdt_entry(0, 0, 0, 0, 0);
    encode_gdt_entry(1, 0, 0xFFFFF, 0x9A, 0xA0);
    encode_gdt_entry(2, 0, 0xFFFFF, 0x92, 0xC0);
    encode_gdt_entry(3, 0, 0xFFFFF, 0xF2, 0xC0);
    encode_gdt_entry(4, 0, 0xFFFFF, 0xFA, 0xA0);

    gdt_flush((uint64_t)&gdt_ptr);
}
