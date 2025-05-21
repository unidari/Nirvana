class TreeNode:
    def __init__(self,
                 value,
                 left,
                 right):

        self.value = value
        self.left = left
        self.right = right


def anagram_trees(root_1: TreeNode, root_2: TreeNode):
    if not root_1 and not root_2: return True
    if not root_1 or not root_2: return False

    return anagram_trees(root_1.left, root_2.right) and anagram_trees(root_1.right, root_2.left)


def input_tree():
    value = input("Введите значение узла (или '-' для пустого узла): ")
    if value == '-': return None
    print(f"Левый потомок узла '{value}':")
    left = input_tree()
    print(f"Правый потомок узла '{value}':")
    right = input_tree()

    return TreeNode(value, left, right)

def solution(root):
    if root:
        print("Введите первое дерево")
        tree1 = input_tree()
        print("Введите второе дерево")
        tree2 = input_tree()

        result = anagram_trees(tree1, tree2)
        print("Деревья являются анаграммами" if result else "Деревья НЕ являются анаграммами")
    else: return False

def main():
    root = int(input("Введите значения корня древа: "))
    solution(root)

if __name__ == "__main__":
    main()