08_Graph_Lab
============

Implement a simple graph class

Requirements
------------

1. Implement all methods of the `Graph` class.

Reading
=======
"Open Data Structures," Chapter 12, the whole chapter. http://opendatastructures.org/ods-cpp/12_Graphs.html

Questions
=========

#### 1. Which of the above requirements work, and which do not? For each requirement, write a brief response.

1. add - I believe this works?
2. remove - I believe this works?
3. getCost - I believe this works?

#### 2. For each of your methods, what is the worst-case running time? You may write your answer in terms of `n` (the number of vertices), `m` (the number of edges), `d` (the maximum degree of any node in the graph), or any combination of these. Try to give the most informative bound that you can.

1. add - This is O(2m) time because we must rebuild each vector every time an edge is added under the current implementation, and we musty rebuild the vector
         for two nodes.
2. remove - This is O(2m) time because we must search two vectors(one in each target node)to remove an item. Even in the case where nothing is removed, the 
            function runs in O(m) time.
3. getCost - This is O(m) time because we only have to search 1 vector in 1 node.

TODO

#### 3. Exercise 12.1 from http://opendatastructures.org/ods-cpp/12_4_Discussion_Exercises.html. You may want to draw by hand, upload the picture online (Instagram, Twitter, imgur, or some place like that), and then just put a link here.
//TODO!!!!!!
#### 4. What is one question that confused you about this exercise, or one piece of advice you would share with students next semester?
Think before you code! You are only adding Edges, not nodes or graphs. Therefore, you only need to update two vectors.
