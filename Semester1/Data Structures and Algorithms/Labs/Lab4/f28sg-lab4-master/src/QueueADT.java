
public interface QueueADT {
	public int size();
	public boolean isEmpty();
	public Object front() throws QueueException;
	public Object dequeue() throws QueueException;
	public void enqueue(Object e);
}
