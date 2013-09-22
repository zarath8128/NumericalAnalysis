.text
.globl pow
#	double pow(double base, double exp)
pow:
	MOVDQ2Q	%XMM0	,	%MM0
	MOVDQ2Q	%XMM1	,	%MM1
	EMMS
	FNINIT
	FYL2X
#	FXTRACT
#	FLD1
#	FSUBP
#	F2XM1
#	FLD1
#	FADDP
#	FSCALE
#	FLD1
#	FMULP
	MOVQ2DQ	%MM1	,	%XMM0
	ret
