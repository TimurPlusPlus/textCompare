#ifndef DOCUMENT_H
#define DOCUMENT_H
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Document
{
        string date;
        string ruleName;
        string actDate;
        string department;
        string government;
        string redactions;
        string fileName;
        long lastReadLine;
        vector <string> text;

        void parseGeneralInfo();
        void readFile();
    public:
        Document (string);
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
       // ifstream* getPDD(){return pd1;}
        vector <string> getText(){return text;}
        void operator = (Document doc);

};

#endif // DOCUMENT_H
