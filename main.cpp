#include <iostream>
#include <clocale>
#include "include\Document.h"
#include "include\Post.h"

using namespace std;

int main()
{
    setlocale(LC_CTYPE, "rus");
    string file1 = "pdd18.txt";
    string file2 = "pdd19.txt";
    Document pdd1(file1);
    Document pdd2(file2);
    Post post(pdd1, pdd2);
    post.findDifference();
    //post.makePostTitle();       //Создаём шапку постановления.
    return 0;
}
