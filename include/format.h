#ifndef _FORMAT_H_
#define _FORMAT_H_

#include <string>
#include <ostream>
#include <iostream>

#define XML_strEncoding "UTF-8"

class CStreamTarget;


class CFormatter {
public:
    enum EscapingFlags {
        NoEscapes,
        StdEscapes,
        AttrEscapes,
        UnRep_CharRef
    };

    CFormatter(const std::string& strEncoding, CStreamTarget* target, int indent, EscapingFlags escapeFlags, EscapingFlags unRepFlags, bool writeBOM);
    CFormatter& operator<<(const std::string& str);
    CFormatter& operator<<(EscapingFlags flag);

private:
    CStreamTarget* m_StreamTarget;     
    EscapingFlags  m_escapeFlags;
    EscapingFlags  m_unRepFlags;
    std::string    m_strEncoding;
    bool           m_bWriteBOM;
    int            m_iIndent;
};


class CStreamTarget {
public:

    explicit CStreamTarget(std::ostream& stream = std::cout);
    explicit CStreamTarget(FILE* fileStream);

    CStreamTarget& operator<<(const std::string& str);

    // Method for forcing buffered data to be written
    void xft_flush();

private:
    std::ostream* m_stream;
    FILE*         m_fileStream;
    bool          m_bIsStdStream;
};

#endif // _FORMAT_H_
