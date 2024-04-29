import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

public class LQueueTest {

	LQueue q;
	@Before
	public void setup()
	{
		q = new LQueue();
	}
	
	/*
	 * 2: complete the following test methods as specified. 
	 */
	
	@Test
	//tests that the isEmpty() method properly reoognizes that the size of the q is 0 upon setup
	public void testIsEmpty() {
		// test that q.isEmpty returns true
		assertTrue(q.isEmpty());
	}
	
	@Test
	//tests that isEmpty() method properly recognizes the size of q when an element is enqueued to it
	public void testIsEmptyFalse() {
		// add an element to the queue "q"
		q.enqueue(1);
		// then test that q is not an empty queue.
		assertFalse(q.isEmpty());
	}

	@Test
	// tests that upon setup the size of the q is 0
	public void testSizeEmpty() {
		// test the size of an empty queue is 0
		assertEquals(0, q.size());
	}
	
	@Test
	//populates q with 3 elements, then checks if q.size() recognizes the correct size
	public void testSizeNonEmpty() {
		// add an element(s) to the queue
		q.enqueue(1);
		q.enqueue(2);
		q.enqueue(3);
		// then test the size of the queue
		assertEquals(3, q.size());
	}

	@Test
	//adds 2 elements via enqueue, then checks that 1 is at the front as it should be fifo
	public void testEnqueue() {
		// enqueue an element(s) to the queue
		q.enqueue(1);
		q.enqueue(2);
		// then test that the correct element is at the front
		assertEquals(1, q.front());
	}
	
	@Test
	//adds 3 elements to queue, then dequeues each element to checks they are dequeued in a fifo order
	public void testDequeue() {
		// enqueue multiple elements to the queue
		q.enqueue(1);
		q.enqueue(2);
		q.enqueue(3);
		// then check that they are returned in the
		// correct order with dequeue.
		assertEquals(1, q.dequeue());
		assertEquals(2, q.dequeue());
		assertEquals(3, q.dequeue());
	}
	
	@Test(expected = QueueException.class)  
	public void testEmptyDequeue() {  
		// try to dequeue an empty queue
		q.dequeue();
	}
	
	@Test(expected = QueueException.class)  
	public void testEmptyFront() {
		// try to get the front value of an empty queue
		q.front();
	}
}
