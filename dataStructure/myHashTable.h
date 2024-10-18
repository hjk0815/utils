


#pragma once

#include <iostream>


#define MAXNUM 9999	

typedef int KeyType;


enum Status{
  HASHOK,
  HASHERROR,
  HASHOVERFLOW,
};

struct RcdType
{
  KeyType key;
};

struct HashTable
{
  RcdType *rcd;
  int size;
  int count;
  int *tag;
};


Status initHashTable(HashTable &H, int size);

Status searchHash(HashTable &H, KeyType key, int &p, int &c);

int Hash(KeyType key, int m); //  hash fuc

void collision(int &p, int m);

Status insertHash(HashTable &H, KeyType key);

Status recreateHash(HashTable &H);

Status deleteHash(HashTable &H, KeyType key);

void printHashTable(HashTable &H);