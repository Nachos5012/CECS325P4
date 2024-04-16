// Krisha Hemani
// Class (CECS 325-02)
// Project Name (Prog 4 – Sorting Contest using pThreads)
// 03/28/2024
// I am using some/majority code from prog3 and made changes to use pthreads. I also used the merge logic which was demonstrated in class.
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <thread>
#include <iostream>
#include <unistd.h>
#include <fstream>
using namespace std;

struct Data {
  int* a1;
  int s1;
  int* a2;
  int s2;
};

void bubbleSort(int arr[], int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        swap(arr[j], arr[j + 1]);
      }
    }
  }
}

void* Bridge(void* numbers) {
  int* data = (int*)numbers;
  bubbleSort(data, 100000);
  return NULL;
}

void merge(int* a1, int s1, int* a2, int s2) {
  int temp[s1 + s2];
  int IndexArray1 = 0, IndexArray2 = 0, TempIndex = 0;
  while (IndexArray1 < s1 && IndexArray2 < s2) {
    if (a1[IndexArray1] < a2[IndexArray2]) {
      temp[TempIndex++] = a1[IndexArray1++];
    }
    else if (a1[IndexArray1] > a2[IndexArray2]) {
      temp[TempIndex++] = a2[IndexArray2++];
    }
    else if (a1[IndexArray1] == a2[IndexArray2]) {
      temp[TempIndex++] = a1[IndexArray1++];
    }
  }
  while (IndexArray1 < s1) {
    temp[TempIndex++] = a1[IndexArray1++];
  }
  while (IndexArray2 < s2) {
    temp[TempIndex++] = a2[IndexArray2++];
  }
  for (int MergePos = 0; MergePos < s1 + s2; MergePos++) {
    a1[MergePos] = temp[MergePos];
  }
}

int main(int argc, char* argv[]) {
  cout << "\nargv[0]: " << argv[0] << "\n";
  cout << "argv[1]: " << argv[1] << "\n";
  cout << "argv[2]: " << argv[2] << "\n";
  ifstream file(argv[1]);
  if (!file) {
    cout << "\nFile: " << argv[1] << " was not created!! \n";
    return 1;
  }
  const int max = 1000000;
  int numbers[max];
  int count =0;
  bool empty = true;
  while (count < max && file >> numbers[count]) {
    count++;
    empty=false;
  }
  if (empty == true) {
    cout << "No numbers were sorted. \n";
    ofstream out(argv[2]);
    file.close();
    out.close();
    return 0;
  }
  int *st0 =numbers;
  int *st1 =numbers+100000;
  int *st2 =numbers+200000;
  int *st3 =numbers+300000;
  int *st4 =numbers+400000;
  int *st5 =numbers+500000;
  int *st6 =numbers+600000;
  int *st7 =numbers+700000;
  

  pthread_t threads[8];
  pthread_create(&threads[0], NULL, Bridge, (void*)st0);
  pthread_create(&threads[1], NULL, Bridge, (void*)st1);
  pthread_create(&threads[2], NULL, Bridge, (void*)st2);
  pthread_create(&threads[3], NULL, Bridge, (void*)st3);
  pthread_create(&threads[4], NULL, Bridge, (void*)st4);
  pthread_create(&threads[5], NULL, Bridge, (void*)st5);
  pthread_create(&threads[6], NULL, Bridge, (void*)st6);
  pthread_create(&threads[7], NULL, Bridge,  (void*)st7);
  

  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);
  pthread_join(threads[2], NULL);
  pthread_join(threads[3], NULL);
  pthread_join(threads[4], NULL);
  pthread_join(threads[5], NULL);
  pthread_join(threads[6], NULL);
  pthread_join(threads[7], NULL);

    merge(st0, 100000, st1, 100000);
    merge(st2, 100000, st3, 100000);
    merge(st4, 100000, st5, 100000);
    merge(st6, 100000, st7, 100000);
    merge(st0, 200000, st2, 200000);
    merge(st4, 200000, st6, 200000);
    merge(st0, 400000, st4, 400000);
    merge(st0, 400000, st4, 400000);


  ofstream out(argv[2]);
  for (int i = 0; i < count; i++) {
    out << numbers[i] << '\n';
  }

  file.close();
  out.close();

  return 0;
}
