/*
4. Compare the times it takes to sort an array filled with random numbers vs a linked list via
bubble sort and insertion sort.
*/

//for timing
#include<functional>
#include <chrono>
using std::chrono::system_clock;
using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::milliseconds;
//-----------
#include<iostream>
#include<algorithm>
using namespace std;


//============ARRAY TEMPLATES===============
template<typename T>
void fillArray (T* array, const long long size){
    //Fill an array with random numbers and sort the array
    for (int i = 0; i<size; i++){ //iterate through array
        T random = rand()%1000/10.0; //generate random number and assign it to current positon in array
        array[i] = random;
        }
}//fillArray

template<typename T>
void printArray (T* array, const long size){
    //Prints each element in an array
    for (int i = 0; i < size; i++)//iterate through array
    {
        cout << array[i] << "   ";//print each element in the array
    }
    cout << endl;
}//printArray

template<typename arrType>
void insertionSortArray(arrType array[], int size){
    //Insertion sort selects an unsorted element from the array, and compares it to all of the previous elements. If the selected element is less than the 
    //previous value, the previous value becomes the next value, and the reference is checked again for all remaining previous element.
    //The function loops until we have check each element in the list

    for (int i = 1; i < size; i++) //iterate through the array
    {
        arrType reference = array[i]; //create a reference to current element
        int j = i-1; //begin iterating from the previous element to the first element in the array
        while ( reference < array[j] && j>= 0){  //if current element is less than previous element
            array[j+1] = array[j];  //the previous element becomes the next element
            j--; //and we compare the current element to the previous-previous element
        }
        array[j+1] = reference; //place the refrence into the proper position
     }
}



template<typename arrType>
void bubbleSortArray(arrType array[], int size){
    //Bubble sort compares one array element to the next element, and swaps them if the next element is smaller.
    //Swapping will continue until there are no more elements to be swapped, meaning that the array is sorted.
    arrType temp;
    for (int i = 0; i < size; i++) //for each element
    {
        for (int j = 0 ; j < size-i-1; j++) //compare it with the next element until there is no next element
        {
            if (array[j] > array[j+1]){ //if current element is greater than the next
                swap(array[j], array[j+1]); //swap the elements
            }
        }//when this loop ends, we will compare the next element (i) with elements ahead of it in the array
    }  
}
//============END OF ARRAY TEMPLATES===============




//=======LINKED LIST CLASS========
template<typename nodeType>
class Node{
    public:
        nodeType data; //node has a data value
        Node<nodeType>* link; //node has a pointer to next node in list
        Node(nodeType value): data(value){ link = nullptr; }//default constructor
};//node templated class

template<typename nodeType>
class List{
    protected:
        long long  nodeCount; //stores number of nodes in the list
    public:
        Node<nodeType>* head; //ref to first node
        Node<nodeType>* tail;//ref to last node
        //a newly created list has an empty head and tail
        List() { nodeCount = 0; head = nullptr; tail = nullptr; } //constructor

        //declare functions of templated class here, define them outside of the class templates
        void insertHead(nodeType val); //inserts node at front of the list
        void fillListFromArray(nodeType* array, int size); //fills a list using sorted arrays
        void timeListInsertionSort(int iterations, int arraySize);
        void timeListBubbleSort(int iterations, int arraySize);
        void insertionSortList();
        nodeType getData(int index); //gets value of list at specified position
        void bubbleSortList();
        void print();//prints each node in a list
        void insert(int index, nodeType val);//inserts a node into a specified position
        void remove(int index);//removes a node from a specified position
        void swap(Node<nodeType>* x, Node<nodeType>* y); //swaps the data values of two nodes
        Node<nodeType>* getNode(int index); //returns a reference to the node at a specified position in the list


};//linked list templated class

template<typename nodeType>
nodeType List<nodeType>::getData(int index){
    if (index < 0 || index > nodeCount ) { return -1 ;}//if index is out of bounds, node does not exist
    Node<nodeType>* node = head;//start from head node
    for (int i = 0; i < index; i++) //
    {
        node = node->link; //traverse until we find the node at the index
    }
    return node->data;//return the node data
}

template<typename nodeType>
Node<nodeType>* List<nodeType>::getNode(int index){
    if ( index < 0 || index > nodeCount) { return 0; } //if index is out of bounds, node does not exist
    Node<nodeType>* node = head; //begin traversing from first node of the list
    for (int i = 0; i < index; i++)
    {
        node = node->link; //iterate until we get the node at the specified index
    }
    return node;
}

template<typename nodeType>
void List<nodeType>::swap(Node<nodeType>* a, Node<nodeType>* b){
    nodeType aData = a->data; //store the data of the first node
    a->data = b->data; //set data of first node to data of second node
    b->data = aData; //set data of second node to data previously in first node
}

template<typename nodeType>
void List<nodeType>::remove(int index){
    if (nodeCount == 0 || index < 0 || index >= nodeCount){ return; } //if list is empty or index is out of bounds, do nothing
    if (index == 0){ //if removing first element, remove the head
        Node<nodeType>* temp = head; 
        head = head->link; //the new head becomes the next node in the list
        delete temp; //the original head is deleted
        nodeCount--; //a node is removed from the list
    }
    else if (index == nodeCount - 1){
        //if removing last element, remove the tail
        Node<nodeType>* prevNode = head; 
        Node<nodeType>* lastNode = head->link;
        while ( lastNode->link != NULL ){ //traverse to the index
            prevNode = prevNode->link; //
            lastNode = lastNode->link;
        }
        prevNode->link = NULL; //the second to last node becomes the tail, and its link is set to null
        tail = prevNode;

        delete lastNode; //the original tail is deleted

        nodeCount--; // a node is removed from the list
    }
    else {
        //otherwise, find the element to remove
        Node<nodeType>* prevNode = head;
        for (int i = 0; i < index - 1; i++) //find the node that comes before the one we want to remove
        {
            prevNode = prevNode->link;
        }
        Node<nodeType>* removeNode = prevNode->link; //the node to be removed is the next node
        Node<nodeType>* nextNode = removeNode->link; //the next node of the node being removed, will be the next node of the previous node
        prevNode->link = nextNode; //set the link of previous node to the next node
        delete removeNode; //remove the node
        nodeCount--;
    }
}//remove

template<typename nodeType>
void List<nodeType>::insertHead(nodeType val){
    Node<nodeType>* node = new Node<nodeType>(val); //create a new node with the value to be inserted at the head
    node->link = head; //the link of the inserted node will be the current head
    head = node; //the inserted node is the new head of the list
    if (nodeCount == 0){ tail = head; } //if the list is empty, the inserted head will also be the tail
    nodeCount++;//we have added a node to the list, increment the node counter
}//insertHead template

template<typename nodeType>
void List<nodeType>::print(){
    Node<nodeType>* current =  this->head; //start traversing from the head
    while (current != NULL){ //while there is a next node
        cout << current->data << "->"; //print out the data of each node
        current = current->link; //set the current node to the next node
    }
    cout << "NULL" << endl;  
}

template<typename nodeType>
void List<nodeType>::insert(int index, nodeType val){
    if (index < 0 || index > nodeCount) { return; }//check if index is out of bounds
    if ( index == 0) { insertHead(val); return;}//if list is empty, insert a head

    Node<nodeType>* prevNode = head; //begin searching for the node that comes before the selected index
    for (int i = 0; i < index-1; i++)//until find the selected index, traverse the nodes
    {
        prevNode = prevNode->link; //when loop finishes, prevNode will link to node at selected index 
    }
    Node<nodeType>* nextNode = prevNode->link; //next node links to node after selected index
    Node<nodeType>* node = new Node<nodeType>(val);//node to be inserted
    //insert node between previous and next node
    node->link = nextNode;//link of inserted will be node after selected index
    prevNode->link = node;//link of prevNode will be the node inserted into selected index
    nodeCount++; //increment node counter because a new node was inserted
}//insert template

template<typename nodeType>
void List<nodeType>::fillListFromArray(nodeType* array, int size){
    for (int i = 0; i < size ; i++) //begin from last element in the value array
    {
        this->insertHead(array[i]);//insert a node with current element to the beginning of the list
    }//this loop inserts values from a sorted array into a list so that the list nodes are ordered by value
    //cout << "List filled." << endl;
}

template<typename nodeType>
void List<nodeType>::insertionSortList(){
    for (int i = 0; i < this->nodeCount; i++) //traverse through the list
    {
        nodeType reference = this->getData(i); //create a reference to the current element
        int j = i-1; //check elements before the current element
        int offset = 0; //each time we have to remove a node, we need to keep track of where the element being removed is
        while ( reference < this->getData(j) && j>=0){

            //this->insert(j+1, this->getData(j));
            //this->remove(j+1);
            this->insert(j, reference);
            this->remove(i + 1 - offset); //the index of the element being removed will be the next element in the list, minus the number of elements we have already traversed
            j--;
            offset++;
        }
        this->insert(j+1, reference);
        this->remove(j+1);
    }
    
}

template<typename nodeType>
void List<nodeType>::bubbleSortList(){
     nodeType temp;
     for (int i = 0; i < nodeCount; i++) //select a current node from the list
     {
         for (int j = 0; j < nodeCount-i-1; j++) //loop until there is no next node
         {
             if ( this->getData(j) > this->getData(j+1)){ //compare current node with the next node
                swap(this->getNode(j), this->getNode(j+1));
             }
         }  
     }    
}
//==========END LL CLASS=========




//=======TIMING==========
template <typename Func>
long long TimeFunc(size_t iterations, Func f)
{

	auto begin = chrono::steady_clock::now(); //begin the clock
    for (size_t i = 0; i < iterations; i++) { f(); } //perform the function over set iterations
    
	auto end = chrono::steady_clock::now(); //end the clock

	return duration_cast<chrono::milliseconds>((end - begin) / iterations).count(); //calculate average time for a single iteration
}//TimeFunc

template <typename T>
void timeArrayInsertionSort(int iterations, int arraySize)
{
    long long totalTime = 0;
    for (int i = 0; i < iterations; i++) //for each iteration
    {
        int* array = new T[arraySize]; //create a new array to sort
        fillArray(array,arraySize); //fill the new array
        auto arrayInsertionSortTime = TimeFunc(1, [&]() {insertionSortArray(array, arraySize);}); //sort the array while timing the function
        totalTime += arrayInsertionSortTime;
    }
    totalTime = totalTime / iterations;
    cout << "The average time it takes to perform an insertion sort on an array of size " << arraySize << " over " << iterations << " iterations is: " << totalTime << " milliseconds." << endl;
}//timeArrayInsertionSort

template<typename T>
void timeArrayBubbleSort(int iterations, int arraySize){
    long long totalTime = 0;
    for (int i = 0; i < iterations; i++) //for each iteration
    {
        int* array = new T[arraySize]; //create a new array to sort
        fillArray(array,arraySize); //fill the new array
        auto arrayBubbleSortTime = TimeFunc(1, [&]() {bubbleSortArray(array, arraySize);}); //sort the array while timing the function
        totalTime += arrayBubbleSortTime;
    }
    totalTime = totalTime / iterations;
    cout << "The average time it takes to perform a bubble sort on an array of size " << arraySize << " over " << iterations << " iterations is: " << totalTime << " milliseconds." << endl;
    
}//timeArrayBubbleSort

template<typename T>
void timeListBubbleSort(int iterations, int listSize){
    long long totalTime = 0;
    for (int i = 0; i < iterations; i++) //for each iteration
    {
        int* array = new T[listSize]; //create a new array to sort
        fillArray(array,listSize); //fill the new array
        List<T>* list = new List<T>();
        list->fillListFromArray(array,listSize);
        auto listBubbleSortTime = TimeFunc(1, [&]() {list->bubbleSortList();}); //sort the list while timing thefunction
        totalTime += listBubbleSortTime;
    }
    totalTime = totalTime / iterations;
    cout << "The average time it takes to perform a bubble sort on a list of size " << listSize << " over " << iterations << " iterations is: " << totalTime << " milliseconds." << endl;
}//timeListBubbleSort

template<typename T>
void timeListInsertionSort(int iterations, int listSize){
    long long totalTime = 0;
    for (int i = 0; i < iterations; i++) //for each iteration
    {
        int* array = new T[listSize]; //create a new array to sort
        fillArray(array,listSize); //fill the new array
        List<T>* list = new List<T>();
        list->fillListFromArray(array,listSize);
        auto listInsertionSortTime = TimeFunc(1, [&]() {list->insertionSortList();}); //sort the list while timing thefunction
        totalTime += listInsertionSortTime;
    }
    totalTime = totalTime / iterations;
    cout << "The average time it takes to perform an insertion sort on a list of size " << listSize << " over " << iterations << " iterations is: " << totalTime << " milliseconds." << endl;
   
}//timeListInsertionSort
int main(){
    srand(time(NULL));
    //Timing large arrays
    int largeArray = 10000; //10,000
    int largeIterations = 10;
    timeArrayBubbleSort<int>(largeIterations, largeArray);
    timeArrayInsertionSort<int>(largeIterations, largeArray);


    //Timing same size list and array
    int size1=1000;
    int arrayIterations = 10;
    timeArrayBubbleSort<int>(arrayIterations, size1); //DONE
    timeArrayInsertionSort<int>(arrayIterations, size1); //DONE

    int size2 = 1000;
    int listIterations = 1;
    timeListInsertionSort<int>(listIterations, size2);
    timeListBubbleSort<int>(listIterations,size2);
   

    //DEMONSTRATION OF WORKING SORTS

    int* array1 = new int[20];
    fillArray(array1, 20);
    cout << "[original array]  " ;
    printArray(array1,20);  
    bubbleSortArray(array1,20);
    cout << "[bubble sorted array]  " ;
    printArray(array1,20);  

    int* array2 = new int[20];
    fillArray(array2, 20);
    cout << "[original array]  " ;
    printArray(array2,20); 
    insertionSortArray(array2,20);
    cout << "[insertion sorted array]  " ;
    printArray(array2,20); 

    int* listArray = new int[20];
    fillArray(listArray, 20);
    List<int>* list = new List<int>();
    list->fillListFromArray(listArray, 20);
    cout << "[original list]   ";
    list->print();  
    list->bubbleSortList();
    cout << "[bubble sorted list]   ";
    list->print();  

    List<int>* list2 = new List<int>();
    list2->fillListFromArray(listArray, 20);
    cout << "[original list]  " ;
    list2->print(); 
    list2->insertionSortList();
    cout << "[insertion sorted list]  " ;
    list2->print(); 

    
}