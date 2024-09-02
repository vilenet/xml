#ifndef __STREAMW_H_
#define __STREAMW_H_


#include <stdio.h>
#include "format.h"


class CStreamWriter: public CStreamTarget 
{
private:
	FILE* m_hStream;

	CStreamWriter(const CStreamWriter& StreamWriter);
	CStreamWriter& operator = (const CStreamWriter& StreamWriter);

public:

    inline CStreamWriter(FILE* hStream = stdout): m_hStream(hStream) {}

    /* virtual */ void xft_write_chars(const unsigned char*const pchToWrite, const unsigned int uiCount);

    /* virtual */ std::stringbuf* xft_get_string_buffer() const;
};


#endif // __STREAMW_H_
