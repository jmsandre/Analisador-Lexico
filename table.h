/*
Tabela de conversão dos estados baseados em um automato
para um analisador léxico em C
COPYRIGHTS (C) 2022 João Marcos	
license: GPL3*/

#ifndef _CONVERSION_TABLE
#define _CONVERSION_TABLE

const int table[][7] = {
			//		Alfa	NUM		f'.'	OP_S	OP_D		" 		'	
/*			q0*/	1,		2,		3,		0,		4,			5,		6,		
/*id/word	q1*/	1,		1,		0,		0,		0,			-1, 	-1,	
/*0-9		q2*/	-1,		2,		3,		0,		0,			-1,		-1,
/*float		q3*/	-1,		3,		-1,		0,		0,			-1,		-1,
/*op_d		q4*/	0,		0,		-1,		0,		0,			-1,		-1,
/*string	q5*/	5,		5,		5,		5,		5,			0,		5,
/*char	 	q6*/    7, 		7,		7,		7,		7,			7,		0,
/*char v	q7*/	0,		0,		0,		0,		0,			0,		0
};

#endif