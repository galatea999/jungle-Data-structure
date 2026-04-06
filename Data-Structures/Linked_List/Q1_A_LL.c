//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>   // printf, scanf 같은 입출력 함수를 쓰기 위한 헤더
#include <stdlib.h>  // malloc, free 같은 메모리 관리 함수를 쓰기 위한 헤더

//////////////////////////////////////////////////////////////////////////////////

/*
 * [연결 리스트(Linked List)란?]
 * 배열처럼 데이터를 순서대로 저장하는 자료구조인데,
 * 배열과 달리 각 데이터가 "다음 데이터의 위치(주소)"를 함께 들고 있어요.
 * 마치 보물찾기처럼, 각 단계에서 "다음 단서의 위치"를 알려주는 방식입니다.
 *
 * 구조: [데이터|다음주소] -> [데이터|다음주소] -> [데이터|NULL]
 *                                                         ↑
 *                                              NULL = 더 이상 다음이 없다는 표시
 */

/* 노드(Node): 연결 리스트의 한 칸(한 데이터)을 나타내는 구조체
 * struct(구조체)는 서로 관련된 변수들을 하나로 묶은 것입니다.
 * 예: 학생 정보를 (이름, 학번, 학점)으로 묶는 것처럼요.
 */
typedef struct _listnode{
	int item;               // 이 노드가 실제로 저장하는 정수값
	struct _listnode *next; // 다음 노드의 "주소"를 저장하는 포인터
	                        // 포인터(*)란 변수가 아니라 변수의 "주소"를 저장하는 공간
} ListNode;			// You should not change the definition of ListNode

/* 연결 리스트 전체를 관리하는 구조체
 * 리스트의 "입구(head)"와 "크기(size)"를 관리합니다.
 */
typedef struct _linkedlist{
	int size;       // 현재 리스트에 몇 개의 노드가 있는지
	ListNode *head; // 첫 번째 노드의 주소 (여기서부터 따라가면 전체를 순회할 수 있음)
} LinkedList;			// You should not change the definition of LinkedList 
//struct _linkedlist 쓰기 귀찮음 => typedef LinkedList로 별명 달아준것


///////////////////////// function prototypes ////////////////////////////////////
// 함수 선언부: "이런 함수들이 아래에 정의되어 있어요"라고 컴파일러에게 미리 알려주는 것

//You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item); // 정렬된 위치에 삽입 (직접 구현해야 함!)

void printList(LinkedList *ll);              // 리스트 전체 출력
void removeAllItems(LinkedList *ll);         // 리스트 전체 삭제
ListNode *findNode(LinkedList *ll, int index);          // index번째 노드 찾기
int insertNode(LinkedList *ll, int index, int value);   // 특정 위치에 노드 삽입
int removeNode(LinkedList *ll, int index);              // 특정 위치의 노드 삭제


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll; // 연결 리스트 변수 선언
	int c, i, j;   // c: 메뉴 선택, i: 입력한 정수, j: 삽입된 인덱스
	c = 1;         // 루프를 바로 시작하기 위해 c를 1로 초기화

	// 연결 리스트를 빈 상태로 초기화
	// head가 NULL이면 "아직 아무 노드도 없다"는 의미
	ll.head = NULL;
	ll.size = 0;

	// 메뉴 출력
	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	// c가 0이 될 때까지 반복 (0 입력 시 종료)
	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c); // 사용자 입력을 c에 저장 (&는 "c의 주소"를 의미)

		switch (c) // c의 값에 따라 다른 동작 수행
		{
		case 1:
			// 정수를 입력받아 정렬된 위치에 삽입
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i); // 삽입 후 삽입된 인덱스를 j에 저장
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			// 가장 최근에 입력한 값이 몇 번째 인덱스에 들어갔는지 출력
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			// 현재 리스트를 출력하고 모든 데이터를 메모리에서 해제
			printf("The resulting sorted linked list is: ");
			printList(&ll);
			removeAllItems(&ll); // 메모리 누수 방지를 위해 사용한 메모리 반환
			break;
		case 0:
			removeAllItems(&ll); // 종료 전 메모리 정리
			break;
		default:
			printf("Choice unknown;\n"); // 1/2/3/0 외의 값 입력 시
			break;
		}


	}
	return 0; // main이 0을 반환하면 "정상 종료"를 의미
}

//////////////////////////////////////////////////////////////////////////////////

/*
 * [구현해야 할 함수]
 * insertSortedLL: 리스트가 항상 오름차순을 유지하도록 올바른 위치에 item을 삽입
 * 예) 리스트: 1 -> 3 -> 5, item = 4 삽입 시
 *     결과:  1 -> 3 -> 4 -> 5
 *
 * 반환값: 삽입된 위치의 인덱스 (0부터 시작)
 */
int insertSortedLL(LinkedList *ll, int item) //linkedList 구조체에는 길이와 head만 있음
{
	//item이 들어왔을때 새 노드를 생성해야 함
	
		// 오름차순을 만들려면, 기존 리스트를 돌면서 item과 비교해야함
		// 만약 head가 null이면 첫값에 추가함
		// head부터 next를 따라가며 비교. 
		// 크거나 같은 값을 찾으면 거기서 멈추고 그걸 next로 삼음 
		// 근데 문제는 이걸 C언어로 어떻게 쓰냐고. 뭘 어떡해.. 도움받고 따라해야지 뭐.
 

		//인덱스와 커서를 선언
		int index = 0;
		ListNode *cur = ll->head; // 리스트노드의 포인터인 커서를 만들어서, 먼저 head를 가리킴

		// 들어갈 자리 찾기
		while (cur != NULL) {
			if (item = cur->item){
			return -1;
			}
			
			if (item < cur->item) //현재 커서의 값이 새로 추가하려는 item보다 크거나 같은 값을 만나면
			break; //거기가 넣는 포인트임
			cur = cur->next; //아니면 계속 탐색해
			index++; //index 없이 cur만으로는 몇번째인지를 알 수 없음
		}

		insertNode(ll, index, item);
		return index;

	
}

///////////////////////////////////////////////////////////////////////////////////

/*
 * printList: 리스트의 모든 노드를 처음부터 끝까지 출력
 * - cur(current) 포인터로 head부터 시작해서 next를 따라 끝까지 이동
 * - cur가 NULL이 되면 리스트 끝에 도달한 것
 */
void printList(LinkedList *ll){

	ListNode *cur; // 현재 가리키고 있는 노드의 포인터
	if (ll == NULL) // 리스트 자체가 없으면 아무것도 안 함
		return;
	cur = ll->head; // 첫 번째 노드부터 시작 (->는 포인터로 구조체 멤버에 접근)

	if (cur == NULL)
		printf("Empty"); // 노드가 하나도 없으면 "Empty" 출력
	while (cur != NULL) // cur이 NULL이 아닌 동안 (끝에 도달하지 않은 동안) 반복
	{
		printf("%d ", cur->item); // 현재 노드의 값 출력
		cur = cur->next;          // 다음 노드로 이동 (포인터를 다음 노드 주소로 업데이트)
	}
	printf("\n");
}


/*
 * removeAllItems: 리스트의 모든 노드를 메모리에서 해제(삭제)
 * - malloc으로 할당한 메모리는 free로 직접 해제해야 함 (C는 자동으로 해주지 않음!)
 * - tmp에 다음 노드 주소를 저장한 뒤 cur를 free해야 안전함
 *   (free한 후에는 cur->next에 접근할 수 없으므로)
 */
void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head; // 첫 번째 노드부터 시작
	ListNode *tmp;            // 다음 노드 주소를 임시 저장할 포인터

	while (cur != NULL){
		tmp = cur->next; // ① 먼저 다음 노드 주소를 tmp에 저장
		free(cur);       // ② 현재 노드 메모리 해제
		cur = tmp;       // ③ 저장해둔 다음 노드로 이동
	}
	ll->head = NULL; // head를 NULL로 초기화 (리스트가 비었음을 표시)
	ll->size = 0;    // 크기도 0으로 초기화
}


/*
 * findNode: index번째(0부터 시작) 노드를 찾아서 그 주소를 반환
 * - 예) index=2이면 head -> next -> next 를 반환 (세 번째 노드)
 * - 유효하지 않은 index이면 NULL 반환
 */
ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp; // 탐색용 임시 포인터

	// 유효성 검사: 리스트가 없거나, 인덱스가 범위를 벗어나면 NULL 반환
	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head; // 첫 번째 노드(인덱스 0)부터 시작

	if (temp == NULL || index < 0)
		return NULL;

	// index번만큼 next를 따라 이동
	// 예) index=2 이면 next를 2번 따라가면 인덱스 2인 노드에 도달
	while (index > 0){
		temp = temp->next; // 다음 노드로 이동
		if (temp == NULL)
			return NULL;   // 이동 중 끝에 도달하면 NULL 반환
		index--;
	}

	return temp; // 찾은 노드의 주소 반환
}

/*
 * insertNode: index 위치에 value를 가진 새 노드 삽입
 * - 삽입 후 앞뒤 연결을 올바르게 재설정해야 함
 * - 성공 시 0, 실패 시 -1 반환
 *
 * 연결 재설정 예시 (index=1에 삽입):
 * 삽입 전: [A] -> [B] -> [C]
 * 삽입 후: [A] -> [새노드] -> [B] -> [C]
 *           pre    new         cur
 */
int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur; // pre: 삽입 위치 앞 노드, cur: 삽입 위치 현재 노드

	// 유효성 검사
	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// 리스트가 비어있거나, 맨 앞(index=0)에 삽입하는 경우
	if (ll->head == NULL || index == 0){
		cur = ll->head;                       // 현재 첫 번째 노드를 임시 저장
		ll->head = malloc(sizeof(ListNode));  // 새 노드를 위한 메모리 할당
		ll->head->item = value;               // 새 노드에 값 저장
		ll->head->next = cur;                 // 새 노드가 기존 첫 번째 노드를 가리킴
		ll->size++;                           // 리스트 크기 1 증가
		return 0;
	}

	// 중간 또는 끝에 삽입하는 경우
	// pre = 삽입 위치 바로 앞 노드
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;                      // cur = 삽입 위치의 기존 노드
		pre->next = malloc(sizeof(ListNode)); // 새 노드 메모리 할당
		pre->next->item = value;              // 새 노드에 값 저장
		pre->next->next = cur;               // 새 노드가 기존 cur를 가리킴
		ll->size++;
		return 0;
	}

	return -1;
}


/*
 * removeNode: index 위치의 노드를 삭제
 * - 삭제 후 앞뒤 연결을 올바르게 재설정해야 함
 * - free()로 메모리 반환 필수!
 * - 성공 시 0, 실패 시 -1 반환
 *
 * 연결 재설정 예시 (index=1 삭제):
 * 삭제 전: [A] -> [B] -> [C]
 * 삭제 후: [A] -> [C]    (B는 free로 메모리 해제)
 *           pre   cur
 */
int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur; // pre: 삭제할 노드의 앞 노드, cur: 삭제할 노드

	// 유효성 검사: 삭제 가능한 최대 인덱스는 size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// 첫 번째 노드(index=0)를 삭제하는 경우: head를 다음 노드로 업데이트
	if (index == 0){
		cur = ll->head->next; // 두 번째 노드 주소 저장
		free(ll->head);       // 첫 번째 노드 메모리 해제
		ll->head = cur;       // head를 두 번째 노드로 업데이트
		ll->size--;
		return 0;
	}

	// 중간 또는 끝 노드 삭제
	// pre = 삭제할 노드의 바로 앞 노드
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;       // cur = 삭제할 노드
		pre->next = cur->next; // pre가 삭제할 노드를 건너뛰고 그 다음을 가리킴. 
		free(cur);             // 삭제할 노드의 메모리 해제
		ll->size--;
		return 0;
	}

	return -1;
}
