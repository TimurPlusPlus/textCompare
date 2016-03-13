#ifndef POST_H
#define POST_H
#include "Document.h"
#include <fstream>
#include <vector>

class Post
{
        Document pdd1;
        Document pdd2;
        string redaction;
        void findCurrentRedaction();
        bool isRedactionFind(vector <string> & pd2, long &lastReadLine);
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
        void compare();
        void findDifference(vector <string> &pd1, vector <string> &pd2, long &lastReadLine);
};

#endif // POST_H
