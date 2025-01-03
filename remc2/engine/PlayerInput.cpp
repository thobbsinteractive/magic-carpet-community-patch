#include "PlayerInput.h"

#include "engine_support.h"
#include "Basic.h"

//----- (000191B0) --------------------------------------------------------
void HandleButtonClick_191B0(int16_t a1, char a2)//1fa1b0 //set spell, destroy castle sub_191B0(0x2a, 0x00)
{
	type_event_0x6E8E* v10x; // ebx

	switch (a1)
	{
	case 0:
	case 1:
	case 2:
	case 26:
		goto LABEL_23;
	case 3:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
		return;
	case 4:
		//v4 = &x_D41A0_BYTEARRAY_0[10 * D41A0_BYTESTR_0.word_0xc];
		if (D41A0_0.array_0x6E3E[D41A0_0.LevelIndex_0xc].str_0x6E3E_byte0 != a1 && D41A0_0.array_0x6E3E[D41A0_0.LevelIndex_0xc].str_0x6E3E_byte0)
			return;
		//v5 = (int)x_D41A0_BYTEARRAY_0;
		D41A0_0.array_0x6E3E[D41A0_0.LevelIndex_0xc].str_0x6E3E_byte0 = a1;
		//result = a2;
		D41A0_0.array_0x6E3E[D41A0_0.LevelIndex_0xc].str_0x6E3E_byte1 |= a2;
		//x_D41A0_BYTEARRAY_0 = x_D41A0_BYTEARRAY_0;
		return;
	case 5:
	case 6:
		//v6 = &x_D41A0_BYTEARRAY_0[10 * D41A0_BYTESTR_0.word_0xc];
		if (D41A0_0.array_0x6E3E[D41A0_0.LevelIndex_0xc].str_0x6E3E_byte0 != a1 && D41A0_0.array_0x6E3E[D41A0_0.LevelIndex_0xc].str_0x6E3E_byte0)
			return;
		//v7 = (int)x_D41A0_BYTEARRAY_0;
		D41A0_0.array_0x6E3E[D41A0_0.LevelIndex_0xc].str_0x6E3E_byte0 = a1;
		//result = a2;
		D41A0_0.array_0x6E3E[D41A0_0.LevelIndex_0xc].str_0x6E3E_byte5 |= a2;
		//x_D41A0_BYTEARRAY_0 = v2;
		return;
	case 12:
	case 13:
	case 14:
	case 16:
	case 18:
	case 19:
	case 29:
	case 42:
	case 44:
		//v15 = &x_D41A0_BYTEARRAY_0[10 * D41A0_BYTESTR_0.word_0xc];
		if (D41A0_0.array_0x6E3E[D41A0_0.LevelIndex_0xc].str_0x6E3E_byte0 != a1 && D41A0_0.array_0x6E3E[D41A0_0.LevelIndex_0xc].str_0x6E3E_byte0)
			return;
	LABEL_23:
		D41A0_0.array_0x6E3E[D41A0_0.LevelIndex_0xc].str_0x6E3E_byte0 = a1;
		//x_D41A0_BYTEARRAY_0 = v2;
		return;
	case 15:
		//v8 = &x_D41A0_BYTEARRAY_0[10 * D41A0_BYTESTR_0.word_0xc];
		if (D41A0_0.array_0x6E3E[D41A0_0.LevelIndex_0xc].str_0x6E3E_byte0 != a1 && D41A0_0.array_0x6E3E[D41A0_0.LevelIndex_0xc].str_0x6E3E_byte0)
			return;
		//v9 = D41A0_BYTESTR_0.word_0xc;
		v10x = x_DWORD_EA3E4[D41A0_0.array_0x2BDE[D41A0_0.LevelIndex_0xc].word_0x00a_2BE4_11240];
		if (v10x->life_0x8 >= 0 || v10x->state_0x45_69 != 3)
			return;
		D41A0_0.array_0x6E3E[D41A0_0.LevelIndex_0xc].str_0x6E3E_byte0 = a1;
		//x_D41A0_BYTEARRAY_0 = v2;
		return;
	case 27:
		//v11 = &x_D41A0_BYTEARRAY_0[10 * D41A0_BYTESTR_0.word_0xc];
		if (D41A0_0.array_0x6E3E[D41A0_0.LevelIndex_0xc].str_0x6E3E_byte0 != a1 && D41A0_0.array_0x6E3E[D41A0_0.LevelIndex_0xc].str_0x6E3E_byte0)
			return;
		//v12 = D41A0_BYTESTR_0.word_0xc;
		if (!(D41A0_0.array_0x2BDE[D41A0_0.LevelIndex_0xc].dw_w_b_0_2BDE_11230.byte[2] & 2))
			return;
		D41A0_0.array_0x6E3E[D41A0_0.LevelIndex_0xc].str_0x6E3E_byte0 = a1;
		//x_D41A0_BYTEARRAY_0 = v2;
		return;
	case 28:
		//v13 = &x_D41A0_BYTEARRAY_0[10 * D41A0_BYTESTR_0.word_0xc];
		if (D41A0_0.array_0x6E3E[D41A0_0.LevelIndex_0xc].str_0x6E3E_byte0 != a1 && D41A0_0.array_0x6E3E[D41A0_0.LevelIndex_0xc].str_0x6E3E_byte0)
			return;
		//v14 = D41A0_BYTESTR_0.word_0xc;
		if (!(D41A0_0.array_0x2BDE[D41A0_0.LevelIndex_0xc].dw_w_b_0_2BDE_11230.byte[2] & 4))
			return;
		D41A0_0.array_0x6E3E[D41A0_0.LevelIndex_0xc].str_0x6E3E_byte0 = a1;
		//x_D41A0_BYTEARRAY_0 = v2;
		return;
	case 30:
		if (x_D41A0_BYTEARRAY_4_struct.setting_byte2_23 < 0
			|| (D41A0_0.array_0x2BDE[D41A0_0.LevelIndex_0xc].WizardName_0x39f_2BFA_12157[0] == 99)
			&& D41A0_0.array_0x2BDE[D41A0_0.LevelIndex_0xc].WizardName_0x39f_2BFA_12157[1] == 104
			&& D41A0_0.array_0x2BDE[D41A0_0.LevelIndex_0xc].WizardName_0x39f_2BFA_12157[2] == 114
			&& D41A0_0.array_0x2BDE[D41A0_0.LevelIndex_0xc].WizardName_0x39f_2BFA_12157[3] == 111
			&& D41A0_0.array_0x2BDE[D41A0_0.LevelIndex_0xc].WizardName_0x39f_2BFA_12157[4] == 110
			&& D41A0_0.array_0x2BDE[D41A0_0.LevelIndex_0xc].WizardName_0x39f_2BFA_12157[5] == 105
			&& D41A0_0.array_0x2BDE[D41A0_0.LevelIndex_0xc].WizardName_0x39f_2BFA_12157[6] == 99
			&& D41A0_0.array_0x2BDE[D41A0_0.LevelIndex_0xc].WizardName_0x39f_2BFA_12157[7] == 108
			&& D41A0_0.array_0x2BDE[D41A0_0.LevelIndex_0xc].WizardName_0x39f_2BFA_12157[8] == 101)
		{
			//v17 = &x_D41A0_BYTEARRAY_0[10 * D41A0_BYTESTR_0.word_0xc];
			if (D41A0_0.array_0x6E3E[D41A0_0.LevelIndex_0xc].str_0x6E3E_byte0 == a1 || !D41A0_0.array_0x6E3E[D41A0_0.LevelIndex_0xc].str_0x6E3E_byte0)
				goto LABEL_39;
		}
		return;
	case 39:
		goto LABEL_39;
	default:
		//v18 = &x_D41A0_BYTEARRAY_0[10 * D41A0_BYTESTR_0.word_0xc];
		if (D41A0_0.array_0x6E3E[D41A0_0.LevelIndex_0xc].str_0x6E3E_byte0 == a1 || !D41A0_0.array_0x6E3E[D41A0_0.LevelIndex_0xc].str_0x6E3E_byte0)
		{
		LABEL_39:
			D41A0_0.array_0x6E3E[D41A0_0.LevelIndex_0xc].str_0x6E3E_byte0 = a1;
			//result = a2;
			D41A0_0.array_0x6E3E[D41A0_0.LevelIndex_0xc].str_0x6E3E_byte1 = a2;
		}
		//LABEL_40:
			//x_D41A0_BYTEARRAY_0 = v2;
		return;
	}
}
// D41A0: using guessed type int x_D41A0_BYTEARRAY_0;
// D41A4: using guessed type int x_DWORD_D41A4;
// EA3E4: using guessed type int x_DWORD_EA3E4[];
