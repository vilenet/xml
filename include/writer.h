#ifndef __WRITER_H_
#define __WRITER_H_

#include "format.h"
#include <vector>
#include <memory>

using namespace std;


class СWriter;


class СWritableObj2 {
public:
    virtual ~СWritableObj2();
    virtual void WriteXML(СWriter &Writer, bool bMakePatternsServerCompliantInWildcards) const = 0;
};


class СWritableObj {
private: 
    bool m_bWriteContentOnly;

public:
    СWritableObj(): m_bWriteContentOnly(false) {}

    bool GetWriteContentOnly() const {return m_bWriteContentOnly;}
    void SetWriteContentOnly(bool Value) {m_bWriteContentOnly = Value;}

    virtual ~СWritableObj();
    virtual void WriteXML(СWriter& Writer) const = 0;
};


class CTag {
private:
    const std::string& m_strTagName;
    const std::string& m_strTagValue;

public:
    inline CTag(const std::string& strTagName, const std::string& strTagValueAsIs = ""): m_strTagName(strTagName), m_strTagValue(strTagValueAsIs) {}
    inline const std::string& GetTagName () const {return m_strTagName;}
    inline const std::string& GetTagValue() const {return m_strTagValue;}
};


class COpenTag {
private:    
	const std::string& m_strTagName;

public:
	inline COpenTag(const std::string& strTagName): m_strTagName(strTagName) {}
	inline const std::string& GetTagName() const {return m_strTagName;}
};


class CTagValue {
private:
	const std::string& m_strTagValue;

public:
	inline CTagValue(const std::string& strTagValue): m_strTagValue(strTagValue) {}
	inline const std::string& GetTagValue() const {return m_strTagValue;}
};


class COpenTagWithAttributes {
private:
	const std::string& m_strTagName;

public:
    inline COpenTagWithAttributes(const std::string& strTagName): m_strTagName(strTagName) {}
    inline const std::string& GetTagName() const {return m_strTagName;}
};


class CAttribute {
private:
	const std::string& m_strAttrName ;
	const std::string& m_strAttrValue;

public:
    inline CAttribute(const std::string& strAttrName, const std::string& strAttrValue): m_strAttrName(strAttrName), m_strAttrValue(strAttrValue) {}
    inline const std::string& GetAttrName () const {return m_strAttrName ;}
    inline const std::string& GetAttrValue() const {return m_strAttrValue;}
};


class CCloseAttributes {};
class CCloseTag {};


class CObjectContent {
private:
    const СWritableObj& m_WritableObj;

public:
    CObjectContent(const СWritableObj& WritableObj): m_WritableObj(WritableObj) {}
    const СWritableObj& GetWritableObj() const {return m_WritableObj;}
};


class СTagState {
private:
	std::string  m_strTagName;
	bool         m_bAttributesOpened;
	СTagState*   m_pPrevious;

public:

    inline СTagState(const std::string& strTagName = "", bool bAttributesOpened = false, СTagState* pPrevious = nullptr):
        m_strTagName(strTagName), m_bAttributesOpened(bAttributesOpened), m_pPrevious(pPrevious)
    {}

    inline const std::string& GetTagName() const {return m_strTagName;}
    inline bool AttributesOpened() const {return m_bAttributesOpened;}
    inline void SetOpenedForAttributes(bool bAttributesOpened) {m_bAttributesOpened = bAttributesOpened;}

    inline void ReturnToPrevious() {
        if(m_pPrevious != nullptr) {
            СTagState* pPrevious = m_pPrevious;
            *this = *m_pPrevious;
            delete pPrevious;
        }
    }

    void DeleteAll();
};


class СWriter {
private:
	CStreamTarget& m_StreamTarget;
	CFormatter     m_Formatter;
	СTagState      m_State;

	СWriter();
	СWriter(const СWriter& Writer);
	СWriter& operator = (const СWriter& Writer);

public:
    СWriter(CStreamTarget& StreamTarget);
    ~СWriter();

	СWriter& operator << (const СWritableObj& WritableObj);
    СWriter& operator << (const CObjectContent    & ObjectContent    );

	СWriter& operator << (const CTag                  & Tag                  );
	СWriter& operator << (const COpenTag              & OpenTag              );
	СWriter& operator << (const CTagValue             & TagValue             );
	СWriter& operator << (const COpenTagWithAttributes& OpenTagWithAttributes);
	СWriter& operator << (const CAttribute            & Attribute            );
	СWriter& operator << (const CCloseAttributes      & CloseAttributes      );
	СWriter& operator << (const CCloseTag             & CloseTag             );
};


#endif // __WRITER_H_
