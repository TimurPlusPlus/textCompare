#ifndef DOCUMENT_H
#define DOCUMENT_H
#include <iostream>
#include <fstream>

using namespace std;

class Document
{
        string file;
        string date;
        string ruleName;
        string actDate;
        string department;
        string government;
        string redactions;
        long lastReadLine;
        ifstream *pd1;

        void parseGeneralInfo();

    public:
        Document(string newFile);
        string getFile() { return file; }
        void setFile(string val) { file = val; }
        string getDate() { return date; }
        void setDate(string val) { date = val; }
        string getRuleName() { return ruleName; }
        void setRuleName(string val) { ruleName = val; }
        string getActDate() { return actDate; }
        void setActDate(string val) { actDate = val; }
        string getDepartment() { return department; }
        void setDepartment(string val) { department = val; }
        string getGovernment() { return government; }
        void setGovernment(string val) { government = val; }
        string getRedactions() { return redactions; }
        void setRedactions(string val) { redactions = val; }
        long getLastReadLine() { return lastReadLine; }
        void setLastReadLine(long val) { lastReadLine = val; }
        ifstream* getPD(){return pd1;}
        void operator = (Document doc);

};

#endif // DOCUMENT_H
