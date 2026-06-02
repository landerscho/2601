# 포켓몬스터 18개 타입 목록 (인덱스와 매칭)
TYPE_NAMES = [
    "노말", "불꽃", "물", "전기", "풀", "얼음", "격투", "독", "땅", 
    "비행", "에스퍼", "벌레", "바위", "고스트", "드래곤", "악", "강철", "페어리"
]

# 타입 상성표 (공격 타입이 행, 방어 타입이 열)
# 1.0: 보통, 2.0: 2배(효과가 굉장함), 0.5: 반감(효과가 별로임), 0.0: 무효(효과가 없음)
TYPE_CHART = [
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0.5, 0, 1, 1, 0.5, 1],       # 노말
    [1, 0.5, 0.5, 1, 2, 2, 1, 1, 1, 1, 1, 2, 0.5, 1, 0.5, 1, 2, 1],   # 불꽃
    [1, 2, 0.5, 1, 0.5, 1, 1, 1, 2, 1, 1, 1, 2, 1, 0.5, 1, 1, 1],     # 물
    [1, 1, 2, 0.5, 0.5, 1, 1, 1, 0, 2, 1, 1, 1, 1, 0.5, 1, 1, 1],     # 전기
    [1, 0.5, 2, 1, 0.5, 1, 1, 0.5, 2, 0.5, 1, 0.5, 2, 1, 0.5, 1, 0.5, 1], # 풀
    [1, 0.5, 0.5, 1, 2, 0.5, 1, 1, 2, 2, 1, 1, 1, 1, 2, 1, 0.5, 1],   # 얼음
    [2, 1, 1, 1, 1, 2, 1, 0.5, 1, 0.5, 0.5, 0.5, 2, 0, 1, 2, 2, 0.5], # 격투
    [1, 1, 1, 1, 2, 1, 1, 0.5, 0.5, 1, 1, 1, 0.5, 0.5, 1, 1, 0, 2],   # 독
    [1, 2, 1, 2, 0.5, 1, 1, 2, 1, 0, 1, 0.5, 2, 1, 1, 1, 2, 1],       # 땅
    [1, 1, 1, 0.5, 2, 1, 2, 1, 1, 1, 1, 2, 0.5, 1, 1, 1, 0.5, 1],     # 비행
    [1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 0.5, 1, 1, 1, 1, 0, 0.5, 1],       # 에스퍼
    [1, 0.5, 1, 1, 2, 1, 0.5, 0.5, 1, 0.5, 2, 1, 1, 0.5, 1, 2, 0.5, 0.5], # 벌레
    [1, 2, 1, 1, 1, 2, 0.5, 1, 0.5, 2, 1, 2, 1, 1, 1, 1, 0.5, 1],     # 바위
    [0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 0.5, 1, 1],         # 고스트
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 0.5, 0],         # 드래곤
    [1, 1, 1, 1, 1, 1, 0.5, 1, 1, 1, 2, 1, 1, 2, 1, 0.5, 1, 0.5],     # 악
    [1, 0.5, 0.5, 0.5, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 0.5, 2],   # 강철
    [1, 0.5, 1, 1, 1, 1, 2, 0.5, 1, 1, 1, 1, 1, 1, 2, 2, 0.5, 1]      # 페어리
]

def get_type_multiplier(attack_type, defend_type1, defend_type2=None):
    """
    공격 타입과 방어 타입(최대 2개)을 받아 최종 데미지 배율을 계산합니다.
    """
    if attack_type not in TYPE_NAMES or defend_type1 not in TYPE_NAMES:
        return "잘못된 타입이 입력되었습니다."
    
    # 타입 이름을 인덱스로 변환
    att_idx = TYPE_NAMES.index(attack_type)
    def1_idx = TYPE_NAMES.index(defend_type1)
    
    # 첫 번째 방어 타입에 대한 배율
    multiplier = TYPE_CHART[att_idx][def1_idx]
    
    # 두 번째 방어 타입이 있다면 배율을 곱해줌 (이중 타입 계산)
    if defend_type2 and defend_type2 in TYPE_NAMES and defend_type2 != defend_type1:
        def2_idx = TYPE_NAMES.index(defend_type2)
        multiplier *= TYPE_CHART[att_idx][def2_idx]
        
    return multiplier

def print_result(attack, def1, def2, multiplier):
    defense_str = f"{def1}/{def2}" if def2 else f"{def1}"
    print(f"\n[{attack}] 타입으로 [{defense_str}] 타입 공격 시:")
    
    if multiplier > 1:
        print(f"👉 배율: x{multiplier} (효과가 굉장했다!)")
    elif multiplier == 0:
        print(f"👉 배율: x{multiplier} (효과가 없는 것 같다...)")
    elif multiplier < 1:
        print(f"👉 배율: x{multiplier} (효과가 별로인 듯하다...)")
    else:
        print(f"👉 배율: x{multiplier} (보통이다.)")

def main():
    print("🔥 포켓몬스터 타입 상성 계산기 💧")
    print("가능한 타입:", ", ".join(TYPE_NAMES))
    print("-" * 40)
    
    while True:
        attack = input("\n공격할 타입을 입력하세요 (종료하려면 q 입력): ").strip()
        if attack.lower() == 'q':
            break
            
        def1 = input("방어할 첫 번째 타입을 입력하세요: ").strip()
        def2 = input("방어할 두 번째 타입을 입력하세요 (없으면 엔터): ").strip()
        
        # 빈 문자열 처리
        def2 = def2 if def2 != "" else None
        
        try:
            multiplier = get_type_multiplier(attack, def1, def2)
            if type(multiplier) == str: # 에러 메시지 반환 시
                print(multiplier)
            else:
                print_result(attack, def1, def2, multiplier)
        except Exception as e:
            print("오류가 발생했습니다. 타입을 정확히 입력해 주세요.")

if __name__ == "__main__":
    main()
