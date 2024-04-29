public void insertionSort() {
    Node current = headNode.getNextNode();
    Node prev = current.prevNode;
    Node temp = current;
    int tempValue;

    while (current != null) {
        while (prev != null) {
            if (prev.value > current.value) {
                tempValue = current.value;
                current.value = prev.value;
                prev.value = tempValue;
                current = temp.getPrevNode();
                prev = current.getPrevNode();
            }
            else {
                current = current.getPrevNode();
                previous = current.getPrevNode();
            }
            current = temp.getNextNode();
            temp =current;
            prev = current.getPrevNode();
        }
        if (temp != null) {
            temp = temp.getNextNode();
        }
    }
}