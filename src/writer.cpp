#include "writer.h"

//
// СWritableObj2
//

СWritableObj2::~СWritableObj2()
{}

//
// СWritableObj
//

СWritableObj::~СWritableObj()
{}

//
// СTagState
//

void СTagState::DeleteAll()
{
	СTagState* pPrevious;

	for(СTagState* pCurrent = m_pPrevious; pCurrent != nullptr; pCurrent = pPrevious)
	{
		pPrevious = pCurrent->m_pPrevious;

		delete pCurrent;
	}

	m_strTagName.clear();
	m_bAttributesOpened = false;
	m_pPrevious = nullptr;
}


//
// СWriter
//

СWriter::СWriter(CStreamTarget& StreamTarget)
	: m_StreamTarget(StreamTarget)
	, m_Formatter(
		XML_strEncoding, 
		&StreamTarget, 4, 
		CFormatter::NoEscapes, 
		CFormatter::UnRep_CharRef, /* Write BOM = */ false)
{
	m_Formatter << ((std::string)"<?xml version=\"1.0\" strEncoding=\"" + XML_strEncoding + "\" standalone=\"yes\"?>");
}


СWriter::~СWriter()
{
	m_StreamTarget.xft_flush();
	m_State.DeleteAll();
}


СWriter& СWriter::operator << (const СWritableObj& WritableObj)
{
    ((СWritableObj&)WritableObj).SetWriteContentOnly(false);
    WritableObj.WriteXML(*this);
    return *this;
}


СWriter& СWriter::operator << (const CObjectContent& ObjectContent)
{
    СWritableObj& WritableObj = (СWritableObj&)ObjectContent.GetWritableObj();
    WritableObj.SetWriteContentOnly(true);
    WritableObj.WriteXML(*this);
    return *this;
}


СWriter& СWriter::operator << (const CTag& Tag)
{
	if(Tag.GetTagValue().empty())
	{
		m_Formatter << ("<" + Tag.GetTagName() + "/>");
	}
	else
	{
		m_Formatter << ("<" + Tag.GetTagName() + ">")
							<< CFormatter::StdEscapes << Tag.GetTagValue() << CFormatter::NoEscapes
					   << ("</" + Tag.GetTagName() + ">");
	}

	return *this;
}


СWriter& СWriter::operator << (const COpenTag& OpenTag)
{
	m_Formatter << ("<" + OpenTag.GetTagName() + ">");
	m_State = СTagState(OpenTag.GetTagName(), /* bAttributesOpened = */ false, /* pPrevious = */ new СTagState(m_State));
	return *this;
}


СWriter& СWriter::operator << (const CTagValue& TagValue)
{
	m_Formatter << CFormatter::StdEscapes << TagValue.GetTagValue() << CFormatter::NoEscapes;
	return *this;
}


СWriter& СWriter::operator << (const COpenTagWithAttributes& OpenTagWithAttributes)
{
	m_Formatter << ("<" + OpenTagWithAttributes.GetTagName());
	m_State = СTagState(OpenTagWithAttributes.GetTagName(), /* bAttributesOpened = */ true, /* pPrevious = */ new СTagState(m_State));
	return *this;
}


СWriter& СWriter::operator << (const CAttribute& Attribute)
{
	m_Formatter << (" " + Attribute.GetAttrName() + "=\"") << CFormatter::AttrEscapes << Attribute.GetAttrValue() << CFormatter::NoEscapes << "\"";
	return *this;
}


СWriter& СWriter::operator << (const CCloseAttributes& CloseAttributes)
{
	m_Formatter << ">";
	m_State.SetOpenedForAttributes(false);
	return *this;
}


СWriter& СWriter::operator << (const CCloseTag& CloseTag)
{
	if(m_State.AttributesOpened())
	{
		m_Formatter << "/>";
	}
	else
	{
		m_Formatter << ("</" + m_State.GetTagName() + ">");
	}

	m_State.ReturnToPrevious();

	return *this;
}
