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
    string textLine = "";
    vector <string> pd1 = pdd1.getText();
    vector <string> pd2 = pdd2.getText();
    string actDate = pdd2.getActDate();
    long lastReadLine = pdd2.getLastReadLine();
    while(textLine != actDate)        //��� �� ��������������� ������ ���������.
    {
        textLine = pd2.at(lastReadLine);
        lastReadLine++;
        transform(textLine.begin(), textLine.end(), textLine.begin(), ::toupper);
    }
    string regulation = "";                         //�������� �������
    for(lastReadLine += 1; pd2.at(lastReadLine) != ""; lastReadLine++)
    {
        regulation += pd2.at(lastReadLine);
        regulation += " ";
    }
    cout << regulation;
    lastReadLine++;
    textLine = pd2.at(lastReadLine);                //������� � �������
    if(textLine.find("� ���. ", 0) == string::npos) //���� ������ �� � ����������, � � �������.
        for(lastReadLine; pd2.at(lastReadLine) != ""; lastReadLine++); //������� �� ������ ������.
    lastReadLine++;
    if(isRedactionFind(pd2, lastReadLine))                              //���� ����� ������
    {
        for(lastReadLine; pd2.at(lastReadLine) != ""; lastReadLine++); //������� �� ������ ������.

        cout << "COOOOOOL" << " " << textLine;
    }
    else            // ���� ����� �� ������, ����� ������ ��������� �������.
    {

    }

   ///       ����������� ������, ������
  ///        ����� �������
}

bool Post::isRedactionFind(vector <string> & pd2, long & lastReadLine)
{
    string textLine;
    for(lastReadLine; pd2.at(lastReadLine) != ""; lastReadLine++)
    {
        textLine = pd2.at(lastReadLine);
        if(textLine.find(getPostNumber(), 0) != string::npos)   //���� ����� ������������� ������� � ���������.
            return true;
    }
    return false;
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
}

string Post::getPostNumber()            //���������� ����� �������������.
{
    return redaction.substr(redaction.rfind(" ") + 1, redaction.length() - 1);
}
