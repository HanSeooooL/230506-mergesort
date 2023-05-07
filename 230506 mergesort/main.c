//
//  main.c
//  230506 mergesort
//
//  Created by 한설 on 2023/05/06.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR_PER_LINE 100

int *filelead(char *name, int *n);
void merge_sort(int *arr, int l, int r);
void merge(int *arr, int l, int m, int r);
void swap(int *a, int *b);
void filesave(char *name, int *a, int n);

int main(int argc, const char * argv[]) {
    int *arr;
    int n = 0;
    arr = filelead("data.txt", &n);
    
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    
    printf("\n");
    merge_sort(arr, 0, n - 1);
    
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    
    filesave("result.txt", arr, n);
        
    return 0;
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

void swap(int *a, int *b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

int *filelead(char *name, int *n)
{
    int count = 1;
    char str[100], *a;
    int num, *arr;
    FILE *fp;                                   //파일 포인터
    fp = fopen(name, "r");                          //파일 읽기
    arr = (int*)malloc(sizeof(int) * 3);        //3칸 메모리 할당
    if (fp == NULL) {
        printf("파일이 없습니다.\n");
        exit(1);
    }
    else if(fp != NULL) {
        while(fgets(str, MAX_CHAR_PER_LINE, fp)) {    //한줄씩 읽어들이고
            a = strtok(str, " ");
            while (a != NULL) {
                if ((*n % 3) == 0 && !(*n == 0)) {      //n을 3으로 나눴을 때 나머지가 없고, (3의 배수) n이 0이 아닐 때
                    count += 1; //count를 1 늘리고
                    arr = realloc(arr, sizeof(int) * (count * 3));    //초기값이 3칸이므로 조건을 처음 만족했을 때 6칸 다음은 9칸. 3의 배수로 칸을 늘려간다.
                }
                num = atoi(a);                      //Ascii형태 int형으로 형변환
                *(arr + *n) = num;                    //arr배열의 n번째 칸에 point 대입
                *n = *n + 1;                            //반복할때마다 +1 (숫자 개수 파악)
                a = strtok(NULL, " ");                   //공백기준 토큰화
            }
        }
        fclose(fp);
    }
    return arr;
}

void filesave(char *name, int *a, int n)
{
    char **ia;
    ia = (char**)malloc(sizeof(char*) * n);
    for (int i = 0; i < n; i++)
    {
        ia[i] = (char*)malloc(sizeof(char) * 10);
    }
    for (int i = 0; i < n; i++)
        sprintf(ia[i], "%d", a[i]);
    FILE *fp = fopen("result.txt", "w");    //파일 쓰기 모드로 open
    for(int i = 0; i < n; i++)
    {
        fputs(ia[i], fp);
        fputs(" ", fp);
    }
    fclose(fp); //파일 닫기
    free(a);
}
