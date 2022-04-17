#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node{  //구조체 Node에 대해서 정의
	int key;
	struct Node* link; //구조체 포인터 변수 link를 선언
} listNode; //구조체의 별칭을 listNode로 설정

typedef struct Head {  //구조체 Head 대해서 정의
	struct Node* first; //구조체 Node의 포인터 변수 first를 선언
}headNode; //구조체의 별칭을 headNode로 설정


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command; //커맨드를 입력받을 변수 선언
	int key; // 정수형 변수 키값을 입력받을 변수 선언
	headNode* headnode=NULL; //구조체 포인터 변수에 NULL값 저장

	do{
		printf("[----- [박준용] [2019038010] -----]");
        printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = "); 
		scanf(" %c", &command); //커맨드를 입력받아서 입력받은 값에 따라 함수 실행

		switch(command) { //입력받은 커맨드에따라 함수 실행
		case 'z': case 'Z': //z를 입력받은 경우
			headnode = initialize(headnode); //initalize 함수 실행 후 리턴값 대입
			break;
		case 'p': case 'P':  //p를 입력받은 경우
			printList(headnode); // printList 함수 실행
			break;
		case 'i': case 'I': //i를 입력받은 경우
			printf("Your Key = ");
			scanf("%d", &key);//key값을 입력 받음
			insertNode(headnode, key);// insertnode 함수 실행 -> key값을 넘겨준다
			break;
		case 'd': case 'D': //d를 입력받은 경우
			printf("Your Key = ");
			scanf("%d", &key);//key값을 입력 받음
			deleteNode(headnode, key);//deleteNode 함수 실행 -> key값을 넘겨준다 
			break;
		case 'n': case 'N'://n을 입력받은 경우
			printf("Your Key = ");
			scanf("%d", &key);//key값을 입력 받음
			insertLast(headnode, key);//insertLast 함수 실행 -> key값을 넘겨준다
			break;
		case 'e': case 'E'://e를 입력받은 경우
			deleteLast(headnode);//deleteLast 함수 실행 
			break;
		case 'f': case 'F'://f를 입력받은 겨우
			printf("Your Key = ");
			scanf("%d", &key);//key값을 입력 받음
			insertFirst(headnode, key);//insertFirst 함수 실행 -> key값을 넘겨준다
			break;
		case 't': case 'T'://t를 입력받은 경우
			deleteFirst(headnode);//deleteFirst 함수 실행
			break;
		case 'r': case 'R'://r을 입력받은 경우
			invertList(headnode);//invertList 함수 실행
			break;
		case 'q': case 'Q'://q를 입력받은 경우
			freeList(headnode);//freeList 함수 실행
			break;
		default://다른 커맨드를 입력받은 경우 집중이라는 경고 메세지 출력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //q를 입력받기 전까지 반복문 실행

	return 1;
}

headNode* initialize(headNode* h) {   //hadenode 포인터 변수를 동적할당 및 메모리 해제하는 함수

	
	if(h != NULL) // headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제
		freeList(h);

	
	headNode* temp = (headNode*)malloc(sizeof(headNode)); // headNode에 대한 포인터 변수 temp 메모리를  동적 할당
	temp->first = NULL; // 새로운 공백 리스트를 만든다
	return temp; //temp를 동적할당하고 리턴
}

int freeList(headNode* h){ //h와 연결된 listNode 메모리 해제
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first; //구조체 listNode의 포인터 변수 p에 리스트의 시작 주소 대입

	listNode* prev = NULL; //prev라는 새로운 공백 리스트 생성
	while(p != NULL) {   //p값이 NULL일 때까지 반복문 실행 ->1번째 노드부터 순차적으로 메모리 해제
		prev = p; //prev에 p 대입
		p = p->link;//p값에 p->link 대입 -> 다음 노드의 헤드값을 가리킨다
		free(prev);//prev 메모리 해제 
	}
	free(h);//h 메모리 해제
	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) { //노드에 key값을 입력하는 함수

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode 구조체 포인터 변수 node를 동적할당
	node->key = key;  // 새로운 노드의 key값에 입력받은 key값을 대입
	node->link = NULL;// node->link가 연결된 값이 없음을 나타냄

	if (h->first == NULL) //노드가 없을 경우
	{
		h->first = node; //첫번째 노드에 입력받은 node 값 대입
		return 0;
	}
    //입력받은 노드의 값들이 존재하는 경우
	listNode* n = h->first; // 새로운 노드를 만든 후 연결리스트 첫번째 주소를 대입
	listNode* trail = h->first; // 새로운 노드를 만든 후 연결리스트 첫번째 주소를 대입

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) 
    { 
		if(n->key >= key) /* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
        { 
			
			if(n == h->first) // n이 헤드 노드일 경우 -> 첫번째 노드인 경우
            {
				h->first = node;  //입력받은 노드를 헤드 노드로 바꾼다
				node->link = n;  //노드의 링크를 n과 연결
			} 
            else /* 중간이거나 마지막인 경우 */
            { 
				node->link = n; 
				trail->link = node;
			}
			return 0;
		}
             // 한칸씩 이동하면서 넣어줄 자리를 찾는다
		trail = n; 
		n = n->link;
	}

	/* 마지막 노드까지 찾지 못한 경우 , 마지막에 삽입 */
	trail->link = node;
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //구조체 노드 동적할당
	node->key = key;  //노드의 키값에 입력받은 값 대입
	node->link = NULL; //새로만든 노드의 링크는 연결된 것이 없음

	if (h->first == NULL) //헤드 노드의 값이 NULL인경우
	{
		h->first = node; //헤드노드가 node를 가리킴
		return 0;
	}

	listNode* n = h->first; // 연결리스트 노드 n이 h_>first를 나타냄
	while(n->link != NULL) { //노드의 링크가 null이 나올때까지 반복
		n = n->link; //노드를 한칸씩 이동 
	}
	n->link = node; // 마지막노드 뒤에 삽입 
	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //node 동적 할당
	node->key = key; //node key값에 입력받은 key값 대입

	node->link = h->first; //node ->link가 첫번째 노드를 가리키게 함
	h->first = node;//헤드노드를 변경

	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) { 

	if (h->first == NULL)   //헤드 노드의 값이 없을 경우 오류메세지 출력
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;  //n 노드가 첫번 째 노드를 가리킴
	listNode* trail = NULL; // 비어있는 노드 생성

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {
		if(n->key == key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {
				h->first = n->link;
			} else { /* 중간인 경우거나 마지막인 경우 */
				trail->link = n->link;
			}
			free(n);
			return 0;
		}
         //노드를 한칸씩 이동
		trail = n; 
		n = n->link;
	}  

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key); //입력받은 키값이 존재하지않는다고 메세지 출력
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL) //노드의 값이 존재하지않는 경우 오류 메세지 출력
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first; //n이 헤드노드를 가리킴
	listNode* trail = NULL; //비어있는 노드 생성

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->link == NULL) { 
		h->first = NULL;
		free(n); 
		return 0;
	}

	
	while(n->link != NULL) { //노드를 한칸씩 이동하며 마지막 노드까지 이동
		trail = n;
		n = n->link;
	}

	// n이 삭제되므로, 이전 노드의 링크 NULL 처리
	trail->link = NULL;
	free(n); //메모리해제

	return 0;
}
/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL) //헤드노드가 없는 경우 오류 메세지 출력
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first; //n이 헤드 노드를 가리킴

	h->first = n->link; //2번째 노드를 헤드노드로 변경 
	free(n);//메모리 해제

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {


	if(h->first == NULL) { //노드의 값이 존재하지 않는경우 오류 메세지 출력
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first; //n이 헤드노드를 가리킴
	listNode *trail = NULL; // 비어있는 노드를 생성
	listNode *middle = NULL; // 비어있는 노드를 생성

	while(n != NULL){// 빈 노드가 나올때까지 반복
		trail = middle;  //trail에 middle값 대입
		middle = n; //middle은 n에 값을 따라감
		n = n->link;//n은 n->link를 넣어주므로 다음 노드를 가리킴
		middle->link = trail; // middle의 링크가 이전 노드인 trail을 가리킴 -> 즉 연결리스트가 역순으로 변함
	}

	h->first = middle; //마지막에는 n이 null을 가리키고 middle이 마지막 노드를 가리키기 때문에 middle이 헤드노드가 된다

	return 0;
}


void printList(headNode* h) { //연결리스트를 출력하는 함수
	int i = 0;    //변수 선언
	listNode* p; //구조체 포인터 변수 선언

	printf("\n---PRINT\n");

	if(h == NULL) { //노드의 값이 없는 겨우 오류메세지 출력 
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; //p가 헤드노드를 가리킴

	while(p != NULL) { //노드가 NULL일 때까지 반복
		printf("[ [%d]=%d ] ", i, p->key); //인덱스번호와 키값을 출력
		p = p->link; //p에 다음노드를 가리키게 함
		i++; //인덱스 번호르 1씩 증가
	}

	printf("  items = %d\n", i); //존재하는 값의 갯수 출력
}