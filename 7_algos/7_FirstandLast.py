def findFirst(nums, target):
    left, right = 0, len(nums) - 1
    first_occurrence = -1

    while left <= right:
        mid = (left + right) // 2
        if nums[mid] == target:
            first_occurrence = mid
            right = mid - 1  # Продолжаем искать в левой части
        elif nums[mid] < target:
            left = mid + 1
        else:
            right = mid - 1

    return first_occurrence


def findLast(nums, target):
    left, right = 0, len(nums) - 1
    last_occurrence = -1

    while left <= right:
        mid = (left + right) // 2
        if nums[mid] == target:
            last_occurrence = mid
            left = mid + 1  # Продолжаем искать в правой части
        elif nums[mid] < target:
            left = mid + 1
        else:
            right = mid - 1

    return last_occurrence


def solution(nums, target):
    first = findFirst(nums, target)
    last = findLast(nums, target)

    if first == -1: return "Element not found in the array"
    else:
        return f"The first occurrence of element {target} is located at index {first}\n" f"The last occurrence of element {target} is located at index {last}"

def main():
    nums = [2, 5, 5, 5, 6, 6, 8, 9, 9, 9]
    target = 5
    print(solution(nums, target))

    test = [int(i) for i in (input("Введите свои числа для списка ")).split()]
    targetTest = int(input('Введите числа-цель '))
    print(solution(test, targetTest))

if __name__ == "__main__":
    main()