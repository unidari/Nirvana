from collections import deque
class TreeNode:
    def __init__(self,
                 value=0,
                 left=None,
                 right=None):
        self.value = value
        self.left = left
        self.right = right


def binary(root):
    def solution (left, right):
        if left is None and right is None: return True
        if left is None or right is None: return False
        else:
            return left.value == right.value and solution(left.left, right.right) and solution(left.right, right.left)
    return solution(root.left, root.right)

def main():
    node3_right_2 = TreeNode (4)
    node3_left_2 = TreeNode(3)
    node3_right_1 = TreeNode(3)
    node3_left_1 = TreeNode(4)
    node2_2 = TreeNode(2, node3_left_2, node3_right_2)
    node2_1 = TreeNode(2, node3_left_1, node3_right_1)
    node1 =TreeNode(1, node2_1, node2_2)
    print(binary(node1))


if __name__ == "__main__":
    main()