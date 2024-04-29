import java.util.ArrayList;

public class DLinkedList {

	private class Node {
		private int value;
		private Node nextNode;
		private Node prevNode;

		public Node(int v) {
			value = v;
			nextNode = null;
			prevNode = null;
		}

		public int getValue() {
			return value;
		}

		public void setValue(int v) {
			value = v;
		}

		public Node getNextNode() {
			return nextNode;
		}

		public void setNextNode(Node n) {
			nextNode = n;
		}

		public Node getPrevNode() {
			return prevNode;
		}

		public void setPrevNode(Node n) {
			prevNode = n;
		}

	}

	// Holds a reference to the head and tail of the list
	private Node headNode;
	private Node tailNode;

	public DLinkedList() {
		headNode = null;
		tailNode = null;
	}

	public Object getHeadValue() {
		if (headNode == null)
			return null;
		return headNode.value;
	}

	public Object getTailValue() {
		if (tailNode == null)
			return null;
		return tailNode.value;
	}

	public void addAtHead(int o) {
		Node newNode = new Node(o);
		newNode.setNextNode(headNode);
		if (headNode != null)
			headNode.setPrevNode(newNode);
		headNode = newNode;
		// special case for empty list
		if (tailNode == null)
			tailNode = newNode;
	}

	public void addAtTail(int o) {
		Node newNode = new Node(o);
		// this means that headNode == null too!
		if (tailNode == null) {
			tailNode = newNode;
			headNode = newNode;
		} else {
			newNode.setPrevNode(tailNode);
			tailNode.setNextNode(newNode);
			tailNode = newNode;
		}
	}

	public int deleteAtHead() {
		// list is empty
		if (headNode == null) {
			headNode = null;
			tailNode = null;
			return -1;
		}
		// singleton: must update tailnode too
		if (headNode == tailNode) {
			int res = headNode.getValue();
			headNode = null;
			tailNode = null;
			return res;
		}

		int res = headNode.getValue();
		headNode = headNode.getNextNode();
		headNode.setPrevNode(null);
		return res;
	}

	public int deleteAtTail() {
		// list is empty
		if (tailNode == null) {
			headNode = null;
			tailNode = null;
			return -1;
		}
		// singleton: must update tailnode too
		if (headNode == tailNode) {
			int res = tailNode.getValue();
			headNode = null;
			tailNode = null;
			return res;
		}
		int res = tailNode.getValue();
		tailNode = tailNode.getPrevNode();
		tailNode.setNextNode(null);
		return res;
	}

	public int delete(Node n) {
		if (n == null)
			return -1;
		Node next = n.getNextNode();
		Node prev = n.getPrevNode();
		int val = n.getValue();
		if (prev != null)
			prev.setNextNode(next);
		if (next != null)
			next.setPrevNode(prev);
		// deleting at the end
		if (n == tailNode)
			tailNode = prev;
		// deleteing at beginning
		if (n == headNode)
			headNode = next;
		return val;
	}

	public void insertAfter(Node n, int val) {
		if (n == null) { // this is the headNode
			addAtHead(val);
			return;
		}
		Node next = n.getNextNode();
		Node newNode = new Node(val);
		newNode.setPrevNode(n);
		newNode.setNextNode(next);
		n.setNextNode(newNode);
		if (next == null) { // insert at tail
			tailNode = newNode;
		} else {
			next.setPrevNode(newNode);
		}
	}

	// computes the size of the list
	public int size() {
		if (headNode == null)
			return 0;
		Node n = headNode;
		int size = 0;
		while (n != null) {
			size++;
			n = n.getNextNode();
		}
		return size;
	}

	// Predicate to check if the linked list is sorted
	public boolean isSorted() {
		if (headNode == null || headNode.nextNode == null)
			return true;
		Node i = headNode.nextNode;
		while (i != null) {
			if (i.getValue() < i.getPrevNode().getValue())
				return false;
			i = i.nextNode;
		}
		return true;
	}

	// toString methods to override printing of object
	public String toString() {
		Node n = headNode;
		StringBuffer buf = new StringBuffer();
		while (n != null) {
			buf.append(n.getValue());
			buf.append(" ");
			n = n.getNextNode();
		}
		return buf.toString();
	}

	/**
	 * Sorted the doubly linked list using the insertion-sort algorithm.
	 * 
	 * This is Question 4
	 * 
	 * Look at how insertionSort in ArraySort.java does insertion sort on arrays.
	 * The task is to perform the same algorithm, but sorting nodes linked together
	 * in a doubly linked list.
	 * 
	 * TODO Where N is the number of elements in the list the complexity is:
	 *
	 * O(N^2)
	 */
	public void insertionSort() {
		//handles case of an empty dll
		if (headNode==null){
			return;
		}

		//instanciates currentNode as the second node
		Node currentNode = headNode.getNextNode();

		while (currentNode != null) {
			//extracts the value of the current node, so that it can be sorted
			int targetValue = currentNode.getValue();
			//creates a pointer to the previous node
			Node prevNode = currentNode.getPrevNode();

			//moves the nodes in the sorted part(left) to the right if they are larger than the target value
			while (prevNode != null && targetValue < prevNode.getValue()) {
				//moves value from left to right
				prevNode.nextNode.setValue(prevNode.getValue());
				//moves the previous pointer a node to the left to check if it needs to sort the next previous node
				prevNode = prevNode.getPrevNode();
			}

			//inserts the target value in the correct sorted node
			if (prevNode == null) {
				//inserts at head if all nodes to the right are greater than
				headNode.setValue(targetValue);
			} else {
				//inserts at the node after the node that didnt meet the while criteria
				prevNode.nextNode.setValue(targetValue);
			}

			//updates the currentNode to the next unsorted node
			currentNode = currentNode.getNextNode();
		}
	}

	public static void main(String[] args) {
		DLinkedList d = new DLinkedList();
		d.addAtHead(4);
		d.addAtHead(1);
		d.addAtHead(7);
		d.addAtHead(10);
		System.out.println("Before sorting: " + d); // this will call the toString method
		d.insertionSort();
		System.out.println("After sorting: " + d);
	}

}
