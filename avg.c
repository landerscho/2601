#include <stdio.h>

int main() {
    int at_bats, hits;
    float average;

    printf("⚾ 야구 타율 계산기 ⚾\n");
    printf("--------------------\n");

    // 타수 입력받기
    printf("타수를 입력하세요 (예: 100): ");
    if (scanf("%d", &at_bats) != 1) {
        printf("오류: 숫자를 올바르게 입력해 주세요.\n");
        return 1;
    }

    // 안타 수 입력받기
    printf("안타 수를 입력하세요 (예: 30): ");
    if (scanf("%d", &hits) != 1) {
        printf("오류: 숫자를 올바르게 입력해 주세요.\n");
        return 1;
    }

    // 입력값 검증 및 타율 계산
    if (at_bats < 0 || hits < 0) {
        printf("오류: 타수와 안타는 0 이상이어야 합니다.\n");
    } else if (hits > at_bats) {
        printf("오류: 안타 수가 타수보다 많을 수 없습니다.\n");
    } else if (at_bats == 0) {
        printf("--------------------\n");
        printf("결과 타율: 0.000\n");
    } else {
        // 정수끼리 나누면 소수점이 버려지므로, (float)를 사용해 실수형으로 변환 후 계산합니다.
        average = (float)hits / at_bats;
        printf("--------------------\n");
        printf("결과 타율: %.3f\n", average); // 소수점 셋째 자리까지 출력
    }

    return 0;
}
