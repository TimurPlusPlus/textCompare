#include "Post.h"
#include "Document.h"
#include <fstream>
#include <algorithm>

Post::Post(Document pd1, Document pd2): pdd1(pd1), pdd2(pd2)
{
    findCurrentRedaction();
}

void Post::findCurrentRedaction()       //Определяет номер постановления.
{
    string res;
    string red1 = pdd1.getRedactions();
    string red2 = pdd2.getRedactions();
    if(red1.find("N", 0) == string::npos)                               //Если первый документ без редакций
    {
        res = red2.substr(red2.find("N", 0) - 14, red2.length() - 2);  //-14 т.к. информация о редакции пишется в формате:
        res = res.substr(0, res.length() - 1);                        // "от 11.11.2011 N ..." нужно отступить на 14 символов влево.
    }
    else
        {                                                       //Последняя позиция, в которой совпали N ред.
            int prevNPosition;
            for(int i = 1; i < red1.length() - 2; i++)
            {
                if(red1.at(i) != 'N')
                    continue;
                else                                        //Нашли очередную редакцию.
                {
                    string tempRedDoc1;
                    string tempRedDoc2;
                    while(red1.at(i) != ',' && red1.at(i) != ')')
                    {
                        tempRedDoc1 += red1.at(i);
                        tempRedDoc2 += red2.at(i);
                        if(red1.at(i) != red2.at(i))      //Если названия редакций отличаются, значит нашли номер постановления.
                            break;
                        i++;
                    }
                    if(tempRedDoc1 != tempRedDoc2)
                    {
                        int startPos = prevNPosition;   //Начинаем поиск следующего N во 2-м документе с последнего совпавшего N.
                        while(red2.at(startPos) != 'N')
                            startPos++;
                        int endPos = startPos;
                        while(red2.at(endPos) != ',' && red2.at(endPos != ')'))
                            endPos++;
                        startPos -= 14;
                        endPos -= 1;                 //Вырезаем лишний символ "," или ")"
                        res = red2.substr(startPos, endPos);
                        res = res.substr(0, endPos - startPos + 1);
                        break;
                    }
                    prevNPosition = i;              //Запоминаем последнюю позицию, в которой совпали N.
                }
            }
            if(res == "")                           //Если дошли до конца первого документа, но так и не нашли разницу.
            {
                res = red2.substr(red1.length(), red2.length() - 2);    //Значит разница в последнем N ред. документа 2.
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
    while(lineIndex != lastReadLine)   //Листаем до последней строки, из которой считывали.
    {
        getline(pd2, textLine);
        lineIndex++;
    }*/
    string actDate = pdd2.getActDate();
    while(textLine != actDate)        //Идём до первоначального номера документа.
    {
        getline(*pd2, textLine);
        //lastReadLine++;
        transform(textLine.begin(), textLine.end(), textLine.begin(), ::toupper);
    }
    getline(*pd2, textLine);
    //lastReadLine++;
    getline(*pd2, textLine);
    //lastReadLine++;
    string regulation = "";         //Название ПРАВИЛА
    while(textLine != "")
    {
        regulation += textLine;
        regulation += " ";
        getline(*pd2, textLine);
        //lastReadLine++;
    }
    cout << regulation;
    getline(*pd2, textLine); //ПЕРЕШЛИ К СКОБКАМ
    //lastReadLine++;
    if(textLine.find("в ред. ", 0) == string::npos) //Если строка не с редакциями, а с ГОСТами.
    {
        while(textLine != "")                     //Листаем до пустой строки.
        {
            getline(*pd2, textLine);
            //lastReadLine++;
        }
    }
    //getline(*pd2, textLine);
    //lastReadLine++;
    if(isRedactionFind(*pd2, textLine))  //Если номер найден
    {

        cout << "COOOOOOL" << " " << textLine;
    }
    else            // Если номер не найден, нужно искать следующее правило.
    {

    }
    ///TODO: ПРОВЕРКА НОМЕРА РЕДАКЦИИ
   ///       ОПРЕДЕЛЕНИЕ ПУНКТА, АБЗАЦА
  ///        ПОИСК РАЗНИЦЫ
}

bool Post::isRedactionFind(ifstream &pd2, string textLine)
{
    bool seeked = false;
    while(textLine != "")
    {
        if(textLine.find(getPostNumber(), 0) != string::npos)   //Если номер постановления нашёлся в редакциях.
        {
            seeked = true;
            break;
        }
        getline(pd2, textLine);
        //lastReadLine++;
    }
    return seeked;
}


void Post::makePostTitle()      //Строит шапку постановления.
{
    string fileName = "post" + getPostNumber() + ".txt";
    ofstream post1(fileName);
    post1 << endl
          << "ПРАВИТЕЛЬСТВО РОССИЙСКОЙ ФЕДЕРАЦИИ" << endl << endl;
    post1 << "ПОСТАНОВЛЕНИЕ"                      << endl;
    post1 << redaction                            << endl << endl;
    post1 << "О ВНЕСЕНИИ ИЗМЕНЕНИЙ"               << endl
          << "В ПОСТАНОВЛЕНИЕ ";
    post1 << pdd1.getDepartment()                 << endl;
    post1 << pdd1.getGovernment()                 << " ";
    post1 << pdd1.getActDate()                    << endl << endl;
    post1 << "Правительство Российской Федерации"
          << "постановляет:"                      << endl;
    post1 << "Утвердить прилагаемые изменения,"
          <<" которые вносятся в постановление";
    post1 << pdd1.getDepartment()                 << " "
          << pdd1.getGovernment()                 << " "
          << pdd1.getActDate()                    << " \""
          << pdd1.getRuleName()                   << "\" " << endl << endl;
    post1 << "Председатель Правительства"         << endl
          << "Российской Федерации"               << endl
          << "В\.ПУТИН"                           << endl  << endl << endl
          << endl << endl << endl;
    post1 << "Утверждены"                         << endl
          << "постановлением Правительства"       << endl
          << "Российской Федерации"               << endl;
    post1 << redaction                            << endl  << endl;
    post1 << "ИЗМЕНЕНИЯ,"                         << endl
          << "КОТОРЫЕ ВНОСЯТСЯ В ПОСТАНОВЛЕНИЕ"   << endl;
    post1 << pdd1.getDepartment()                 << endl;
    post1 << pdd1.getGovernment()                 << endl;
    post1 << pdd1.getActDate()                    << endl  << endl;
    //post1 << "1.";

    lastLine = post1.tellp();
}

string Post::getPostNumber()            //Возвращает номер постановления.
{
    return redaction.substr(redaction.rfind(" ") + 1, redaction.length() - 1);
}
