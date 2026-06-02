#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10 // 스택의 최대 크기

// 스택 구조체 정의
typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

// 스택 초기화
void initStack(Stack* s) {
    s->top = -1;
}

// 스택이 비었는지 확인
int isEmpty(Stack* s) {
    return s->top == -1;
}

// 스택이 가득 찼는지 확인
int isFull(Stack* s) {
    return s->top == MAX_SIZE - 1;
}

// 데이터 삽입(Push)
void push(Stack* s, int value) {
    if (isFull(s)) {
        printf("오류: 스택이 가득 찼습니다.\n");
        return;
    }
    s->data[++(s->top)] = value;
}

// 데이터 추출(Pop)
int pop(Stack* s) {
    if (isEmpty(s)) {
        printf("오류: 스택이 비어있습니다.\n");
        return -1;
    }
    return s->data[(s->top)--];
}

// 최상단 데이터 확인(Peek)
int peek(Stack* s) {
    if (isEmpty(s)) return -1;
    return s->data[s->top];
}

// [시각화 함수] 두 스택의 상태를 나란히 출력
void printStacks(Stack* original, Stack* temp) {
    printf("\n   [원본 스택]\t   [임시 스택]\n");
    printf("   -----------\t   -----------\n");
    
    // 두 스택 중 더 높은 top을 찾음
    int maxTop = (original->top > temp->top) ? original->top : temp->top;
    
    // 위에서부터 아래로 출력 (스택의 LIFO 형태 구현)
    for (int i = maxTop; i >= 0; i--) {
        // 원본 스택 부분
        if (i <= original->top) printf("\t%2d\t|", original->data[i]);
        else printf("\t  \t|");
        
        // 임시 스택 부분
        if (i <= temp->top) printf("\t%2d\n", temp->data[i]);
        else printf("\n");
    }
    printf("   -----------\t   -----------\n\n");
}

// 보조 스택을 이용한 스택 정렬 알고리즘 (오름차순)
void sortStack(Stack* original) {
    Stack temp;
    initStack(&temp);
    
    int step = 1;
    
    printf("==========================================\n");
    printf("   🔄 스택 정렬 시뮬레이션을 시작합니다 🔄\n");
    printf("==========================================\n");
    printStacks(original, &temp);

    // 원본 스택이 빌 때까지 반복
    while (!isEmpty(original)) {
        // 1. 원본 스택에서 하나를 꺼냄
        int current = pop(original);
        printf("[Step %d] 원본 스택에서 '%d'을(를) Pop(추출)했습니다.\n", step++, current);
        
        // 2. 임시 스택의 Top이 current보다 크다면, 작거나 같은 값이 나올 때까지 
        //    임시 스택의 값들을 다시 원본 스택으로 되돌려 보냄
        while (!isEmpty(&temp) && peek(&temp) > current) {
            int moved = pop(&temp);
            push(original, moved);
            printf("  👉 임시 스택의 '%d'이(가) '%d'보다 커서 원본 스택으로 되돌립니다.\n", moved, current);
            printStacks(original, &temp);
        }
        
        // 3. 알맞은 자리를 찾았으므로 임시 스택에 current를 넣음
        push(&temp, current);
        printf("[Step %d] 임시 스택에 '%d'을(를) Push(삽입)했습니다.\n", step++, current);
        printStacks(original, &temp);
        
        // 사용자가 천천히 볼 수 있도록 Enter 키 입력 대기
        printf(">> 다음 단계를 보려면 Enter를 누르세요...");
        while (getchar() != '\n'); 
    }
    
    // 임시 스택은 현재 내림차순(Top이 가장 작음)이므로 
    // 다시 원본으로 부으면 오름차순(Top이 가장
