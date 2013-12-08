Author
==========
"Proctor, Patrick", proctopj
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

1. add - This is functioning perfectly.
2. remove - This is functioning perfectly.
3. getCost - This is functioning perfectly.

#### 2. For each of your methods, what is the worst-case running time? You may write your answer in terms of `n` (the number of vertices), `m` (the number of edges), `d` (the maximum degree of any node in the graph), or any combination of these. Try to give the most informative bound that you can.

1. add - This runs in O(d1 + d2) where each d is for each node in an edge. This is because the vectors resize with each addition
2. remove - This runs in O(1) because the vectors need not resize upon a removal of an edge
3. getCost - This also runs in O(1) because vectors can be accessed in constant time, and node numbers are implicit.

TODO

#### 3. Exercise 12.1 from http://opendatastructures.org/ods-cpp/12_4_Discussion_Exercises.html. You may want to draw by hand, upload the picture online (Instagram, Twitter, imgur, or some place like that), and then just put a link here.

This is provided in the jpg file in my repo.

#### 4. What is one question that confused you about this exercise, or one piece of advice you would share with students next semester?

This Lab is easy because of its simplicity, but you need to do either Vise or expand the parameters of this lab in order to fulfill your graph algorithms requirement.