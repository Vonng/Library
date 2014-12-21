/***********************************************************************
Vczh Library++ 3.0
Developer: ³Âè÷å«(vczh)
UI::Console
***********************************************************************/


#ifndef V_CONSOLE
#define V_CONSOLE

#include "String.h"

namespace Vonng
{
	class Console abstract
	{
	public:
		static void Write(const WString& string);
		static void WriteLine(const WString& string);
		static WString Read();
		static void SetColor(bool red, bool green, bool blue, bool light);
		static void SetTitle(const WString& string);
	};
}

#endif