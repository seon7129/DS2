/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

// find min value in the right side of the key
struct TreeNode* findMinNode(struct TreeNode* root)
{
    while(root->left != NULL)
        root = root->left;

    return (root);
}

struct TreeNode* deleteNode(struct TreeNode* root, int key)
{
    // tree가 비어있을 때, key값을 찾을 수 없을 때
    if (root == NULL)
        return (root);

    // find key node
    if (key < root->val)
        root->left = deleteNode(root->left, key);
    else if (key > root->val)
        root->right = deleteNode(root->right, key);
    else // key노드를 찾았으면,
    {
        if (root->left == NULL && root->right == NULL) // key node가 leaf node일 때
            root = NULL;
        else if (root->left == NULL) // key node의 왼쪽이 null일 때
            root = root->right;
        else if (root->right == NULL) // key node의 오른쪽이 null일 때
            root = root->left;
        else // key node의 자식이 둘 다 있을 떄
        {
            struct TreeNode* min;
            min = findMinNode(root->right); // key노드의 오른쪽 노드에서 최솟값 찾기
            root->val = min->val;
            root->right = deleteNode(root->right, root->val); // 빠진 노드를 삭제.. 최종적으로 null으로 채워짐
        }
    }

    return (root);
}