class Node {
    public:
        int key;
        int value;
        Node* prev;
        Node* next;

        Node(int k,int v) : key(k), value(v), prev(nullptr), next(nullptr){}
};
#include <unordered_map>
using namespace std;
class LRUCache{
private:
    int capacity;
    unordered_map<int, Node*> cache; // Hash map to store key-node pairs
    Node* head;// Dummy head
    Node* tail; // Dummy tail
    void remove(Node* node){
        //Remove an existing node from linked list
        node->prev->next= node->next;
        node->next->prev= node->prev;
    }
    void add(Node* node){
        // Add a new node after the head
        node->next= head->next;
        node->prev= head;
        head->next->prev= node;
        head->next= node;
    }
public:
    LRUcache(int capacity){
        this->capacity= capacity;
        head= new Node(0,0);
        tail= new Node(0,0);
        head->next= tail;
        tail->prev= head;
    }
    int get(int key){
        if(cache.find(key) != cache.end()){
            Node* node= cache[key];
            remove(node);
            add(node);
            return node->value;
        }
        return -1;
    }
    void put(int key, int value){
        if(cache.find(key) != cache.end())  
        remove(cache[key]);
        Node* node= new Node(key, value);
        add(node);
        cache[key]= node;
        if(cache.size()> capacity){
            // Remove from tail
            Node* lru = tail-> prev;
            remove(lru);
            cache.erase(lru->key);
            delete lru;
        }
    }
    ~LRUCache(){
        Node* current = head;
        while(current != nullptr){
            Node* next= current->next;
            delete current;
            current=next;
        }
    }
};