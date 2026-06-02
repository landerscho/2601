#include <stdio.h>
#include <stdlib.h>

#define SIZE 7 // 시각화를 위해 7개(3레벨 트리)로 고정

// 배열 요소 교환 함수
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 현재 배열 상태와 트리 구조를 시각적으로 출력하는 함수
void printState(int arr[], int heap_size, int step, const char* msg) {
    printf("\n==================================================\n");
    if (step >= 0) printf("[Step %d] %s\n", step, msg);
    else printf("▶ %s\n", msg);
    
    // 1. 배열 상태 출력 (힙 영역과 정렬 완료 영역을 분리해서 표시)
    printf("\n배열 상태: [ ");
    for (int i = 0; i < SIZE; i++) {
        if (i == heap_size && heap_size < SIZE) {
            printf("| "); // 힙 영역이 끝나는 지점 표시
        }
        printf("%02d ", arr[i]);
    }
    printf("]\n");
    if (heap_size < SIZE) {
        printf("           (왼쪽: 힙 영역 | 오른쪽: 정렬 완료)\n");
    }

    // 2. 트리 구조 시각화 (콘솔 텍스트 기반)
    printf("\n[현재 힙(트리) 구조]\n");
    if (heap_size == 0) {
        printf("  (힙 영역이 비어있습니다 - 정렬 완료)\n");
    } else {
        // 1레벨 (Root)
        printf("             (%02d)\n", arr[0]);
        
        // 2레벨
        if (heap_size > 1) {
            printf("           /      \\\n");
            printf("        (%02d)", arr[1]);
            if (heap_size > 2) printf("      (%02d)\n", arr[2]);
            else printf("\n");
        }
        
        // 3레벨
        if (heap_size > 3) {
            printf("        /  \\");
            if (heap_size > 5) printf("      /  \\\n");
            else if (heap_size > 4) printf("      /\n");
            else printf("\n");
            
            printf("     (%02d)", arr[3]);
            if (heap_size > 4) printf("  (%02d)", arr[4]);
            
            if (heap_size > 5) printf("  (%02d)", arr[5]);
            if (heap_size > 6) printf("  (%02d)\n", arr[6]);
            else printf("\n");
        }
    }
    printf("==================================================\n");
    
    // 사용자 입력 대기 (Enter 키를 누르면 다음으로 진행)
    printf(">> 다음 단계를 보려면 Enter를 누르세요...");
    while (getchar() != '\n');
}

// 힙 성질을 유지하도록 아래로 내려가며 정렬하는 함수 (Max Heapify)
void heapify(int arr[], int heap_size, int i) {
    int largest = i;       // 루트를 가장 큰 값으로 가정
    int left = 2 * i + 1;  // 왼쪽 자식 노드 인덱스
    int right = 2 * i + 2; // 오른쪽 자식 노드 인덱스

    // 왼쪽 자식이 루트보다 크면 largest 갱신
    if (left < heap_size && arr[left] > arr[largest])
        largest = left;

    // 오른쪽 자식이 현재까지의 largest보다 크면 갱신
    if (right < heap_size && arr[right] > arr[largest])
        largest = right;

    // largest가 루트가 아니라면 교환하고, 교환된 자식 노드에 대해 다시 heapify 진행
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        // 시각화: 내부 교환 과정 출력 (선택 사항이므로 진행을 빠르게 하려면 주석 처리 가능)
        // printState(arr, heap_size, -1, "Heapify 진행 중 (자식 노드와 위치 교환)"); 
        heapify(arr, heap_size, largest);
    }
}

// 힙 정렬 메인 함수
void heapSort(int arr[], int n) {
    int step = 1;
    
    printState(arr, n, 0, "초기 배열 상태 (아직 힙이 아님)");

    // 1. 초기 배열을 최대 힙(Max Heap) 구조로 만듦
    // 마지막 부모 노드부터 루트(0)까지 역순으로 heapify 적용
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    printState(arr, n, step++, "최대 힙(Max Heap) 구성 완료! (가장 큰 값이 루트에 위치함)");

    // 2. 힙에서 요소를 하나씩 추출하여 정렬
    for (int i = n - 1; i > 0; i--) {
        // 현재 루트(가장 큰 값)를 힙의 마지막 요소와 교환
        char msg[100];
        sprintf(msg, "루트 값(%02d)과 마지막 노드(%02d) 교환 -> '%02d' 정렬 완료", arr[0], arr[i], arr[0]);
        swap(&arr[0], &arr[i]);
        printState(arr, i, step++, msg); // i가 현재 남은 힙의 크기가 됨 (교환된 마지막 요소는 정렬 완료 영역으로 빠짐)

        // 줄어든 힙 영역에 대해 루트 노드부터 다시 최대 힙 성질을 복원
        heapify(arr, i, 0);
        sprintf(msg, "루트 노드 변경으로 인해 무너진 힙 구조 복원 (Heapify)");
        printState(arr, i, step++, msg);
    }
    
    printState(arr, 0, step, "🏁 모든 요소가 정렬되었습니다! (힙 정렬 완료)");
}

int main() {
    // 7개의 난수 배열 생성
    int data[SIZE] = { 42, 17, 93, 8, 65, 31, 54 };

    printf("==================================================\n");
    printf("        🔄 힙 정렬(Heap Sort) 시뮬레이터 🔄\n");
    printf("==================================================\n");
    printf("- 배열을 이진 트리로 시각화하여 정렬 과정을 보여줍니다.\n");
    printf("- Enter 키를 누르면서 단계별로 확인해 보세요.\n");
    printf(">> 시작하려면 Enter를 누르세요...");
    while (getchar() != '\n');

    // 힙 정렬 시작
    heapSort(data, SIZE);

    return 0;
}
