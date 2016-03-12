#include "Document.h"
#include <algorithm>


Document::Document(ifstream& ifs)
{
    //file = newFile;
   // ifstream f(file);
   // pd1 = &f;
    pd1 = &ifs;
    parseGeneralInfo();
}
void Document::operator= (Document doc)
{
    //file = doc.getFile();
    date = doc.getDate();
    ruleName = doc.getRuleName();
    actDate = doc.getActDate();
    department = doc.getDepartment();
    government = doc.getGovernment();
    redactions = doc.getRedactions();
    pd1 = doc.getPD();
}
void Document::parseGeneralInfo()
{
   // ifstream pd1(file);
    string textLine;
    lastReadLine = 0;
    for(int i = 0; i < 5; i++)
    {
        getline(*pd1, textLine);
        lastReadLine++;
    }
    transform(textLine.begin(), textLine.end(), textLine.begin(), ::toupper);
    actDate = textLine;
    for(int i = 0; i < 2; i++)
    {
        getline(*pd1, textLine);
        lastReadLine++;
    }
    ruleName = textLine;
    for(int i = 0; i < 2; i++)
    {
        getline(*pd1, textLine);
        lastReadLine++;
    }
    string str;
    while(textLine != "")
    {
        str += textLine;
        getline(*pd1, textLine);
        lastReadLine++;
    }
    redactions = str;
    getline(*pd1, textLine);
    lastReadLine++;
    while (textLine != "")
    {
        getline(*pd1, textLine);
        lastReadLine++;
    }
    getline(*pd1, textLine);
    lastReadLine++;
    textLine = textLine.substr(textLine.find(" ", 0), textLine.length() - 1);
    transform(textLine.begin(), textLine.end(), textLine.begin(), ::toupper);
    department = textLine;
    getline(*pd1, textLine);
    lastReadLine++;
    transform(textLine.begin(), textLine.end(), textLine.begin(), ::toupper);
    government = textLine;
}
