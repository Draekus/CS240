ExpandList(head, n)
    // If n is less than or equal to 0, return an empty list
    IF n <= 0 THEN
        RETURN NULL
    
    // If the list is empty, return NULL
    IF head IS NULL THEN
        RETURN NULL
    
    // Will point to the head of the new list
    new_head = NULL  
    // Will point to the last node of the new list
    tail = NULL
    // Pointer used to traverse the original list     
    current = head   
    
    // Process each node in the original list
    WHILE current IS NOT NULL
        value = current.value
        
        // Create n copies of the current node
        FOR i = 1 TO n
            new_node = CREATE_NODE(value)
            
            // If this is the first node, set it as the head
            IF new_head IS NULL THEN
                new_head = new_node
                tail = new_node
            ELSE
                // Otherwise, append to the end of the new list
                tail.next = new_node
                tail = new_node
            ENDIF
        ENDFOR
        
        // Move to the next node in the original list
        current = current.next
    ENDWHILE
    
    RETURN new_head

Time Complexity:
The time complexity is O(n * m) where n is the number of nodes in 
the original list and m is the number of copies to be made for each node.






PairwiseSwap(head)  

    // Handle case where list is empty or has one node 
    IF head IS NULL OR head.next IS NULL THEN  
        RETURN head  

    // Variables to track nodes  
    current = head  
    new_head = head.next  

    // Loop through the list, two nodes at a time  
    WHILE current IS NOT NULL AND current.next IS NOT NULL 

        // Save pointers to the pair of nodes and the next pair  
        first = current  
        second = current.next  
        next_pair = second.next  

        // Swap the pair by changing links  
        second.next = first  

        // Connect to the rest of the list 
        // If this is the end or only one node remains, connect to it  
        IF next_pair IS NULL OR next_pair.next IS NULL THEN  
            first.next = next_pair  

        ELSE  
            // Otherwise, connect to the next pair's second node  
            first.next = next_pair.next  

    // Move to the next pair  
    current = next_pair  

RETURN new_head 

 

Time Complexity:  

Each node is visited once and the work done inside the loop is O(1) 
so the running time is O(n) where n is the number of nodes in the list.





RemoveNthFromEnd(head, n): 

    // Initialize two pointers 
    first = head 
    second = head 
    
    // Move the first pointer n steps ahead to maintain a space of n elements between 
    // the two pointers. When first reaches the end, second will be n elements behind. 
    FOR i = 1 TO n DO 
        first = first.next 


    // If first is NULL, remove the head node 
    // This is because the head node is n elements from the end of the list 
    IF first is NULL THEN 
        RETURN head.next 
   
    // Move both pointers until first reaches the last node 
    WHILE first.next is NOT NULL DO 
        first = first.next 
        second = second.next 

    // When first.next is null then second will be at the nth element  
    // and it can be removed 
    second.next = second.next.next   

    // Reurn the head of the linked list 
    RETURN head 



BubbleSortUsingStacks(S):  
    // Auxiliary stack  
    // This stack will be used to hold elements temporarily
    T = new Stack() 
    // Boolean variable to track swaps
    swapped = True 
    // Initialize the number of elements in the stack
    n = S.size() 

    WHILE swapped IS True DO 
        swapped = False 
        // Reset the last sorted index to n
        // This variable will track the last sorted index
        last_sorted = n   
     
    // Move elements from S to T while sorting the largest element 
    FOR i = 1 TO last_sorted - 1 DO 
        a = S.pop() 
        b = S.pop() 
         
        IF a > b THEN 
            S.push(a) 
            T.push(b) 
            swapped = True 
        ELSE 
            S.push(b) 
            T.push(a) 
        
    // Move the largest element back to S 
    T.push(S.pop())  // The largest element is placed correctly 
    last_sorted = last_sorted - 1 
     
    // Move elements back from T to S 
    WHILE NOT T.is_empty() DO 
        S.push(T.pop()) 






 ReverseFirstK(Q, k)   
    // Declare an auxiliary stack  
    S = new Stack() 
    
    // Check if k is greater than the size of the queue
    IF k > Q.size() THEN 
        RETURN Q
    // Check if k is less than or equal to 0
    IF k <= 0 THEN 
        RETURN Q
    // Check if the queue is empty
    IF Q.is_empty() THEN 
        RETURN Q
    // Check if k is 1
    IF k == 1 THEN 
        RETURN Q
    
    // Use the stack to reverse the first k elements 
    FOR i = 1 TO k DO 
        S.push(Q.dequeue()) 

    // Step 2: Enqueue back the reversed elements 
    WHILE S is not empty DO 
        Q.enqueue(S.pop()) 

    // Move the remaining elements to the back to preserve order 
    size = Q.size() 
    FOR i = 1 TO (size - k) DO 
        Q.enqueue(Q.dequeue()) 






Mirror(S):   

    // Check if the stack is empty
    IF S.is_empty() THEN 
        RETURN S
    // Check if the stack has only one element
    IF S.size() == 1 THEN 
        RETURN S
    
    // Declare an auxiliary queue 
    Q = new Queue() 
    size = S.size() 

    // Transfer elements from stack to queue 
    WHILE S is not empty DO 
        Q.enqueue(S.pop()) 

    // Restore stack order and duplicate elements in queue 
    FOR i = 1 TO size DO 
        temp = Q.dequeue() 
        S.push(temp) 
        Q.enqueue(temp) 

    // Move stack elements back to queue 
    WHILE S is not empty DO 
        Q.enqueue(S.pop()) 

    // Queue is currently in same order as stack 
    // Rotate queue to reverse order 
    FOR i = 1 TO size DO 
        Q.enqueue(Q.dequeue()) 
    
    // Transfer elements back to stack to complete mirroring 
    WHILE Q is not empty DO 
        S.push(Q.dequeue()) 



KadaneAlgorithm(array)
    // Initialize variables to track current and maximum sums
    maximum = array[0]
    current_max = array[0]
    
    // Start from the second element 
    FOR i = 1 TO array.length - 1
        // Calculate the maximum between current element and 
        // current element plus current_max
        current_max = MAX(array[i], current_max + array[i])
        
        // Update maximum if we found a new maximum
        maximum = MAX(maximum, current_max)
    
    
    RETURN maximum

Time Complexity:
The time complexity is O(n), where n is the number of elements in the array.


FindMedianSortedArrays(nums1, nums2)
    // Ensure nums1 is the smaller array
    IF length(nums1) > length(nums2) THEN
        RETURN FindMedianSortedArrays(nums2, nums1)
    
    // Initialize variables
    m = length(nums1)
    n = length(nums2)
    low = 0
    high = m
    
    WHILE low <= high
        // Partition positions
        partitionX = (low + high) / 2
        partitionY = (m + n + 1) / 2 - partitionX
        
        // Find elements around the partitions
        // If partition is at 0, use -INFINITY
        // If partition is at end, use +INFINITY
        maxX = (partitionX == 0) ? -INFINITY : nums1[partitionX - 1]
        minX = (partitionX == m) ? +INFINITY : nums1[partitionX]
        
        maxY = (partitionY == 0) ? -INFINITY : nums2[partitionY - 1]
        minY = (partitionY == n) ? +INFINITY : nums2[partitionY]
        
        // Check if we found the correct partition
        IF maxX <= minY AND maxY <= minX THEN
            // Found the right partition
            // Calculate median based on odd or even total length
            IF (m + n) % 2 == 0 THEN
                // If even then calculate average of two middle elements
                RETURN (MAX(maxX, maxY) + MIN(minX, minY)) / 2
            ELSE
                // If odd then middle element
                RETURN MAX(maxX, maxY)
            
        ELSE IF maxX > minY THEN
            // Need to move partition left in nums1
            high = partitionX - 1
        ELSE
            // Need to move partition right in nums1
            low = partitionX + 1
     



SearchMatrix(matrix, target)
    // Start from the top-right corner
    row = 0
    col = matrix[0].length - 1
    
    // Continue until we go out of bounds
    WHILE row < matrix.length AND col >= 0
        current = matrix[row][col]
        
        IF current == target THEN
            // Found the target
            RETURN TRUE
        ELSE IF current > target THEN
            // Current value is too large
            col = col - 1
        ELSE
            // Current value is too small
            row = row + 1
        
    
    
    // If we exit the loop, the target is not in the matrix
    RETURN FALSE