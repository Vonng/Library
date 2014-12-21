/****************************** Module Header ******************************\
Filename:		Pointer.h
Project:		Vonng
Digest:		    Smart Pointer
Author:			Feng Ruohang
Create:			2014/11/25
LastModify:		2014/11/25
\****************************** Module Header ******************************/

#ifndef V_POINTER
#define V_POINTER

#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

#ifdef _WIN64
#define VONNG_64
#endif

#include "Basic.h"

namespace Vonng
{
	template<typename T>
	class Ptr
	{
		template<typename X>
		friend class Ptr;
	protected:
		vint*				counter;
		T*					reference;

		void Inc()
		{
			if (counter)
			{
				++(*counter);
			}
		}

		void Dec()
		{
			if (counter)
			{
				if (--(*counter) == 0)
				{
					delete counter;
					delete reference;
					counter = 0;
					reference = 0;
				}
			}
		}

		vint* Counter()const
		{
			return counter;
		}

		Ptr(vint* _counter, T* _reference)
			:counter(_counter)
			, reference(_reference)
		{
			Inc();
		}
	public:

		Ptr()
		{
			counter = 0;
			reference = 0;
		}

		Ptr(T* pointer)
		{
			if (pointer)
			{
				counter = new vint(1);
				reference = pointer;
			}
			else
			{
				counter = 0;
				reference = 0;
			}
		}

		Ptr(const Ptr<T>& pointer)
		{
			counter = pointer.counter;
			reference = pointer.reference;
			Inc();
		}

		template<typename C>
		Ptr(const Ptr<C>& pointer)
		{
			T* converted = pointer.Obj();
			if (converted)
			{
				counter = pointer.Counter();
				reference = converted;
				Inc();
			}
			else
			{
				counter = 0;
				reference = 0;
			}
		}

		~Ptr()
		{
			Dec();
		}

		template<typename C>
		Ptr<C> Cast()const
		{
			C* converted = dynamic_cast<C*>(reference);
			return Ptr<C>((converted ? counter : 0), converted);
		}

		Ptr<T>& operator=(T* pointer)
		{
			Dec();
			if (pointer)
			{
				counter = new vint(1);
				reference = pointer;
			}
			else
			{
				counter = 0;
				reference = 0;
			}
			return *this;
		}

		Ptr<T>& operator=(const Ptr<T>& pointer)
		{
			if (this != &pointer)
			{
				Dec();
				counter = pointer.counter;
				reference = pointer.reference;
				Inc();
			}
			return *this;
		}

		template<typename C>
		Ptr<T>& operator=(const Ptr<C>& pointer)
		{
			T* converted = pointer.Obj();
			Dec();
			if (converted)
			{
				counter = pointer.Counter();
				reference = converted;
				Inc();
			}
			else
			{
				counter = 0;
				reference = 0;
			}
			return *this;
		}

		bool operator==(const T* pointer)const
		{
			return reference == pointer;
		}

		bool operator!=(const T* pointer)const
		{
			return reference != pointer;
		}

		bool operator>(const T* pointer)const
		{
			return reference>pointer;
		}

		bool operator>=(const T* pointer)const
		{
			return reference >= pointer;
		}

		bool operator<(const T* pointer)const
		{
			return reference<pointer;
		}

		bool operator<=(const T* pointer)const
		{
			return reference <= pointer;
		}

		bool operator==(const Ptr<T>& pointer)const
		{
			return reference == pointer.reference;
		}

		bool operator!=(const Ptr<T>& pointer)const
		{
			return reference != pointer.reference;
		}

		bool operator>(const Ptr<T>& pointer)const
		{
			return reference>pointer.reference;
		}

		bool operator>=(const Ptr<T>& pointer)const
		{
			return reference >= pointer.reference;
		}

		bool operator<(const Ptr<T>& pointer)const
		{
			return reference<pointer.reference;
		}

		bool operator<=(const Ptr<T>& pointer)const
		{
			return reference <= pointer.reference;
		}

		operator bool()const
		{
			return reference != 0;
		}

		T* Obj()const
		{
			return reference;
		}

		T* operator->()const
		{
			return reference;
		}
	};
}
#endif