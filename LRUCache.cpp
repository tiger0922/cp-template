class Node {
public:
    int key, val;
    Node* next = NULL;
    Node* prev = NULL;

    Node(int key, int val) {
        this->key = key;
        this->val = val;
    }
};

class DLL {
    Node* head;
    Node* tail;
public:
    DLL() {
        this->head = new Node(0,0);
        this->tail = head;
    }
    void remove(Node* node) {
        if (node == tail) tail = node->prev;
        if (node->prev) node->prev->next = node->next;
        if (node->next) node->next->prev = node->prev;
        // clear the connection of this node
        node->prev = NULL;
        node->next = NULL;
    }
    void append(Node* node) {
        this->tail->next = node;
        node->prev = this->tail;
        this->tail = node;
    }
    void removeLRU() {
        if (head == tail) return;
        remove(this->head->next);
    }
    Node* getLRUnode() {
        return this->head->next;
    }
};

class LRUCache {
    unordered_map<int,Node*> hashMap;
    int capacity;
    DLL dll;
public:
    LRUCache(int capacity) {
        this->dll = DLL();
        this->capacity = capacity;
    }
    
    int get(int key) {
        // key not in hashMap
        if (hashMap.find(key) == hashMap.end()) {
            return -1;
        }

        Node* node = hashMap[key];
        dll.remove(node);
        dll.append(node);
        return node->val;
    }
    
    void put(int key, int value) {
        // key not in hashMap
        if (hashMap.find(key) == hashMap.end()) {
            Node* node = new Node(key, value);
            hashMap[key] = node;
            this->capacity--;
            if (this->capacity < 0) {
                Node* lru_node = dll.getLRUnode();
                hashMap.erase(lru_node->key);
                dll.removeLRU();
                this->capacity++;
            }
            dll.append(node);
            return;
        }
        Node* node = hashMap[key];
        node->val = value; // Update value
        dll.remove(node);
        dll.append(node);
    }
};

