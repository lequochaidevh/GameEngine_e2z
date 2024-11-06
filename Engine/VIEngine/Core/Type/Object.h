#pragma once

#include"RTTI.h"
#include"pch.h"

namespace VIEngine {
	class VI_API Object {
	public:
		DECLARE_RTTI
	public:
		VI_FORCE_INLINE bool isTypeOf(const RTTI& other) const { return getRunTimeTypeInfo().isTypeOf(other); }
		VI_FORCE_INLINE bool isDerivedFrom(const RTTI& other) const { return getRunTimeTypeInfo().isDerivedFrom(other); }

		/*Know exacly Type of pointer destination*/
		VI_FORCE_INLINE bool isExactlyTypeOf(const Object* obj) const { return obj && getRunTimeTypeInfo().isTypeOf(obj->getRunTimeTypeInfo()); }
		VI_FORCE_INLINE bool isExactlyDerivedFrom(const Object* obj) const { return obj && getRunTimeTypeInfo().isDerivedFrom(obj->getRunTimeTypeInfo()); }
	};

	class VI_API Actor : public Object {
	public:
		DECLARE_RTTI
	};

	DEFINE_RTTI_NO_PARENT(Object)
	DEFINE_RTTI(Actor, &Object::runTimeType)
}