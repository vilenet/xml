#ifndef __WRITEOBJ_H_
#define __WRITEOBJ_H_

#include "writer.h"
#include "streamw.h"

inline void WriteObject(const СWritableObj& WritableObj, FILE* hStream = stdout)
{
	CStreamWriter StreamWriter(hStream); СWriter(StreamWriter) << WritableObj;
}

extern bool WriteObject(const СWritableObj& WritableObj, const char* szFileName, const char* szOpenFileMode = "wb");

extern bool WriteObject(const СWritableObj2& WritableObj, const char *szFileName, const char* szOpenFileMode = "wb");


#endif // __WRITEOBJ_H_
