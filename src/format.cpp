#include "format.h"
#include <ostream>
#include <iostream>

//
// CFormatter
//
CFormatter::CFormatter(
    const std::string& strEncoding, 
    CStreamTarget* target, 
    int indent, 
    EscapingFlags escapeFlags, 
    EscapingFlags unRepFlags, 
    bool writeBOM)
        : m_strEncoding(strEncoding)
        , m_StreamTarget(target)
        , m_iIndent(indent)
        , m_escapeFlags(escapeFlags)
        , m_unRepFlags(unRepFlags)
        , m_bWriteBOM(writeBOM) 
{
    if (writeBOM) {
        *m_StreamTarget << "\xEF\xBB\xBF"; // UTF-8 BOM
    }
}

CFormatter& CFormatter::operator<<(const std::string& str) {
    if (m_iIndent > 0) {
        *m_StreamTarget << std::string(m_iIndent, ' ');
    }
    *m_StreamTarget << str;
    return *this;
}

CFormatter& CFormatter::operator<<(EscapingFlags flag) {
    m_escapeFlags = flag;
    return *this;
}


//
// CStreamTarget
//
CStreamTarget::CStreamTarget(std::ostream& stream)
    : m_stream(&stream), m_fileStream(nullptr), m_bIsStdStream(true) {}

CStreamTarget::CStreamTarget(FILE* fileStream)
    : m_stream(nullptr), m_fileStream(fileStream), m_bIsStdStream(false) {}

CStreamTarget& CStreamTarget::operator<<(const std::string& str) {
    if (m_bIsStdStream && m_stream) {
        *m_stream << str;
    } else if (m_fileStream) {
        fwrite(str.c_str(), sizeof(char), str.size(), m_fileStream);
    }
    return *this;
}

void CStreamTarget::xft_flush() {
    if (m_bIsStdStream && m_stream) {
        m_stream->flush();
    } else if (m_fileStream) {
        fflush(m_fileStream);
    }
}
