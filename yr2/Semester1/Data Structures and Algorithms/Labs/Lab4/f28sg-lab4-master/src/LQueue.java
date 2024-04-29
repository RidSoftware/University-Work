/*
 * Queue implementation with a linked list.
 */
public class LQueue implements QueueADT {
	
	private class Node{
		Object element;
		Node next;
		
		public Node(Object e, Node n){
			element = e;
			next = n;
		}
		
		public Node(Object e){
			element = e;
			next = null;
		}
	}
	
	private Node head;
	private Node tail;
	private int size;
	
	public LQueue(){
		head = null;
		tail = null;	
		size = 0;
	}
	
	/*
	 * Part 3: complete the following methods
	 */
	
	// Part 3: complete	
	/**
	 * Returns true if the queue is empty, false otherwise.
	 * 
	 * TODO Where N is the number of elements in the queue the complexity is:
	 *
	 * O(1)
	 */
	public boolean isEmpty(){
		//returns boolean value if a head exists for the LQueue, as that would show that no elements exist, thus empty
		Node current = head;

		if (current == null){
			return true;
		}else{
			return false;
		}

	}
	
	// Part 3: complete
	/**
	 * Returns how many elements are in the queue.
	 * 
	 * TODO Where N is the number of elements in the queue the complexity is:
	 *
	 * O(N)
	 */
	public int size(){
		//creates counter variable and a pointer currently pointing at the first element
		int count = 0;
		Node current = head;

		//iterates through each node in the LQueue, counting how many elements there are
		while (current != null){
			count++;
			current = current.next;
		}
		return count; 
	}
	
	// Part 3: complete
	/**
	 * Adds a new element to the end of the queue.
	 * 
	 * TODO Where N is the number of elements in the queue the complexity is:
	 *
	 * O(1)
	 */
	public void enqueue(Object o) {
		//creates a new node with the element passed to the enqueue method
		Node newNode = new Node(o);

		//if the queue is empty upadtes both the head and the tail pointers
		if(isEmpty()){
			head = newNode;
			tail = newNode;
		} else{ //else, updates the tail pointer and the next pointer
			//updates next of the current tail first 
			tail.next = newNode;
			//then mutates the tail to updated tail
			tail = newNode;
		}
		//ensures the size variable keeps track of the size dynamically
		//may have to refactor ther size() method to return the public size variable
		size++;

	}
	
	// Part 3: complete	
	/**
	 * Removes the element at the front of the queue.
	 * 
	 * TODO Where N is the number of elements in the queue the complexity is:
	 *
	 * O(1)
	 */
	public Object dequeue() throws QueueException{
		//throws exception for empty queue
		if (isEmpty()) {
			throw new QueueException("cannot dequeue an empty queue");
		}

		//extracts the desired head element fro dequeue
		Object dequeuedElement = head.element;

		//updates head element
		head = head.next;
		
		//if the queue is empty after dequeue, then sets the tail to null
		if (isEmpty()){
			tail = null;
		}

		//update size of queue
		size--;

		return dequeuedElement;
	}
	
	// Part 3: complete
	/**
	 * Returns the element at the front of the queue without removing it.
	 * 
	 * TODO Where N is the number of elements in the queue the complexity is:
	 *
	 * O(1)
	 */
	public Object front() throws QueueException{
		//throws exception for empty queue
		if(isEmpty()){
			throw new QueueException("cannot return front of empty queue");
		}

		//returns the element at the front of the queue
		return head.element;
	}
	
}
