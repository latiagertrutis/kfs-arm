MEMORY
{
	flash (rx) : ORIGIN = 0x08000000, LENGTH = 1024K
	sram (rwx) : ORIGIN = 0x20000000, LENGTH = 112K
}

/* End of ram */
_eram = ORIGIN(sram) + LENGTH(sram);
/* Stack starts at the end of the ram */
_stack = _eram;

SECTIONS
{
	.text : ALIGN(4)
	{
		KEEP(*(.ivt)) /* Interrupt vector table */
		*(.text*)
		. = ALIGN(4);
		_etext = .;
	} > flash

	_idata = LOADADDR(.data);

	.data : ALIGN(4)
	{
		_data = .;
		*(.data*)
		. = ALIGN(4);
		_edata = .;
	} > sram AT > flash

	.bss : ALIGN(4)
	{
		_bss = .;
		*(.bss*)
		. = ALIGN(4);
		_ebss = .;
		PROVIDE(_end = .);
	} > sram
}
