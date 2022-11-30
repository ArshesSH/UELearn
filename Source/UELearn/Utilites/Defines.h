#pragma once

// Null Check
#define CheckNull(p) {if (p == NULL) return;}
#define CheckNullResult(p, result) {if (p == NULL) return result;}

// True
#define CheckTrue(p) {if (p == true) return;}
#define CheckTrueResult(p, result) {if (p == true) return result;}

// False
#define CheckFalse(p) {if (p == false) return;}
#define CheckFalseResult(p, result) {if (p == false) return result;}

//class Defines
//{
//public:
//	template <typename T>
//	static bool CheckNull<T>( const T& p )
//	{
//		return p == NULL;
//	}
//};