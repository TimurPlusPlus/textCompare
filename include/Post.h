#ifndef POST_H
#define POST_H
#include "Document.h"
#include <fstream>

class Post
{
        Document pdd1;
        Document pdd2;
        string redaction;
        long lastLine;
        void findCurrentRedaction();
        bool isRedactionFind(ifstream &pd2, string textLine, long &lastReadLine);
    public:
        Post(Document pdd1, Document pdd2);
        /*Document getPdd1() { return pdd1; }
        void setPdd1(Document val) { pdd1 = val; }
        Document getPdd2() { return pdd2; }
        void setPdd2(Document val) { pdd2 = val; }*/
        string getRedaction() { return redaction; }
        void setRedaction(string val) { redaction = val; }
        void makePostTitle();
        string getPostNumber();
        void findDifference();


};

#endif // POST_H
