#include <iostream>
#include "threadsafe_lookuptable.h"
using namespace std;

struct hash_int
{
    int operator()(int key) const
    {
        return key;
    }
};


int main()
{
    threadsafe_lookup_table<int, int, hash_int > t;  // ͨ��hash_int ��1��20ӳ���˵�ͬһ��bucket��

    t.add_or_update_mapping(1, 1);
    t.add_or_update_mapping(20, 2222);

    system("pause");
}