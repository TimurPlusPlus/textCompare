#include "Document.h"
#include <algorithm>


Document::Document(string fileName)
{
   // pd1 = &ifs;
    this->fileName = fileName;
    readFile();
    parseGeneralInfo();
}
void Document::operator= (Document doc)
{
    date = doc.getDate();
    ruleName = doc.getRuleName();
    actDate = doc.getActDate();
    department = doc.getDepartment();
    government = doc.getGovernment();
    redactions = doc.getRedactions();
    lastReadLine = doc.getLastReadLine();
    text = doc.getText();
   // pd1 = doc.getPDD();
}

void Document::readFile()
{
    ifstream pd1(fileName);
    string textLine;
    while(getline(pd1, textLine))
        text.push_back(textLine);
}
void Document::parseGeneralInfo()
{
    string textLine;
    textLine = text.at(4);
    transform(textLine.begin(), textLine.end(), textLine.begin(), ::toupper);
    actDate = textLine;
    ruleName = text.at(6);
    string str;
    for(lastReadLine = 8; text.at(lastReadLine) != ""; lastReadLine++)
        str += text.at(lastReadLine);
    redactions = str;
    lastReadLine++;
    for(lastReadLine; text.at(lastReadLine) != ""; lastReadLine++);      //Отматали до следующей пустой строки.
    lastReadLine++;
    textLine = text.at(lastReadLine);
    textLine = textLine.substr(textLine.find(" ", 0), textLine.length() - 1);
    transform(textLine.begin(), textLine.end(), textLine.begin(), ::toupper);
    department = textLine;
    textLine = text.at(lastReadLine);
    transform(textLine.begin(), textLine.end(), textLine.begin(), ::toupper);
    government = textLine;
}
