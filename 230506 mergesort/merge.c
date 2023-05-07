//
//  merge.c
//  230506 mergesort
//
//  Created by 한설 on 2023/05/07.
//

#include "merge.h"


void swap(int *a, int *b);
void merge(int *a, int l, int m, int r);

void merge_sort(int *arr, int l, int r)
{
    if (l < r)
    {
        int k = (l + r) / 2;
        merge_sort(arr, l, k);
        merge_sort(arr, k + 1, r);
        merge(arr, l, k + 1, r);
    }
}

void merge(int *a, int l, int m, int r)    //l은 가장 왼쪽 원소 인덱스, m은 분할된 오른쪽 배열이 시작되는 인덱스 r은 가장 오른쪽 원소 인덱스
{
    int *sorted;
    int i, j, k, mtmp;
    k = 0;
    mtmp = m;   //mtmp = 초기 m의 값 저장
    sorted = (int*)malloc(sizeof(int) * r - l + 1); //필요한 칸수에 맞게 배열 생성
    for (i = l; i < mtmp; i++)  //왼쪽 배열의 가장 왼쪽부터
    {
        for (j = m; j < r + 1; j++) //오른쪽 배열의 가장 왼쪽부터
        {
             if (a[i] > a[j])
             {
                 sorted[k] = a[j];
                 m = m + 1;         //오른쪽 배열에서 하나가 임시배열로 들어갈 경우, 이후 과정에서 다시 인식하는걸 막기 위해 + 1
                 k = k + 1;         //임시배열 다음칸으로 옮기기
             }
        }
        sorted[k] = a[i];           //왼쪽배열에서 인식한 값보다 오른쪽 배열에서 인식한 값들 중 더 작은 값은 이제 없으므로 임시배열에 기입
        k = k + 1;                  //임시배열 다음칸으로 옮기기
    }
    
    while (m != r + 1)              //만약 오른쪽배열에서 미처 입력되지 못한 값이 있는 경우
    {
        sorted[k] = a[m];           //밀어넣기
        k = k + 1;
        m = m + 1;
    }
    k = 0;                          //원래 배열로 다시 입력해야 하므로 초기화
    for (i = l; i < r + 1; i++, k++)//원래 배열에 임시배열에 저장한 정렬값 덮어쓰기
        a[i] = sorted[k];
    
    free(sorted);
}

void swap(int *a, int *b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}
