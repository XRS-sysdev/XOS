#include "gdt.h"
#include <stdint.h>

struct gdt_entry gdt[5];
struct gdt_ptr gdt_ptr;

extern void gdt_flush(uint64_t gdt_ptr_address);

void encode_gdt_entry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
        gdt[num].base_low = (base & 0xFFFF);
        gdt[num].base_middle = ((base >> 16) & 0xFF);
        gdt[num].base_high = ((base >> 24) & 0xFF);

        gdt[num].limit_low = (limit & 0xFFFF);
        gdt[num].granularity = ((limit >> 16) & 0x0F);

        gdt[num].granularity |= (granularity & 0xF0);
        gdt[num].access = access;
}

void init_gdt() {
        gdt_ptr.limit = (sizeof(struct gdt_entry) * 5) - 1;
        gdt_ptr.base = (uint64_t)&gdt;

        encode_gdt_entry(0, 0, 0, 0, 0);
        encode_gdt_entry(1, 0, 0, 0x9A, 0x20);
        encode_gdt_entry(2, 0, 0, 0x92, 0x00);
        encode_gdt_entry(3, 0, 0, 0xFA, 0x20);
        encode_gdt_entry(4, 0, 0, 0xF2, 0x00);

        gdt_flush((uint64_t)&gdt_ptr);
}