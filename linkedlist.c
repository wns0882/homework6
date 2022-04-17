#include<stdio.h>
#include<stdlib.h>

/* �ʿ��� ������� �߰� */

typedef struct Node{  //����ü Node�� ���ؼ� ����
	int key;
	struct Node* link; //����ü ������ ���� link�� ����
} listNode; //����ü�� ��Ī�� listNode�� ����

typedef struct Head {  //����ü Head ���ؼ� ����
	struct Node* first; //����ü Node�� ������ ���� first�� ����
}headNode; //����ü�� ��Ī�� headNode�� ����


/* �Լ� ����Ʈ */
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
	char command; //Ŀ�ǵ带 �Է¹��� ���� ����
	int key; // ������ ���� Ű���� �Է¹��� ���� ����
	headNode* headnode=NULL; //����ü ������ ������ NULL�� ����

	do{
		printf("[----- [���ؿ�] [2019038010] -----]");
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
		scanf(" %c", &command); //Ŀ�ǵ带 �Է¹޾Ƽ� �Է¹��� ���� ���� �Լ� ����

		switch(command) { //�Է¹��� Ŀ�ǵ忡���� �Լ� ����
		case 'z': case 'Z': //z�� �Է¹��� ���
			headnode = initialize(headnode); //initalize �Լ� ���� �� ���ϰ� ����
			break;
		case 'p': case 'P':  //p�� �Է¹��� ���
			printList(headnode); // printList �Լ� ����
			break;
		case 'i': case 'I': //i�� �Է¹��� ���
			printf("Your Key = ");
			scanf("%d", &key);//key���� �Է� ����
			insertNode(headnode, key);// insertnode �Լ� ���� -> key���� �Ѱ��ش�
			break;
		case 'd': case 'D': //d�� �Է¹��� ���
			printf("Your Key = ");
			scanf("%d", &key);//key���� �Է� ����
			deleteNode(headnode, key);//deleteNode �Լ� ���� -> key���� �Ѱ��ش� 
			break;
		case 'n': case 'N'://n�� �Է¹��� ���
			printf("Your Key = ");
			scanf("%d", &key);//key���� �Է� ����
			insertLast(headnode, key);//insertLast �Լ� ���� -> key���� �Ѱ��ش�
			break;
		case 'e': case 'E'://e�� �Է¹��� ���
			deleteLast(headnode);//deleteLast �Լ� ���� 
			break;
		case 'f': case 'F'://f�� �Է¹��� �ܿ�
			printf("Your Key = ");
			scanf("%d", &key);//key���� �Է� ����
			insertFirst(headnode, key);//insertFirst �Լ� ���� -> key���� �Ѱ��ش�
			break;
		case 't': case 'T'://t�� �Է¹��� ���
			deleteFirst(headnode);//deleteFirst �Լ� ����
			break;
		case 'r': case 'R'://r�� �Է¹��� ���
			invertList(headnode);//invertList �Լ� ����
			break;
		case 'q': case 'Q'://q�� �Է¹��� ���
			freeList(headnode);//freeList �Լ� ����
			break;
		default://�ٸ� Ŀ�ǵ带 �Է¹��� ��� �����̶�� ��� �޼��� ���
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //q�� �Է¹ޱ� ������ �ݺ��� ����

	return 1;
}

headNode* initialize(headNode* h) {   //hadenode ������ ������ �����Ҵ� �� �޸� �����ϴ� �Լ�

	
	if(h != NULL) // headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ����
		freeList(h);

	
	headNode* temp = (headNode*)malloc(sizeof(headNode)); // headNode�� ���� ������ ���� temp �޸𸮸�  ���� �Ҵ�
	temp->first = NULL; // ���ο� ���� ����Ʈ�� �����
	return temp; //temp�� �����Ҵ��ϰ� ����
}

int freeList(headNode* h){ //h�� ����� listNode �޸� ����
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
	 */
	listNode* p = h->first; //����ü listNode�� ������ ���� p�� ����Ʈ�� ���� �ּ� ����

	listNode* prev = NULL; //prev��� ���ο� ���� ����Ʈ ����
	while(p != NULL) {   //p���� NULL�� ������ �ݺ��� ���� ->1��° ������ ���������� �޸� ����
		prev = p; //prev�� p ����
		p = p->link;//p���� p->link ���� -> ���� ����� ��尪�� ����Ų��
		free(prev);//prev �޸� ���� 
	}
	free(h);//h �޸� ����
	return 0;
}


/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) { //��忡 key���� �Է��ϴ� �Լ�

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode ����ü ������ ���� node�� �����Ҵ�
	node->key = key;  // ���ο� ����� key���� �Է¹��� key���� ����
	node->link = NULL;// node->link�� ����� ���� ������ ��Ÿ��

	if (h->first == NULL) //��尡 ���� ���
	{
		h->first = node; //ù��° ��忡 �Է¹��� node �� ����
		return 0;
	}
    //�Է¹��� ����� ������ �����ϴ� ���
	listNode* n = h->first; // ���ο� ��带 ���� �� ���Ḯ��Ʈ ù��° �ּҸ� ����
	listNode* trail = h->first; // ���ο� ��带 ���� �� ���Ḯ��Ʈ ù��° �ּҸ� ����

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL) 
    { 
		if(n->key >= key) /* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
        { 
			
			if(n == h->first) // n�� ��� ����� ��� -> ù��° ����� ���
            {
				h->first = node;  //�Է¹��� ��带 ��� ���� �ٲ۴�
				node->link = n;  //����� ��ũ�� n�� ����
			} 
            else /* �߰��̰ų� �������� ��� */
            { 
				node->link = n; 
				trail->link = node;
			}
			return 0;
		}
             // ��ĭ�� �̵��ϸ鼭 �־��� �ڸ��� ã�´�
		trail = n; 
		n = n->link;
	}

	/* ������ ������ ã�� ���� ��� , �������� ���� */
	trail->link = node;
	return 0;
}

/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //����ü ��� �����Ҵ�
	node->key = key;  //����� Ű���� �Է¹��� �� ����
	node->link = NULL; //���θ��� ����� ��ũ�� ����� ���� ����

	if (h->first == NULL) //��� ����� ���� NULL�ΰ��
	{
		h->first = node; //����尡 node�� ����Ŵ
		return 0;
	}

	listNode* n = h->first; // ���Ḯ��Ʈ ��� n�� h_>first�� ��Ÿ��
	while(n->link != NULL) { //����� ��ũ�� null�� ���ö����� �ݺ�
		n = n->link; //��带 ��ĭ�� �̵� 
	}
	n->link = node; // ��������� �ڿ� ���� 
	return 0;
}

/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //node ���� �Ҵ�
	node->key = key; //node key���� �Է¹��� key�� ����

	node->link = h->first; //node ->link�� ù��° ��带 ����Ű�� ��
	h->first = node;//����带 ����

	return 0;
}

/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) { 

	if (h->first == NULL)   //��� ����� ���� ���� ��� �����޼��� ���
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;  //n ��尡 ù�� ° ��带 ����Ŵ
	listNode* trail = NULL; // ����ִ� ��� ����

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL) {
		if(n->key == key) {
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->first) {
				h->first = n->link;
			} else { /* �߰��� ���ų� �������� ��� */
				trail->link = n->link;
			}
			free(n);
			return 0;
		}
         //��带 ��ĭ�� �̵�
		trail = n; 
		n = n->link;
	}  

	/* ã�� �� �Ѱ�� */
	printf("cannot find the node for key = %d\n", key); //�Է¹��� Ű���� ���������ʴ´ٰ� �޼��� ���
	return 0;

}

/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {

	if (h->first == NULL) //����� ���� ���������ʴ� ��� ���� �޼��� ���
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first; //n�� ����带 ����Ŵ
	listNode* trail = NULL; //����ִ� ��� ����

	/* ��尡 �ϳ��� �ִ� ���, �� first node == last node��  ��� ó�� */
	if(n->link == NULL) { 
		h->first = NULL;
		free(n); 
		return 0;
	}

	
	while(n->link != NULL) { //��带 ��ĭ�� �̵��ϸ� ������ ������ �̵�
		trail = n;
		n = n->link;
	}

	// n�� �����ǹǷ�, ���� ����� ��ũ NULL ó��
	trail->link = NULL;
	free(n); //�޸�����

	return 0;
}
/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL) //����尡 ���� ��� ���� �޼��� ���
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first; //n�� ��� ��带 ����Ŵ

	h->first = n->link; //2��° ��带 ������ ���� 
	free(n);//�޸� ����

	return 0;
}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {


	if(h->first == NULL) { //����� ���� �������� �ʴ°�� ���� �޼��� ���
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first; //n�� ����带 ����Ŵ
	listNode *trail = NULL; // ����ִ� ��带 ����
	listNode *middle = NULL; // ����ִ� ��带 ����

	while(n != NULL){// �� ��尡 ���ö����� �ݺ�
		trail = middle;  //trail�� middle�� ����
		middle = n; //middle�� n�� ���� ����
		n = n->link;//n�� n->link�� �־��ֹǷ� ���� ��带 ����Ŵ
		middle->link = trail; // middle�� ��ũ�� ���� ����� trail�� ����Ŵ -> �� ���Ḯ��Ʈ�� �������� ����
	}

	h->first = middle; //���������� n�� null�� ����Ű�� middle�� ������ ��带 ����Ű�� ������ middle�� ����尡 �ȴ�

	return 0;
}


void printList(headNode* h) { //���Ḯ��Ʈ�� ����ϴ� �Լ�
	int i = 0;    //���� ����
	listNode* p; //����ü ������ ���� ����

	printf("\n---PRINT\n");

	if(h == NULL) { //����� ���� ���� �ܿ� �����޼��� ��� 
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; //p�� ����带 ����Ŵ

	while(p != NULL) { //��尡 NULL�� ������ �ݺ�
		printf("[ [%d]=%d ] ", i, p->key); //�ε�����ȣ�� Ű���� ���
		p = p->link; //p�� ������带 ����Ű�� ��
		i++; //�ε��� ��ȣ�� 1�� ����
	}

	printf("  items = %d\n", i); //�����ϴ� ���� ���� ���
}