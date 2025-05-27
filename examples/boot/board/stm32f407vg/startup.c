/* Interrupt vector table size */
#define IVT_ARRAY_SIZE 48

typedef void (* isr_t)(void);

extern int main(void);
/* Defined in the linker script */
extern unsigned int _stack;
extern unsigned int _idata;
extern unsigned int _data;
extern unsigned int _edata;
extern unsigned int _bss;
extern unsigned int _ebss;

void isr_reset(void);
void isr_hardfault(void);

__attribute((used, section(".ivt")))
static const isr_t ivt[IVT_ARRAY_SIZE] = {
    (isr_t) &_stack,
    isr_reset,
    0, // isr_nmi (non maskable interrupts)
    isr_hardfault,
};

/* Copy from flash to ram the initial values of .data section */
static void load_data_section()
{
    unsigned int *src_p = &_idata;
    unsigned int *dest_p = &_data;

    for (; dest_p < &_edata; dest_p++, src_p++) {
        *dest_p = *src_p;
    }
}

/* Initialize .bss section to 0 */
static void init_bss()
{
    unsigned int *bss_p = &_bss;

    for (; bss_p < &_ebss; bss_p++) {
        *bss_p = 0;
    }
}

void isr_reset(void)
{
    /* Place to add some hardware initialization */
    /* system_init(); */

    load_data_section();
    init_bss();
    main();

    /* If wanted mor rich C runtime we can remove the "-nostartfiles" and replace */
    /* a the main() with a call to _start(). Newlib runtime files include things */
    /* like semi-hosting, profiling and so on. */
    /* _start(); */

    /* We should never reach this point */
    while (1);
}

void isr_hardfault(void)
{
    while (1);
}
