#include <stdio.h>
#include <string.h>

#define MAX_WORDS 100    // 최대 저장할 수 있는 단어 수
#define MAX_LENGTH 50    // 단어의 최대 글자 수 (바이트 기준)

int main() {
    char used_words[MAX_WORDS][MAX_LENGTH]; // 사용된 단어들을 저장할 2차원 배열
    int word_count = 0;                     // 현재까지 입력된 단어 수
    char current_word[MAX_LENGTH] = "";     // 현재 제시어
    char user_input[MAX_LENGTH];            // 사용자가 입력한 단어
    int turn_count = 1;

    printf("?? C언어 끝말잇기 게임에 오신 것을 환영합니다! ??\n");
    printf("--------------------------------------------------\n");
    printf("?? 규칙:\n");
    printf("1. 한글 기준 2글자 이상의 단어만 입력할 수 있습니다.\n");
    printf("2. 이전 단어의 마지막 글자로 시작해야 합니다.\n");
    printf("3. 한 번 사용한 단어는 다시 쓸 수 없습니다.\n");
    printf("4. 게임을 끝내고 싶다면 '포기'를 입력하세요.\n");
    printf("--------------------------------------------------\n\n");

    while (1) {
        // 1. 단어 입력 받기
        if (word_count == 0) {
            printf("?? 첫 번째 단어를 제시해 주세요: ");
        } else {
            printf("\n[%d번째 턴] 현재 제시어: %s\n", turn_count, current_word);
            printf("?? 다음 단어 입력: ");
        }
        scanf("%s", user_input);

        // 2. 종료 조건 확인 ('포기' 입력 시)
        if (strcmp(user_input, "포기") == 0) {
            printf("\n========================================\n");
            printf("?? 게임 종료! 항복하셨습니다.\n");
            printf("?? 총 이어나간 단어 수: %d개\n", word_count);
            printf("?? 사용된 단어 목록: ");
            for (int i = 0; i < word_count; i++) {
                printf("%s", used_words[i]);
                if (i < word_count - 1) printf(", ");
            }
            printf("\n========================================\n");
            break;
        }

        // 3. 규칙 1: 글자 수 확인 (C언어에서 한글은 1글자당 2~3바이트를 차지하므로 최소 4바이트 이상이어야 2글자 이상임)
        if (strlen(user_input) < 4) {
            printf("? 경고: 너무 짧습니다. 2글자 이상 입력해야 합니다. 다시 입력해 주세요!\n");
            continue;
        }

        // 4. 규칙 2: 끝말이 이어지는지 확인 (첫 턴이 아닐 때만)
        if (word_count > 0) {
            // 한글 초성/중성/종성 구조상 바이트 단위 비교를 위해 UTF-8 기준 마지막 글자(3바이트)와 첫 글자(3바이트)를 비교합니다.
            // 아래 방식은 일반적인 개발 환경(UTF-8)에서 작동하는 간이 검증 로직입니다.
            int curr_len = strlen(current_word);
            
            // 이전 단어의 마지막 3바이트와 새 단어의 첫 3바이트 비교
            if (strncmp(&current_word[curr_len - 3], user_input, 3) != 0) {
                printf("? 경고: 끝말이 이어지지 않습니다. 다시 입력해 주세요!\n");
                continue;
            }
        }

        // 5. 규칙 3: 중복 단어 확인
        int is_duplicate = 0;
        for (int i = 0; i < word_count; i++) {
            if (strcmp(used_words[i], user_input) == 0) {
                is_duplicate = 1;
                break;
            }
        }
        if (is_duplicate) {
            printf("? 경고: 이미 사용된 단어입니다. 다른 단어를 생각해 보세요!\n");
            continue;
        }

        // 6. 모든 규칙 통과 시 데이터 업데이트
        printf("? 통과!\n");
        strcpy(used_words[word_count], user_input); // 사용된 단어 목록에 저장
        strcpy(current_word, user_input);           // 현재 제시어 변경
        word_count++;
        turn_count++;
        
        if (word_count >= MAX_WORDS) {
            printf("\n? 대단합니다! 준비된 단어 저장 공간(%d개)을 모두 채워 게임을 종료합니다.\n", MAX_WORDS);
            break;
        }
    }

    return 0;
}
