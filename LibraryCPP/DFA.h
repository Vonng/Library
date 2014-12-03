/****************************** Module Header ******************************\
Filename:		StateMachine.h
Project:		Vonng
Digest:		    StateMachine:
Author:			Feng Ruohang
Create:			2014/12/03
LastModify:		2014/12/03
\****************************** Module Header ******************************/
#ifndef _V_DFA
#define _V_DFA

#ifdef NDEBUG
#define __V_DISABLE_ALL_DEBUG_MARCO__
#endif

#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

#include "Basic.h"


namespace Vonng
{
	class StateMachine
	{
	public:
		StateMachine()
		{
		}


	private:
		int state;



	};
}
#endif