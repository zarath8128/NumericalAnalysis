.text
.globl GetMXCSR
GetMXCSR:
	STMXCSR	(%RDI)
