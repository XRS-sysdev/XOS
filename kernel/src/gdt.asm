bits 64
global gdt_flush
                   
gdt_flush:        
        lgdt [rdi]        

        mov ax, 0x10
        mov ds, ax
        mov es, ax                                                                                                                                                  
        mov fs, ax                                                                                                                                                  
        mov gs, ax         
        mov ss, ax                                                                                                                                                  

        mov rax, rsp    
        push 0x10       
        push rax        
        pushfq          
        push 0x08       
        lea rax, [rel .reload_cs]
        push rax        
        iretq           

.reload_cs:
        ret