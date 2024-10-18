#include "myHashTable.h"


// 哈希表每次重建增长后的大小
int hashsize[] = { 11, 31, 61, 127, 251, 503 };
int index    = 0;



Status initHashTable(HashTable &H, int size)
{
  int i;
  H.rcd = (RcdType *)malloc(sizeof(RcdType) * size);
  H.tag = (int *)malloc(sizeof(int) * size);
  if ((H.rcd == NULL) || (H.tag == NULL))  return HASHOVERFLOW;
  int maxnum = MAXNUM;

  for (i = 0; i < size; i++)  
  {
    H.rcd[i].key = maxnum;
    H.tag[i] = 0;
  }
  H.size = size;
  H.count = 0;
  return HASHOK;
}

Status searchHash(HashTable &H, KeyType key, int &p, int &c)
{
  p = Hash(key,H.size);
  // int h = p;
  c = 0;
  while ((H.tag[p] == 1) && (H.rcd[p].key != key) || (H.tag[p] == -1)) 
  {
    // 处理冲突
    collision(p, H.size);
    c++;
    if (c >= H.size) {
      return HASHERROR;  // 返回错误，表明哈希表已满或未找到
    }
  }
  if (H.tag[p] == 1 && H.rcd[p].key == key) return HASHOK;
  else return HASHERROR;
}

int Hash(KeyType key, int m)
{
  return (3 * key) % m;  // 除留余数
}

void collision(int &p, int m)
{
  p = (p + 1) % m;
}

Status insertHash(HashTable &H, KeyType key)
{
  int p, c;
  if (searchHash(H,key,p,c) == HASHERROR){
    if (c*1.0 / H.size < 0.5){
      H.rcd[p].key = key;
      H.tag[p] = 1;
      H.count++;
      return HASHOK;
    }
    else{
      recreateHash(H); // 
    }
  }
    
  return HASHERROR;
}

Status recreateHash(HashTable &H)
{
  RcdType *orcd;
	int *otag, osize, i;
	orcd = H.rcd;
	otag = H.tag;
	osize = H.size;
  printf("recreateHash size:: %d",index);
	initHashTable(H, hashsize[index++]);
	//把所有元素，按照新哈希函数放到新表中
	for (i = 0; i < osize; i++) {
		if (1 == otag[i]) {
			insertHash(H, orcd[i].key);
		}
	}
	return HASHOK;
}

Status deleteHash(HashTable &H, KeyType key)
{
  int p, c;
  if (searchHash(H, key, p, c) == HASHOK){
    H.tag[p] = -1;
    H.count--;
    return HASHOK;
  }
  else return HASHERROR;
}

void printHashTable(HashTable &H)
{
	int  i;
	printf("key(%d) : ",H.size);
	for (i = 0; i < H.size; i++)
		printf("%3d ", H.rcd[i].key);
	printf("\n");
	printf("tag(%d) : ",H.size);
	for (i = 0; i < H.size; i++)
		printf("%3d ", H.tag[i]);
	printf("\n\n");
}
