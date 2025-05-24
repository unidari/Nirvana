class TreeNode:
    def __init__(self,
                 value=0,
                 left=None,
                 right=None):
        self.value = value
        self.left = left
        self.right = right

    def insert(self, value):
        # Если значение меньше текущего, вставляем в левое поддерево
        if value <= self.value:
            if self.left:
                self.left.insert(value)  # Рекурсивно ищем место в левом поддереве
            else:
                self.left = TreeNode(value)  # Вставляем новый узел
        # Если значение больше текущего, вставляем в правое поддерево
        elif value > self.value:
            if self.right:
                self.right.insert(value)  # Рекурсивно ищем место в правом поддереве
            else:
                self.right = TreeNode(value)  # Вставляем новый узел


def maxPath(root):
    max_sum = -float('inf')
    def solution(node):
        nonlocal max_sum
        if not node: return 0
        leftMax = max(solution(node.left), 0)
        rightMax = max(solution(node.right), 0)
        curSumm = (node.value) + leftMax + rightMax
        max_sum = max(max_sum, curSumm)
        return (node.value + max(leftMax, rightMax))
    solution(root)
    return max_sum

def tree():
    val = int(input("введите значение узла: "))
    if val == 0: return None
    node = TreeNode(val)
    left = input(f"Добавить левого для {val}? (1 - да, 0 - нет): ").lower()
    if left == 'да':
        node.left = tree()
    right = input(f"Добавить правого для {val}? (1 - да, 0 - нет): ").lower()
    if right == 'да':
        node.right = tree()
    return node

def main():
    'Решения для приведённых примеров'
    root_1 = TreeNode(1, TreeNode(1), TreeNode(2))
    print(maxPath(root_1))
    root_2 = TreeNode(-5, TreeNode(1), TreeNode(7, TreeNode(2), TreeNode(3)))
    print(maxPath(root_2))

    root = tree()
    print(maxPath(root))

if __name__ == "__main__":
    main()