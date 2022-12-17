#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <queue>
using namespace std;

#define MAX_SIZE 100
int alreadyExists = 0; //이미 존재하는 단어인지
int noExists = 0; //존재하지 않는 단어인지

typedef struct node
{
    char word[MAX_SIZE]; // 영어 단어
    char meaning[MAX_SIZE]; // 한글 뜻
    struct node *left;
    struct node *right;
}Node;

// 처음에 사전트리를 만들기 위해  파일을 읽어오기
FILE *checkReadFile(int argc, char *argv)
{
    if (argc != 2)
    {
        printf("Usage) ./a.out engkor.dat\n");
        exit(0);
    }

    FILE *fp = fopen(argv, "r");
    if (!fp)
    {
        fprintf(stderr, "%s 파일을 열 수 없습니다\n", argv);
        exit(0);
    }

    return (fp);
}

//새로운 노드 생성
Node *makeNewNode(char *word, char *meaning)
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->word, word);
    strcpy(newNode->meaning, meaning);
    newNode->left = NULL;
    newNode->right = NULL;

    return (newNode);
}

//새로운 노드 하나를 트리에 추가
void addNewNodeinTree(Node **root, char* tempWord, char* tempMeaning)
{
    alreadyExists = 0;

    if (!*root)
    {
        *root = makeNewNode(tempWord, tempMeaning);
        return ;
    }

    if (strcmp((*root)->word, tempWord) > 0)
        addNewNodeinTree(&((*root)->left), tempWord, tempMeaning);
    else if (strcmp((*root)->word, tempWord) < 0)
        addNewNodeinTree(&((*root)->right), tempWord, tempMeaning);
    else
    {
        printf("이미 존재하는 단어 입니다.\n");
        alreadyExists = 1;
        return ;
    }
}

//단어 사전 트리 만들기
Node *makeDicTree(FILE *fp, Node *root)
{
    printf("사전 준비중..\n");
    while (!feof(fp))
    {
        char tempWord[MAX_SIZE];
        char tempMeaning[MAX_SIZE];

        fgets(tempWord, sizeof(tempWord), fp); // 파일에서 한 줄 읽어오기
        fgets(tempMeaning, sizeof(tempMeaning), fp);
        tempWord[strlen(tempWord)-1] = '\0'; //fgets는 개행까지 받아서
        tempMeaning[strlen(tempMeaning)-1] = '\0';

        addNewNodeinTree(&root, tempWord, tempMeaning); // 트리에 추가
    }

    printf("사전이 준비되었습니다.\n");
    return (root);
}

//메뉴 출력
void printMenu()
{
    printf("=====Dictionary Menu=====\n");
    printf("1. 영한 사전 검색\n2. Leaf node 단어 출력\n3. 단어 추가\n4. 단어 삭제\n5. 종료\n");
    printf("=========================\n입력>> ");
}

//영한 검색
void searchEtoFindK(Node *root)
{
    if (!root)
    {
        printf("사전이 비어있습니다\n");
        return ;
    }

    getchar();
    printf("검색(영어): ");
    char searchWord[MAX_SIZE];
    scanf( "%[^\n]s", searchWord);
    getchar();

    while (root)
    {
        if (strcmp(searchWord, root->word) == 0)
        {
            printf("%s : %s\n", root->word, root->meaning);
            return ;
        }
        else if (strcmp(searchWord, root->word) < 0)
            root = root->left;
        else if (strcmp(searchWord, root->word) > 0)
            root = root->right;
    }
    printf("단어가 사전에 등록되어있지 않습니다.\n");
}

//leaf node 찾는 함수
void findLeafNode(Node *root)
{
    if (root == NULL)
        return ;

    if (root->left == NULL && root->right == NULL)
        printf("%s\n", root->word);
    findLeafNode(root->left);
    findLeafNode(root->right);
}

// 새로운 단어를 추가하기 위해서 파일 읽어오기
FILE *checkAddWordFile(char *argv)
{
    FILE *fp = fopen(argv, "a"); // 파일의 맨 끝에 쓰기 위해
    if (!fp)
    {
        fprintf(stderr, "%s 파일을 열 수 없습니다\n", argv);
        exit(0);
    }

    return (fp);
}

// 새로운 단어를 받아서 사전에  추가
void addWord(char *fname, Node *root)
{
    FILE *fp = checkAddWordFile(fname);

    getchar();
    char newWord[MAX_SIZE];
    char newMeaning[MAX_SIZE];
    printf("추가할 단어(영어): ");
    scanf( "%[^\n]s", newWord);
    getchar();
    printf("추가할 단어의 뜻(한글): ");
    scanf( "%[^\n]s", newMeaning);
    getchar();

    //현재 트리에 등록
    addNewNodeinTree(&root, newWord, newMeaning);
    //파일에 등록
    if (alreadyExists == 0)
    {
        fputs(newWord, fp);
        fputs("\n", fp);
        fputs(newMeaning, fp);
        fputs("\n", fp);

        printf("등록완료\n");
    }

    fclose(fp);
}

// 삭제할 단어가 있는지 없는지 파악
void searchDWord(Node *root, char *dWord)
{
    noExists = 0;

    if (!root)
    {
        printf("사전이 비어있습니다\n");
        return ;
    }

    while (root)
    {
        if (strcmp(dWord, root->word) == 0)
            return ;
        else if (strcmp(dWord, root->word) < 0)
            root = root->left;
        else if (strcmp(dWord, root->word) > 0)
            root = root->right;
    }

    printf("단어가 사전에 등록되어있지 않습니다.\n");
    noExists = 1;
}

//트리 삭제를 위한, 오른쪽 노드에서 가장 작은 값을 구하기 위해
Node *findMinNode(Node *root)
{
    while (root->left != NULL)
        root = root->left;

    return (root);
}

// 트리에서 노드 삭제
Node *deleteWordinTree(Node **root, char *dWord)
{
    if (*root == NULL)
        return (*root);

    if (strcmp(dWord, (*root)->word) < 0)
        (*root)->left = deleteWordinTree(&((*root)->left), dWord);
    else if (strcmp(dWord, (*root)->word) > 0)
        (*root)->right = deleteWordinTree(&((*root)->right), dWord);
    else
    {
        //leaf node 이거나 서브트리가 하나일 때
        if ((*root)->left == NULL)
        {
            Node *temp = *root;
            *root = (*root)->right;
            free(temp);
        }
        else if ((*root)->right == NULL)
        {
            Node *temp = *root;
            *root = (*root)->left;
            free(temp);
        }
        else // 서브트리를 2개 가지고 있을 때
        {
            Node *min;
            min = findMinNode((*root)->right);
            strcpy((*root)->word, min->word);
            strcpy((*root)->meaning, min->meaning);
            free(min);
            (*root)->right = deleteWordinTree(&((*root)->right), (*root)->word);
        }
    }
    return (*root);
}

// 노드 삭제를 위해 파일을 w로 읽어오기
FILE *checkDeleteWordFile(char *argv)
{
    FILE *fp = fopen(argv, "w");
    if (!fp)
    {
        fprintf(stderr, "%s 파일을 열 수 없습니다\n", argv);
        exit(0);
    }

    return (fp);
}

//삭제 완료된 트리를 다시 읽어서 파일에 저장
void resetFile(char *fname, Node *root)
{
    FILE *fp = checkDeleteWordFile(fname);

    queue<Node*> q;
    q.push(root);
    while (!q.empty())
    {
        root = q.front();

        fputs(root->word, fp);
        fputs("\n", fp);
        fputs(root->meaning, fp);
        fputs("\n", fp);

        q.pop();

        if (root->left)
            q.push(root->left);
        if (root->right)
            q.push(root->right);
    }

    fclose(fp);
}

//단어를 받아서 사전에서 삭제
void deleteWord(char *fname, Node *root)
{
    getchar();
    char dWord[MAX_SIZE];
    printf("삭제할 단어를 입력하세요(영어): ");
    scanf( "%[^\n]s", dWord);
    getchar();

    searchDWord(root, dWord);
    if (noExists == 0)
    {
        root = deleteWordinTree(&root, dWord);
        resetFile(fname,root);
        printf("삭제완료\n");
    }
}

//사전 실행 함수
void executeDic(char *fname, Node *root)
{
    int order;
    while (1)
    {
        printMenu();
        scanf("%d", &order);

        switch (order)
        {
            case 1:
                searchEtoFindK(root);
                break;
            case 2:
                findLeafNode(root);
                break;
            case 3:
                addWord(fname,root);
                break;
            case 4:
                deleteWord(fname, root);
                break;
            case 5:
                printf("사전을 종료합니다.\n");
                return ;
            default :
                printf("잘못된 입력 입니다.\n");
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    Node *root = NULL;

    FILE *fpR = checkReadFile(argc, argv[1]);
    root = makeDicTree(fpR,root); // 파일을 트리로 만들기
    fclose(fpR);

    executeDic(argv[1],root); // 사전 실행

    return (0);
}
