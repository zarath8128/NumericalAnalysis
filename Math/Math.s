.text
.globl pow
#	double pow(double base, double exp)
pow:
	FNINIT
	MOVDQ2Q	%XMM0	,	%MM0
	MOVDQ2Q	%XMM1	,	%MM1
	EMMS
#	FYL2X
#	FXTRACT
	FLD1
#	FSUBP
#	F2XM1
#	FLD1
#	FADDP
#	FSCALE
#	FLD1
#	FMULP
	MOVQ2DQ	%MM0	,	%XMM0
	ret
