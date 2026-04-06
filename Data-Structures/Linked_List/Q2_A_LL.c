//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 2 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2); // 구현해야 할 함수!

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll1, ll2; // 이번엔 리스트가 두 개!
	int c, i, j;
	c = 1;

	// 두 리스트 모두 빈 상태로 초기화
	ll1.head = NULL;
	ll1.size = 0;

	ll2.head = NULL;
	ll2.size = 0;

	printf("1: Insert an integer to the linked list 1:\n");
	printf("2: Insert an integer to the linked list 2:\n");
	printf("3: Create the alternate merged linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list 1: ");
			scanf("%d", &i);
			j = insertNode(&ll1, ll1.size, i); // ll1.size = 맨 끝 인덱스 → 맨 뒤에 추가
			printf("Linked list 1: ");
			printList(&ll1);
			break;
		case 2:
			printf("Input an integer that you want to add to the linked list 2: ");
			scanf("%d", &i);
			j = insertNode(&ll2, ll2.size, i); // ll2도 마찬가지로 맨 뒤에 추가
			printf("Linked list 2: ");
			printList(&ll2);
			break;
		case 3:
		    printf("The resulting linked lists after merging the given linked list are:\n");
			alternateMergeLinkedList(&ll1, &ll2); // 두 리스트를 교차 병합
			printf("The resulting linked list 1: ");
			printList(&ll1);
			printf("The resulting linked list 2: ");
			printList(&ll2);
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		case 0:
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

/*
 * [구현해야 할 함수]
 * alternateMergeLinkedList: ll1과 ll2를 교차(alternate)로 병합
 *
 * 예)
 * ll1: 1 -> 2 -> 3 -> 4 -> 5
 * ll2: 6 -> 7 -> 8
 *
 * 결과:
 * ll1: 1 -> 6 -> 2 -> 7 -> 3 -> 8 -> 4 -> 5  (ll1에 교차로 합쳐짐)
 * ll2: (비어있음)                               (ll2의 노드들은 ll1으로 이동됨)
 *
 * 전략:
 * - ll1의 노드 하나, ll2의 노드 하나를 번갈아가며 ll1에 끼워 넣음
 * - ll2가 먼저 끝나면 나머지 ll1은 그대로 둠
 * - ll1이 먼저 끝나면 ll2의 남은 노드들을 ll1 뒤에 이어 붙임
 * - 삽입할 때마다 ll1의 삽입 위치 인덱스가 2씩 증가함 (한 칸 건너뛰며 삽입)
 */
void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2)
{
	// 아. 정렬 안 하고 합치기만 하면 되는구나!
	//이거 링크드 리스트임
	int pos =1; //ll1에서 삽입할 위치

	while (ll2->size > 0) {
		ListNode* temp = findNode(ll2, 0);
		int val = temp ->item; //먼저 값 저장!
		removeNode(ll2, 0); //메모리 free를 위해. 근데 여기서 temp가 가리키는 값이 free가 돼버리므로 미리 저장해주어야 함
		insertNode(ll1, pos, val);
		pos += 2;
		if (pos > ll1->size) // 현재 코드상 ll2가 짧을때는 문제 없음
		pos = ll1->size; // 그러나 ll1이 짧을때 예외처리

	}

}

///////////////////////////////////////////////////////////////////////////////////

// 아래 함수들은 Q1과 동일 — Q1 주석 참고

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}

int removeNode (LinkedList *ll, int index){

	ListNode *pre, *cur; 

	if (ll == NULL || index <0 || index >= ll->size)
		return -1;

	if (index == 0) {
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;
		return 0;

	}
	
}
