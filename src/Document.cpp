#include "Document.h"
#include <algorithm>


Document::Document(string newFile)
{
    file = newFile;
    //pdd =
    parseGeneralInfo();
}
void Document::operator= (Document doc)
{
    file = doc.getFile();
    date = doc.getDate();
    ruleName = doc.getRuleName();
    actDate = doc.getActDate();
    department = doc.getDepartment();
    government = doc.getGovernment();
    redactions = doc.getRedactions();
}
void Document::parseGeneralInfo()
{
    ifstream pdd1(file);
    string textLine;
    getline(pdd1, textLine);
    getline(pdd1, textLine);
    getline(pdd1, textLine);
    getline(pdd1, textLine);
    getline(pdd1, textLine);
    transform(textLine.begin(), textLine.end(), textLine.begin(), ::toupper);
    actDate = textLine;
    getline(pdd1, textLine);
    getline(pdd1, textLine);
    ruleName = textLine;
    getline(pdd1, textLine);
    getline(pdd1, textLine);
    string str;
    while(textLine != "")
    {
        str += textLine;
        getline(pdd1, textLine);
    }
    redactions = str;
    getline(pdd1, textLine);
    while (textLine != "")
        getline(pdd1, textLine);
    getline(pdd1, textLine);
    textLine = textLine.substr(textLine.find(" ", 0), textLine.length() - 1);
    transform(textLine.begin(), textLine.end(), textLine.begin(), ::toupper);
    department = textLine;
    getline(pdd1, textLine);
    transform(textLine.begin(), textLine.end(), textLine.begin(), ::toupper);
    government = textLine;
}
