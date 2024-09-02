#include "streamw.h"


/* virtual */
void CStreamWriter::xft_write_chars(const unsigned char*const pchToWrite, const unsigned int uiCount)
{
    if (m_hStream != nullptr)
    {
        fwrite(pchToWrite, sizeof(unsigned char), uiCount, m_hStream);
    }
}

/* virtual */
std::stringbuf* CStreamWriter::xft_get_string_buffer() const
{
    return nullptr;
}
