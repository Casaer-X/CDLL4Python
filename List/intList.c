#include<stdint.h>
#include <stdlib.h>
//定义int64_t类型的链表
typedef struct IntNode {
    int64_t data;
    struct IntNode* next;
} IntNode;
//初始化链表
IntNode* createIntList() {
    IntNode* head = (IntNode*)malloc(sizeof(IntNode));
    if (head == NULL) {
        return NULL; // 内存分配失败
    }
    head->data = 0; // 初始化头节点数据
    head->next = NULL; // 头节点的下一个指针为空
    return head;
}
//在链表末尾添加新节点
int addIntNode(IntNode* head, int64_t value) {
    if (head == NULL) {
        return -1; // 链表未初始化
    }
    IntNode* newNode = (IntNode*)malloc(sizeof(IntNode));
    if (newNode == NULL) {
        return -1; // 内存分配失败
    }
    newNode->data = value;
    newNode->next = NULL;

    IntNode* current = head;
    while (current->next != NULL) {
        current = current->next; // 找到链表的最后一个节点
    }
    current->next = newNode; // 将新节点添加到链表末尾
    return 0; // 成功添加节点
}
//插入新节点到链表的指定位置
int insertIntNode(IntNode* head, int64_t value, int position) {
    if (head == NULL || position < 0) {
        return -1; // 链表未初始化或位置不合法
    }
    IntNode* newNode = (IntNode*)malloc(sizeof(IntNode));
    if (newNode == NULL) {
        return -1; // 内存分配失败
    }
    newNode->data = value;

    if (position == 0) { // 插入到头部
        newNode->next = head->next;
        head->next = newNode;
        return 0; // 成功插入
    }

    IntNode* current = head;
    for (int i = 0; i < position - 1 && current->next != NULL; i++) {
        current = current->next; // 找到插入位置的前一个节点
    }
    newNode->next = current->next; // 将新节点的下一个指针指向当前节点的下一个节点
    current->next = newNode; // 将当前节点的下一个指针指向新节点
    return 0; // 成功插入
}
//删除指定位置的节点
int deleteIntNode(IntNode* head, int position) {
    if (head == NULL || position < 0) {
        return -1; // 链表未初始化或位置不合法
    }
    IntNode* current = head;
    if (position == 0) { // 删除头节点
        if (current->next == NULL) {
            return -1; // 链表为空，无法删除
        }
        IntNode* toDelete = current->next;
        current->next = toDelete->next; // 将头节点的下一个指针指向下一个节点
        free(toDelete); // 释放被删除节点的内存
        return 0; // 成功删除
    }

    for (int i = 0; i < position - 1 && current->next != NULL; i++) {
        current = current->next; // 找到要删除节点的前一个节点
    }
    if (current->next == NULL) {
        return -1; // 位置超出链表范围，无法删除
    }
    IntNode* toDelete = current->next;
    current->next = toDelete->next; // 将前一个节点的下一个指针指向被删除节点的下一个节点
    free(toDelete); // 释放被删除节点的内存
    return 0; // 成功删除
}
//释放链表的所有节点
void freeIntList(IntNode* head) {
    if (head == NULL) {
        return; // 链表未初始化
    }
    IntNode* current = head->next; // 从头节点的下一个开始
    while (current != NULL) {
        IntNode* toDelete = current;
        current = current->next; // 保存下一个节点
        free(toDelete); // 释放当前节点的内存
    }
    free(head); // 释放头节点的内存
}
//修改链表中指定位置的节点数据
int modifyIntNode(IntNode* head, int64_t value, int position) {
    if (head == NULL || position < 0) {
        return -1; // 链表未初始化或位置不合法
    }
    IntNode* current = head->next; // 从头节点的下一个开始
    for (int i = 0; i < position && current != NULL; i++) {
        current = current->next; // 找到指定位置的节点
    }
    if (current == NULL) {
        return -1; // 位置超出链表范围，无法修改
    }
    current->data = value; // 修改节点数据
    return 0; // 成功修改
}

// 获取链表长度
int getIntListLength(IntNode* head) {
    if (head == NULL) return 0;
    int count = 0;
    IntNode* current = head->next;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// 将链表内容复制到数组，返回实际元素个数
int copyIntListToArray(IntNode* head, int64_t* arr, int maxlen) {
    if (head == NULL || arr == NULL || maxlen <= 0) return 0;
    int count = 0;
    IntNode* current = head->next;
    while (current != NULL && count < maxlen) {
        arr[count++] = current->data;
        current = current->next;
    }
    return count;
}

// 获取指定位置的元素值，成功返回0，失败返回-1
int getIntNodeValue(IntNode* head, int position, int64_t* value) {
    if (head == NULL || position < 0 || value == NULL) {
        return -1;
    }
    IntNode* current = head->next;
    for (int i = 0; i < position && current != NULL; i++) {
        current = current->next;
    }
    if (current == NULL) {
        return -1;
    }
    *value = current->data;
    return 0;
}