/* Interrupt vector table size */
#define IVT_ARRAY_SIZE 48

typedef void (* isr_t)(void);

extern int main(void);
/* Defined in the linker script */
extern unsigned int _stack;

void isr_reset(void);
void isr_hardfault(void);

__attribute((used, section(".ivt")))
static const isr_t ivt[IVT_ARRAY_SIZE] = {
    (isr_t) &_stack,
    isr_reset,
    0, // isr_nmi (non maskable interrupts)
    isr_hardfault,
};

void isr_reset(void)
{
    main();

    while (1);
}

void isr_hardfault(void)
{
    while (1);
}
