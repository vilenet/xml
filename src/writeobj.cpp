#include "writeobj.h" 

bool WriteObject(const СWritableObj& WritableObj, const char* szFileName, const char* szOpenFileMode)
{
	FILE* hFile = fopen(szFileName, szOpenFileMode);

	if (hFile == nullptr)
	{
	    return false;
	}

	WriteObject(WritableObj, hFile);
	fclose(hFile);

	return true;
}

bool WriteObject(const СWritableObj2& WritableObj, const char *szFileName, const char* szOpenFileMode)
{
    FILE *hFile = fopen(szFileName, szOpenFileMode);

    if (hFile == nullptr)
    {
        return false;
    }

    FILE *hStream = hFile;
    CStreamWriter StreamWriter(hStream);
    СWriter Writer(StreamWriter);
    WritableObj.WriteXML(Writer, false);

    fclose(hFile);

    return true;
}

