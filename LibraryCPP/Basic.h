/****************************** Module Header ******************************\
Filename:		V_Type.h
Project:		Vonng
Digest:			Basic data type and useful content definition
Author:			Feng Ruohang
Create:			2014/11/18 23:23
LastModify:		2014/11/18 23:36

Comment:		Reference: Vczh Library++ 2.0
\****************************** Module Header ******************************/

#ifndef _V_BASIC
#define _V_BASIC

#ifdef NDEBUG
#define _V_DISABLE_DEBUG
#endif

#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

#ifdef _WIN64
#define VONNG_64
#endif

namespace Vonng
{
	/* 32/64 Compatible */
#ifdef VONNG_64
	typedef __int64					vint;
	typedef signed __int64			vsint;
	typedef unsigned __int64		vuint;
#else
	typedef __int32					vint;
	typedef signed __int32			vsint;
	typedef unsigned __int32		vuint;
#endif


	//String Relative
#ifdef VONNG_64
#define ITOA_S		_i64toa_s
#define ITOW_S		_i64tow_s
#define I64TOA_S	_i64toa_s
#define I64TOW_S	_i64tow_s
#define UITOA_S		_ui64toa_s
#define UITOW_S		_ui64tow_s
#define UI64TOA_S	_ui64toa_s
#define UI64TOW_S	_ui64tow_s
#else
#define ITOA_S		_itoa_s
#define ITOW_S		_itow_s
#define I64TOA_S	_i64toa_s
#define I64TOW_S	_i64tow_s
#define UITOA_S		_ui64toa_s
#define UITOW_S		_ui64tow_s
#define UI64TOA_S	_ui64toa_s
#define UI64TOW_S	_ui64tow_s
#endif

	//Debug Marcos
#ifdef _DEBUG
#define CHECK_ERROR(CONDITION,DESCRIPTION) do{if(!(CONDITION))throw Error(DESCRIPTION);}while(0)
#endif
#ifdef NDEBUG
#define CHECK_ERROR(CONDITION,DESCRIPTION)
#endif

#define CHECK_FAIL(DESCRIPTION) do{throw Error(DESCRIPTION);}while(0)


	//Nickname
	typedef unsigned	__int8		vuint8;
	typedef signed		__int8		vint8;
	typedef unsigned	__int16		vuint16;
	typedef signed		__int16		vint16;
	typedef unsigned	__int32		vuint32;
	typedef signed		__int32		vint32;
	typedef unsigned	__int64		vuint64;
	typedef signed		__int64		vint64;
	
	typedef unsigned char			vbyte;
	typedef vbyte*					vbuffer;
	typedef const char*             cstr;
	typedef wchar_t					wchar;
	typedef const wchar_t*			wcstr;

	typedef signed __int64			pos_t;

	typedef __int64					vsize;

	typedef double					vdouble;
	typedef bool					boolean;


	//Common Struct
	template<typename T>
	struct Interval
	{
		T lo;
		T hi;

		Interval(T low, T high) :lo(low), hi(high){};
		T length()
		{
			return hi - lo;
		}
	};

	template<typename T, size_t minSize>
	union BinaryRetriver
	{
		T t;
		char binary[sizeof(T)>minSize ? sizeof(T) : minSize];
	};


	//Universal Base
	class Object
	{
	public:
		virtual ~Object();
	};

	class Error
	{
	private:
		wchar_t*			description;
	public:
		Error(wchar_t* _description);

		wchar_t*			Description()const;
	};


	//Interface
	class NotCopyable
	{
	private:
		NotCopyable(const NotCopyable&);
		NotCopyable& operator=(const NotCopyable&);
	public:
		NotCopyable();
	};



	class Interface : private NotCopyable
	{
	public:
		virtual ~Interface();
	};

	struct DateTime
	{
		vint				year;
		vint				month;
		vint				dayOfWeek;
		vint				day;
		vint				hour;
		vint				minute;
		vint				second;
		vint				milliseconds;

		unsigned __int64	totalMilliseconds;
		unsigned __int64	filetime;

		static DateTime		LocalTime();
		static DateTime		UtcTime();

		DateTime			ToLocalTime();
		DateTime			ToUtcTime();
	};



}
#endif