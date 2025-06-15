def solution(candidates, k):

    def backtrack(s, summa):

        if summa == k:
            return True
        if summa > k:
            return False

        for i in range(s, len(candidates)):
            if backtrack(i + 1, summa + candidates[i]):
                return True
        return False

    return backtrack(0, 0)


def main():
    n, k = map(int, input().split())

    candidates = list(map(int, input().split()))
    print("YES" if solution(candidates, k) else "NO")

if __name__ == "__main__":
    main()