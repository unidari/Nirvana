class TreeNode:
    def __init__(self,
                 value=0,
                 left=None,
                 right=None):
        self.value = value
        self.left = left
        self.right = right


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

def pre_order(node):
    if node:
        print(node.value)
        pre_order(node.left)
        pre_order(node.right)

def main():
    node12 = TreeNode (1)
    node11 = TreeNode(0)
    node10 = TreeNode(3)
    node9 = TreeNode(15)
    node8 = TreeNode(14)
    node7 = TreeNode(6, node11, node12)
    node6 = TreeNode (2)
    node5 = TreeNode(10, None, node10)
    node4 = TreeNode(8, node8, node9)
    node3 = TreeNode(5, node6, node7)
    node2 = TreeNode(3, node4, node5)
    node1 = TreeNode(1, node2, node3)
    print(solution(node1))

if __name__ == "__main__":
    main()
