.section ".text.boot"

.globl _boot

_boot:
	mrc x5, mpidr_el1
	and x5, x5, #3 // remove the upper bits from x5
	cmp x5. #0

	beq continue

sleep:
	wfi
	b sleep

continue:
	ldr x1, __bss_start__ // the __bss_start__ is defined by linker
	ldr x2, __bss_end__
	ldr x3, #0
	str x3, [x1], #8

	ldr x1, _boot
	mov sp, x1

	bl main // branch to main label, defined by the linker
