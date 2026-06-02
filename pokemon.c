#include <stdio.h>
#include <string.h>

#define NUM_TYPES 18

// 포켓몬스터 18개 타입 목록 (인덱스와 매칭)
const char* TYPE_NAMES[NUM_TYPES] = {
    "노말", "불꽃", "물", "전기", "풀", "얼음", "격투", "독", "땅", 
    "비행", "에스퍼", "벌레", "바위", "고스트", "드래곤", "악", "강철", "페어리"
};

// 타입 상성표 (공격 타입이 행, 방어 타입이 열)
const float TYPE_CHART[NUM_TYPES][NUM_TYPES] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0.5, 0, 1, 1, 0.5, 1},       // 노말
    {1, 0.5, 0.5, 1, 2, 2, 1, 1, 1, 1, 1, 2, 0.5, 1, 0.5, 1, 2, 1},   // 불꽃
    {1, 2, 0.5, 1, 0.5, 1, 1, 1, 2, 1, 1, 1, 2, 1, 0.5, 1, 1, 1},     // 물
    {1, 1, 2, 0.5, 0.5, 1, 1, 1, 0, 2, 1, 1, 1, 1, 0.5, 1, 1, 1},     // 전기
    {1, 0.5, 2, 1, 0.5, 1, 1, 0.5, 2, 0.5, 1, 0.5, 2, 1, 0.5, 1, 0.5, 1}, // 풀
    {1, 0.5, 0.5, 1, 2, 0.5, 1, 1, 2, 2, 1, 1, 1, 1, 2, 1, 0.5, 1},   // 얼음
    {2, 1, 1, 1, 1, 2, 1, 0.5, 1, 0.5, 0.5, 0.5, 2, 0, 1, 2, 2, 0.5}, // 격투
    {1, 1, 1, 1, 2, 1, 1, 0.5, 0.5, 1, 1, 1, 0.5, 0.5, 1, 1, 0, 2},   // 독
    {1, 2, 1, 2, 0.5, 1, 1, 2, 1, 0, 1, 0.5, 2, 1, 1, 1, 2, 1},       // 땅
    {1, 1, 1, 0.5, 2, 1, 2, 1, 1, 1, 1, 2, 0.5, 1, 1, 1, 0.5, 1},     // 비행
    {1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 0.5, 1, 1, 1, 1, 0, 0.5, 1},       // 에스퍼
    {1, 0.5, 1, 1, 2, 1, 0.5, 0.5, 1, 0.5, 2, 1, 1, 0.5, 1, 2, 0.5, 0.5}, // 벌레
    {1, 2, 1, 1, 1, 2, 0.5, 1, 0.5, 2, 1, 2, 1, 1, 1, 1, 0.5, 1},     // 바위
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 0.5, 1, 1},         // 고스트
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 0.5, 0},         // 드래곤
    {1, 1, 1, 1, 1, 1, 0.5, 1, 1, 1, 2, 1, 1, 2, 1, 0.5, 1, 0.5},     // 악
    {1, 0.5, 0.5, 0.5, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 0.5, 2},   // 강철
    {1, 0.5, 1, 1, 1, 1, 2, 0.5, 1, 1, 1, 1, 1, 1, 2, 2, 0.5, 1}      // 페어리
};

// 입력받은 타입 문자열의 인덱스를 반환하는 함수 (찾지 못하면 -1 반환)
int get_type_index(const char* type_name) {
    for (int i = 0; i < NUM_TYPES; i++) {
        if (strcmp(TYPE_NAMES[i], type_name) == 0) {
            return i;
        }
    }
    return -1;
}

// 개행 문자(\n, \r)를 제거해주는 유틸리티 함수
void strip_newline(char* str) {
    str[strcspn(str, "\r\n")] = '\0';
}

int main() {
    char attack[50], def1[50], def2[50];
    
    printf("🔥 포켓몬스터 타입 상성 계산기 💧\n");
    printf("가능한 타입: ");
    for (int i = 0; i < NUM_TYPES; i++) {
        printf("%s", TYPE_NAMES[i]);
        if (i < NUM_TYPES - 1) printf(", ");
    }
    printf("\n----------------------------------------\n");

    while (1) {
        printf("\n공격할 타입을 입력하세요 (종료하려면 q 입력): ");
        fgets(attack, sizeof(attack), stdin);
        strip_newline(attack);
        
        if (strcmp(attack, "q") == 0 || strcmp(attack, "Q") == 0) {
            break;
        }

        printf("방어할 첫 번째 타입을 입력하세요: ");
        fgets(def1, sizeof(def1), stdin);
        strip_newline(def1);

        printf("방어할 두 번째 타입을 입력하세요 (없으면 엔터): ");
        fgets(def2, sizeof(def2), stdin);
        strip_newline(def2);

        // 인덱스 찾기
        int att_idx = get_type_index(attack);
        int def1_idx = get_type_index(def1);
        int def2_idx = get_type_index(def2); // 빈 문자열이나 잘못된 타입이면 -1

        // 예외 처리
        if (att_idx == -1 || def1_idx == -1) {
            printf("잘못된 타입이 입력되었습니다. 다시 입력해 주세요.\n");
            continue;
        }

        // 1. 첫 번째 방어 타입에 대한 배율 계산
        float multiplier = TYPE_CHART[att_idx][def1_idx];

        // 2. 두 번째 방어 타입이 존재하고 유효하며, 첫 번째 타입과 다를 경우 (이중 타입 계산)
        if (strlen(def2) > 0 && def2_idx != -1 && def1_idx != def2_idx) {
            multiplier *= TYPE_CHART[att_idx][def2_idx];
        }

        // 결과 출력
        printf("\n[%s] 타입으로 [%s", attack, def1);
        if (strlen(def2) > 0 && def2_idx != -1) {
            printf("/%s", def2);
        }
        printf("] 타입 공격 시:\n");

        // %g 포맷을 사용하면 2.0, 1.0 등 소수점 아래가 0일 때 깔끔하게 2, 1로 출력됩니다.
        if (multiplier > 1.0f) {
            printf("👉 배율: x%g (효과가 굉장했다!)\n", multiplier);
        } else if (multiplier == 0.0f) {
            printf("👉 배율: x%g (효과가 없는 것 같다...)\n", multiplier);
        } else if (multiplier < 1.0f) {
            printf("👉 배율: x%g (효과가 별로인 듯하다...)\n", multiplier);
        } else {
            printf("👉 배율: x%g (보통이다.)\n", multiplier);
        }
    }

    return 0;
}
