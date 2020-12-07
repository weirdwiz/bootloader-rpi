.section ".text.boot"

.globl _boot

_boot:
	mrs x5, mpidr_el1
	and x5, x5, #3
	cmp x5, #0

	beq continue

sleep:
	wfi
	b sleep

continue:
	ldr x1, =__bss_start
    ldr     w2, =__bss_size
3:  cbz     w2, 4f
	str     xzr, [x1], #8
	sub     w2, w2, #1
	cbnz    w2, 3b


	ldr x1, _boot
	mov sp, x1

4:
	bl main
