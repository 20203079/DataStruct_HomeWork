#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


/* AVL Tree 구현
	ㄴ> AVL Tree란 Binary Search Tree(BST)에 조건이 하나 추가된 Tree로 조건은 다음과 같음
	조건 : Tree 내에 존재하는 모든 노드의 왼쪽 subTree의 height과 오른쪽 subTree의 height의 차이(BlanceFactor)의 절댓값은 항상 1보다 작거나 같아야 한다.
*/

typedef struct node {	// 노드의 구성 => 1. 데이터가 담기는 공간 2. 왼쪽 하위노드를 가리키는 포인터 변수 3. 오른쪽 하위노드를 가리키는 포인터 변수
	int data;
	struct node* left;
	struct node* right;
}Tree;

Tree* makeNode(){	// Tree의 노드를 생성해 주는 함수
	Tree* tmp= (Tree*)malloc(sizeof(Tree));
	tmp->left = NULL; // 특정 노드의 하위노드의 값이 없을 때 발생하는 연산오류를 방지하기 위해 기본값을 NULL로 초기화
	tmp->right = NULL; // 특정 노드의 하위노드의 값이 없을 때 발생하는 연산오류를 방지하기 위해 기본값을 NULL로 초기화

	return tmp; // 만든 노드의 주소를 반환
}

void insert_bst(Tree** root, int data){		// Binary Tree에 노드를 삽입할 때, Binary Search Tree(BST)의 형식으로 노드를 삽입해 주는 함수(노드의 값은 파라미터로 받아온 data의 값)
	if (tree_size(*root) >= 50){ // Tree 내에 존재하는 노드의 개수는 50개 이하가 되도록 삽입 제한
		printf("insert is failed.\n");
		return;
	}

	if (*root == NULL){	// 비어있는 공간일 경우 노드 삽입(왼쪽 하위노드 또는 오른쪽 하위노드는 기본적으로 NULL값으로 초기화했었음)
		(*root) = makeNode();
		(*root)->data = data;
	}

	if ((*root)->data < data) // 삽입하고자 하는 노드가 Tree 내에 존재하는 특정 노드보다 큰 경우
		insert_bst(&((*root)->right), data); // ㄴ> 특정 노드의 오른쪽 하위노드랑 값을 비교하도록 함(특정 노드 기준 높이가 1에 해당하는 하위노드랑 비교)

	if ((*root)->data > data) // 삽입하고자 하는 노드가 Tree 내에 존재하는 특정 노드보다 작은 경우
		insert_bst(&((*root)->left), data); // ㄴ> 특정 노드의 왼쪽 하위노드랑 값을 비교하도록 함(특정 노드 기준 높이가 1에 해당하는 하위노드랑 비교)
}

int node_height(Tree* root){	// Tree 내에 존재하는 subTree의 height를 계산해주는 함수
	if (root->left != NULL && root->right == NULL) // 노드의 왼쪽 하위노드는 존재하고, 오른쪽 하위노드는 존재하지 않는 경우
		return 1 + node_height(root->left);
	else if (root->left == NULL && root->right != NULL) //노드의 왼쪽 하위노드는 존재하지 않고, 오른쪽 하위노드는 존재하는 경우
		return 1 + node_height(root->right);
	else if (root->left == NULL && root->right == NULL) // 노드의 하위노드는 존재하지 않는 경우
		return 0;
	else // 노드의 왼쪽 하위노드와 오른쪽 하위노드가 모두 존재하는 경우
		return (1 + ((node_height(root->left)) >= (node_height(root->right)) ? node_height(root->left) : node_height(root->right)));
}

int node_balanceFactor(Tree* root){		// 특정 노드의 왼쪽 subTree중 가장 큰 subTree의 height과 오른쪽 subTree중 가장 큰 subTree의 height의 차이(BlanceFactor)를 구해주는 함수
										// ㄴ> height의 차이 : (노드의 왼쪽 subTree중 가장 큰 subTree의 height) - (노드의 오른쪽 subTree중 가장 큰 subTree의 height) 
	int bf = 0; // bf = Blancefactor를 의미
	if (root->left != NULL && root->right == NULL){ // 노드의 왼쪽 하위노드는 존재하고, 오른쪽 하위노드는 존재하지 않는 경우
		bf = (node_height(root));
	}
	else if (root->left == NULL && root->right != NULL){ //노드의 왼쪽 하위노드는 존재하지 않고, 오른쪽 하위노드는 존재하는 경우
		bf = (node_height(root));
	}
	else if (root->left == NULL && root->right == NULL) // 노드의 하위노드는 존재하지 않는 경우
		bf = 0;
	else // 노드의 왼쪽 하위노드와 오른쪽 하위노드가 모두 존재하는 경우
		bf = (node_height(root->left) - node_height(root->right));

	return bf;
}

Tree* ll_rotate(Tree** root){	// 특정 노드를 A, A의 왼쪽 하위노드를 B, B의 왼쪽 하위노드를 C라고 한다면 Tree의 구조를 다음과 같이 바뀌게 해주는 함수
								// ㄴ> 구조 : B의 왼쪽 하위노드는 C, B의 오른쪽 하위노드는 A
	Tree* tmpB = (*root)->left;
	(*root)->left = tmpB->right;
	tmpB->right = *root;

	return tmpB;
}

Tree* rr_rotate(Tree** root){	// 특정 노드를 A, A의 오른쪽 하위노드를 B, B의 오른쪽 하위노드를 C라고 한다면 Tree의 구조를 다음과 같이 바뀌게 해주는 함수
								// ㄴ> 구조 : B의 왼쪽 하위노드는 A, B의 오른쪽 하위노드는 C
	Tree* tmpB = (*root)->right;
	(*root)->right = tmpB->left;
	tmpB->left = *root;

	return tmpB;
}

Tree* lr_rotate(Tree** root){	// 특정 노드를 A, A의 왼쪽하위노드를 B, B의 오른쪽 하위노드를 C라고 한다면 Tree의 구조를 다음과 같이 바뀌게 해주는 함수
								// ㄴ> 구조 : C의 왼쪽 하위노드는 B, C의 오른쪽 하위노드는 A
	Tree* tmpB = (*root)->left;
	Tree* tmpC = (*root)->left->right;
	tmpB->right = tmpC->left;
	(*root)->left = tmpC->right;
	tmpC->left = tmpB;
	tmpC->right = *root;

	return tmpC;
}

Tree* rl_rotate(Tree** root){	// 특정 노드를 A, A의 오른쪽 하위노드를 B, B의 왼쪽 하위노드를 C라고 한다면 Tree의 구조를 다음과 같이 바뀌게 해주는 함수
								// ㄴ> 구조 : C의 왼쪽 하위노드는 A, C의 오른쪽 하위노드는 B
	Tree* tmpB = (*root)->right;
	Tree* tmpC = (*root)->right->left;
	tmpB->left = tmpC->right;
	(*root)->right = tmpC->left;
	tmpC->left = (*root);
	tmpC->right = tmpB;

	return tmpC;
}

void avl_sort(Tree** root){		// Tree를 순회(Postorder) 하면서 BlanceFactor가 1보다 크거나 -1보다 작은 경우, Tree가 AVL Tree가 되도록 Tree를 재정렬 시켜주는 함수
	if ((*root)->left != NULL) // 노드의 왼쪽 하위노드의 값이 더 있을 때
		avl_sort(&((*root)->left));
	if ((*root)->right != NULL) // 노드의 오른쪽 하위노드의 값이 더 있을때
		avl_sort(&((*root)->right));
	if (node_balanceFactor(*root) > 1){ // 1보다 큰 BlanceFactor를 가지는 노드가 존재하는 경우({(노드의 왼쪽 subTree중 가장 큰 subTree의 height) - (노드의 오른쪽 subTree중 가장 큰 subTree의 height)} > 1)
		if (node_balanceFactor((*root)->left) >= 0) // ㄴ> 위의 노드의 왼쪽 하위노드의 왼쪽 subTree중 가장 큰 subTree의 height이 위의 노드의 왼쪽 하위노드의 오른쪽 subTree중 가장 큰 subTree의 height보다 크거나 같은 경우
			*root = ll_rotate(&(*root));	
		else
			*root = lr_rotate(&(*root));
	}
	else if (node_balanceFactor(*root) < -1){ // -1보다 작은 BlanceFactor를 가지는 노드가 존재하는 경우({(노드의 왼쪽 subTree중 가장 큰 subTree의 height) - (노드의 오른쪽 subTree중 가장 큰 subTree의 height)} < -1)
		if (node_balanceFactor((*root)->right) <= 0) // ㄴ> 위의 노드의 오른쪽 하위노드의 왼쪽 subTree중 가장 큰 subTree의 height이 위의 노드의 오른쪽 하위노드의 오른쪽 subTree중 가장 큰 subTree의 height보다 작거나 같은 경우
			*root = rr_rotate(&(*root));
		else
			*root = rl_rotate(&(*root));
	}
}

void pre_traversal(Tree** root){	// Tree를 Preorder 하면서 노드를 출력해 주는 함수
	printf("%d ", (*root)->data);
	if ((*root)->left != NULL)
		pre_traversal(&((*root)->left));
	if ((*root)->right != NULL)
		pre_traversal(&((*root)->right));
}

int tree_size(Tree* root){		// Tree 내에 존재하는 노드 개수를 반환해 주는 함수
	if (root == NULL) // Tree 내에 존재하는 노드가 1개도 없는 경우
		return 0;
	else if (root->left == NULL && root->right == NULL) // 노드가 단말노드인 경우
		return 1;
	else // 노드의 하위노드가 존재하는 경우
		return 1 + (tree_size(root->left) + tree_size(root->right));
}

Tree* minNode(Tree* root){		// Tree의 특정 subtTree 내에 존재하는 가장 작은 노드의 주소를 반환해 주는 함수
	if (root->left != NULL) return minNode(root->left);
	else return root;
}

void delNode(Tree** root, int data){	// Tree 내에 파라미터로 받아온 data의 값과 같은 노드가 있다면 제거해 주는 함수

	if ((*root)->data > data) // Tree 내에 존재하는 특정 노드보다 제거하고자 하는 노드가 작은 경우
		delNode(&((*root)->left), data); // ㄴ> 특정 노드의 왼쪽 하위노드랑 값을 비교하도록 함(특정 노드 기준 높이가 1에 해당하는 하위노드랑 비교)
	else if ((*root)->data < data) // Tree 내에 존재하는 특정 노드보다 제거하고자 하는 노드가 큰 경우
		delNode(&((*root)->right), data); // ㄴ> 특정 노드의 오른쪽 하위노드랑 값을 비교하도록 함(특정 노드 기준 높이가 1에 해당하는 하위노드랑 비교)
	else{ // Tree 내에 존재하는 특정 노드가 제거하고자 하는 노드와 같은 경우
		if ((*root)->left == NULL && (*root)->right == NULL){ // 제거하고자 하는 노드의 하위노드는 존재하지 않는 경우
			free(*root);
			*root = NULL;
		}
		else if ((*root)->left != NULL && (*root)->right == NULL){ // 제거하고자 하는 노드의 왼쪽 하위노드는 존재하고, 오른쪽 하위노드는 존재하지 않는 경우
			Tree* tmp = *root;
			(*root) = (*root)->left;
			free(tmp);
			
		}
		else if ((*root)->left == NULL && (*root)->right != NULL){ // 제거하고자 하는 노드의 왼쪽 하위노드는 존재하지 않고, 오른쪽 하위노드는 존재하는 경우
			Tree *tmp = *root;
			(*root) = (*root)->right;
			free(tmp);
		}
		else { // 제거하고자 하는 노드의 왼쪽 하위노드와 오른쪽 하위노드가 모두 존재하는 경우
			Tree * minnode = minNode((*root)->right);
			(*root)->data = minnode->data;
			delNode(&((*root)->right), minnode->data);
		}
	}
}

void clear(Tree** root){	// 프로그램을 종료할 때 Tree 내에 존재하는 모든 노드(malloc을 통해 만들어졌음), 즉 할당된 모든 메모리를 해제시켜주는 함수
	// Tree를 순회(Postorder)하면서 메모리 해제
	if ((*root)->left != NULL)
		clear(&((*root)->left));
	if ((*root)->right != NULL)
		clear(&((*root)->right));
	free(*root);
}

void main(){	// Tree 내에 들어갈 수 있는 노드의 개수는 최대 50개
	Tree* root = NULL; // Tree의 root를 생성
	int i = 0, node = 0; // 반복문을 돌리기 위한 i라는 변수 선언 및 초기화, Tree의 입력과 제거를 위한 node 변수 선언 및 초기화
	printf("Inser node to AVL tree:\n"); 
	for (i = 0; i < 9; i++){
		scanf("%d", &node);
		insert_bst(&root, node);
	}

	printf("\n\nPreorder traversal of the constructed AVL tree is\n");
	pre_traversal(&root);
	
	printf("\nPreorder traversal after deletion of ");	scanf("%d", &node); 
	delNode(&root, node); 
	avl_sort(&root);

	pre_traversal(&root);	printf("\n");
	clear(&root);
}