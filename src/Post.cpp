#include "Post.h"
#include "Document.h"
#include <fstream>
#include <algorithm>

Post::Post(Document pd1, Document pd2): pdd1(pd1), pdd2(pd2)
{
    findCurrentRedaction();
}

void Post::findCurrentRedaction()       //���������� ����� �������������.
{
    string res;
    string red1 = pdd1.getRedactions();
    string red2 = pdd2.getRedactions();
    if(red1.find("N", 0) == string::npos)                               //���� ������ �������� ��� ��������
    {
        res = red2.substr(red2.find("N", 0) - 14, red2.length() - 2);  //-14 �.�. ���������� � �������� ������� � �������:
        res = res.substr(0, res.length() - 1);                        // "�� 11.11.2011 N ..." ����� ��������� �� 14 �������� �����.
    }
    else
        {                                                       //��������� �������, � ������� ������� N ���.
            int prevNPosition;
            for(int i = 1; i < red1.length() - 2; i++)
            {
                if(red1.at(i) != 'N')
                    continue;
                else                                        //����� ��������� ��������.
                {
                    string tempRedDoc1;
                    string tempRedDoc2;
                    while(red1.at(i) != ',' && red1.at(i) != ')')
                    {
                        tempRedDoc1 += red1.at(i);
                        tempRedDoc2 += red2.at(i);
                        if(red1.at(i) != red2.at(i))      //���� �������� �������� ����������, ������ ����� ����� �������������.
                            break;
                        i++;
                    }
                    if(tempRedDoc1 != tempRedDoc2)
                    {
                        int startPos = prevNPosition;   //�������� ����� ���������� N �� 2-� ��������� � ���������� ���������� N.
                        while(red2.at(startPos) != 'N')
                            startPos++;
                        int endPos = startPos;
                        while(red2.at(endPos) != ',' && red2.at(endPos != ')'))
                            endPos++;
                        startPos -= 14;
                        endPos -= 1;                 //�������� ������ ������ "," ��� ")"
                        res = red2.substr(startPos, endPos);
                        res = res.substr(0, endPos - startPos + 1);
                        break;
                    }
                    prevNPosition = i;              //���������� ��������� �������, � ������� ������� N.
                }
            }
            if(res == "")                           //���� ����� �� ����� ������� ���������, �� ��� � �� ����� �������.
            {
                res = red2.substr(red1.length(), red2.length() - 2);    //������ ������� � ��������� N ���. ��������� 2.
                res = res.substr(0, res.length() - 1);
            }
        }
        redaction = res;
}

void Post::findDifference()
{
    long lineIndex = 0;
    string textLine = "";
    ifstream* pd2 = pdd2.getPD();
    /*ifstream pd2(pdd2.getFile());
    long lastReadLine = pdd2.getLastReadLine();
    while(lineIndex != lastReadLine)   //������� �� ��������� ������, �� ������� ���������.
    {
        getline(pd2, textLine);
        lineIndex++;
    }*/
    string actDate = pdd2.getActDate();
    while(textLine != actDate)        //��� �� ��������������� ������ ���������.
    {
        getline(*pd2, textLine);
        //lastReadLine++;
        transform(textLine.begin(), textLine.end(), textLine.begin(), ::toupper);
    }
    getline(*pd2, textLine);
    //lastReadLine++;
    getline(*pd2, textLine);
    //lastReadLine++;
    string regulation = "";         //�������� �������
    while(textLine != "")
    {
        regulation += textLine;
        regulation += " ";
        getline(*pd2, textLine);
        //lastReadLine++;
    }
    cout << regulation;
    getline(*pd2, textLine); //������� � �������
    //lastReadLine++;
    if(textLine.find("� ���. ", 0) == string::npos) //���� ������ �� � ����������, � � �������.
    {
        while(textLine != "")                     //������� �� ������ ������.
        {
            getline(*pd2, textLine);
            //lastReadLine++;
        }
    }
    //getline(*pd2, textLine);
    //lastReadLine++;
    if(isRedactionFind(*pd2, textLine))  //���� ����� ������
    {

        cout << "COOOOOOL" << " " << textLine;
    }
    else            // ���� ����� �� ������, ����� ������ ��������� �������.
    {

    }
    ///TODO: �������� ������ ��������
   ///       ����������� ������, ������
  ///        ����� �������
}

bool Post::isRedactionFind(ifstream &pd2, string textLine)
{
    bool seeked = false;
    while(textLine != "")
    {
        if(textLine.find(getPostNumber(), 0) != string::npos)   //���� ����� ������������� ������� � ���������.
        {
            seeked = true;
            break;
        }
        getline(pd2, textLine);
        //lastReadLine++;
    }
    return seeked;
}


void Post::makePostTitle()      //������ ����� �������������.
{
    string fileName = "post" + getPostNumber() + ".txt";
    ofstream post1(fileName);
    post1 << endl
          << "������������� ���������� ���������" << endl << endl;
    post1 << "�������������"                      << endl;
    post1 << redaction                            << endl << endl;
    post1 << "� �������� ���������"               << endl
          << "� ������������� ";
    post1 << pdd1.getDepartment()                 << endl;
    post1 << pdd1.getGovernment()                 << " ";
    post1 << pdd1.getActDate()                    << endl << endl;
    post1 << "������������� ���������� ���������"
          << "������������:"                      << endl;
    post1 << "��������� ����������� ���������,"
          <<" ������� �������� � �������������";
    post1 << pdd1.getDepartment()                 << " "
          << pdd1.getGovernment()                 << " "
          << pdd1.getActDate()                    << " \""
          << pdd1.getRuleName()                   << "\" " << endl << endl;
    post1 << "������������ �������������"         << endl
          << "���������� ���������"               << endl
          << "�\.�����"                           << endl  << endl << endl
          << endl << endl << endl;
    post1 << "����������"                         << endl
          << "�������������� �������������"       << endl
          << "���������� ���������"               << endl;
    post1 << redaction                            << endl  << endl;
    post1 << "���������,"                         << endl
          << "������� �������� � �������������"   << endl;
    post1 << pdd1.getDepartment()                 << endl;
    post1 << pdd1.getGovernment()                 << endl;
    post1 << pdd1.getActDate()                    << endl  << endl;
    //post1 << "1.";

    lastLine = post1.tellp();
}

string Post::getPostNumber()            //���������� ����� �������������.
{
    return redaction.substr(redaction.rfind(" ") + 1, redaction.length() - 1);
}
