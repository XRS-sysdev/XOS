#include "idt.h"

struct idt_entry idt[256];
struct idt_ptr idt_ptr;

extern void isr0();  extern void isr1();  extern void isr2();  extern void isr3();
extern void isr4();  extern void isr5();  extern void isr6();  extern void isr7();
extern void isr8();  extern void isr9();  extern void isr10(); extern void isr11();
extern void isr12(); extern void isr13(); extern void isr14(); extern void isr15();
extern void isr16(); extern void isr17(); extern void isr18(); extern void isr19();
extern void isr20(); extern void isr21(); extern void isr22(); extern void isr23();
extern void isr24(); extern void isr25(); extern void isr26(); extern void isr27();
extern void isr28(); extern void isr29(); extern void isr30(); extern void isr31();

void set_idt_gate(int num, uint64_t handler, uint8_t ist, uint8_t flags) {
    idt[num].offset_low  = handler & 0xFFFF;
    idt[num].selector    = 0x08; // Kernel Code Segment in your GDT
    idt[num].ist         = ist;
    idt[num].attributes  = flags;
    idt[num].offset_mid  = (handler >> 16) & 0xFFFF;
    idt[num].offset_high = (handler >> 32) & 0xFFFFFFFF;
    idt[num].reserved    = 0;
}

void init_idt() {
    idt_ptr.limit = (sizeof(struct idt_entry) * 256) - 1;
    idt_ptr.base  = (uint64_t)&idt;

    uint8_t *ptr = (uint8_t *)&idt;
    for (uint32_t i = 0; i < sizeof(idt); i++) {
        ptr[i] = 0;
    }

    set_idt_gate(0,  (uint64_t)isr0,  0, 0x8E);
    set_idt_gate(1,  (uint64_t)isr1,  0, 0x8E);
    set_idt_gate(2,  (uint64_t)isr2,  0, 0x8E);
    set_idt_gate(3,  (uint64_t)isr3,  0, 0x8E);
    set_idt_gate(4,  (uint64_t)isr4,  0, 0x8E);
    set_idt_gate(5,  (uint64_t)isr5,  0, 0x8E);
    set_idt_gate(6,  (uint64_t)isr6,  0, 0x8E);
    set_idt_gate(7,  (uint64_t)isr7,  0, 0x8E);
    set_idt_gate(8,  (uint64_t)isr8,  0, 0x8E);
    set_idt_gate(9,  (uint64_t)isr9,  0, 0x8E);
    set_idt_gate(10, (uint64_t)isr10, 0, 0x8E);
    set_idt_gate(11, (uint64_t)isr11, 0, 0x8E);
    set_idt_gate(12, (uint64_t)isr12, 0, 0x8E);
    set_idt_gate(13, (uint64_t)isr13, 0, 0x8E);
    set_idt_gate(14, (uint64_t)isr14, 0, 0x8E);
    set_idt_gate(15, (uint64_t)isr15, 0, 0x8E);
    set_idt_gate(16, (uint64_t)isr16, 0, 0x8E);
    set_idt_gate(17, (uint64_t)isr17, 0, 0x8E);
    set_idt_gate(18, (uint64_t)isr18, 0, 0x8E);
    set_idt_gate(19, (uint64_t)isr19, 0, 0x8E);
    set_idt_gate(20, (uint64_t)isr20, 0, 0x8E);
    set_idt_gate(21, (uint64_t)isr21, 0, 0x8E);
    set_idt_gate(22, (uint64_t)isr22, 0, 0x8E);
    set_idt_gate(23, (uint64_t)isr23, 0, 0x8E);
    set_idt_gate(24, (uint64_t)isr24, 0, 0x8E);
    set_idt_gate(25, (uint64_t)isr25, 0, 0x8E);
    set_idt_gate(26, (uint64_t)isr26, 0, 0x8E);
    set_idt_gate(27, (uint64_t)isr27, 0, 0x8E);
    set_idt_gate(28, (uint64_t)isr28, 0, 0x8E);
    set_idt_gate(29, (uint64_t)isr29, 0, 0x8E);
    set_idt_gate(30, (uint64_t)isr30, 0, 0x8E);
    set_idt_gate(31, (uint64_t)isr31, 0, 0x8E);

    __asm__ volatile("lidt %0" : : "m"(idt_ptr));
}

void isr_handler(struct registers *regs) {
    for (;;) {
        __asm__ volatile("cli; hlt");
    }
}