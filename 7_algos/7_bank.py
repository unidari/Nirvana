def solution(m, monetss):
    monetss.sort(reverse=True)
    all = {}
    def backTracking(m, start):
        if m == 0: return 1
        if (m, start) in all: return all[(m, start)]

        count = 0
        for i in range(start, len(monetss)):
            if monetss[i] <= m:
                count += backTracking(m - monetss[i], i)
        all[(m, start)] = count
        return count
    return backTracking(m, 0)

def main():
    m = int(input())
    n = int(input())
    monetss = list(map(int, input().split()))

    print(solution(m, monetss))

if __name__ == "__main__":
    main()