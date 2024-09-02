#include "format.h"
#include "writer.h"
#include <iostream>

int main() 
{
    std::ostream& outputStream = std::cout;
    CStreamTarget target(outputStream);
    СWriter writer(target);

    writer 
        << COpenTag("root") << CAttribute("version", "1.0") << CAttribute("encoding", "UTF-8") << CCloseAttributes()
            << COpenTag("metadata")
                << CTag("title", "Example XML")
                << CTag("author", "OpenAI")
                << COpenTag("date") 
                    << CTag("created", "2024-01-01")
                    << CTag("modified", "2024-08-28")
                << CCloseTag() // Close tag date
            << CCloseTag() // Close tag metadata
            << COpenTag("content")
                << COpenTag("section") << CAttribute("id", "1") << CAttribute("name", "Introduction") << CCloseAttributes()
                    << CTag("paragraph", "This is the introduction section.")
                << CCloseTag() // Close tag section
                << COpenTag("section") << CAttribute("id", "2") << CAttribute("name", "Main Content") << CCloseAttributes()
                    << COpenTag("paragraph")
                        << CTag("text", "This is the first paragraph of the main content.")
                        << CTag("text", "This is the second paragraph with more information.")
                    << CCloseTag() // Close tag paragraph
                << CCloseTag() // Close tag section
            << CCloseTag() // Close tag content
        << CCloseTag(); // Close tag root

    return 0;
}
