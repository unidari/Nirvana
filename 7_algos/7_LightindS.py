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
        if value < self.value:
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

def solution(root):
    if root is None:
        return 0

    maximum = root.value
    left_value = solution(root.left)
    right_value = solution(root.right)

    if left_value > maximum:
        maximum = left_value

    if right_value > maximum:
        maximum = right_value

    return maximum

def main():
    root = TreeNode(1)
    root.insert(3)
    root.insert(5)
    root.insert(8)
    root.insert(10)
    root.insert(2)
    root.insert(6)
    root.insert(14)
    root.insert(15)
    root.insert(3)
    root.insert(0)
    root.insert(10)

    print("Ответ на вопрос приведённой задачи")
    print(solution(root))
    """
    root: TreeNode = TreeNode(1)
    """

    new_root=int(input("Введите корень для решения задачи вашего дерева "))
    tree = TreeNode(new_root)
    i = int(input("Введите количество узлов "))
    for n in range(i):
        node = int(input("Введите узел "))
        tree.insert(node)
        node = 0
    print(solution(tree))

if __name__ == "__main__":
    main()
