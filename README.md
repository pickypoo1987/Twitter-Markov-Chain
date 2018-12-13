# Markov-Chain Random Tweet Generator:

![Andrey Markov](https://upload.wikimedia.org/wikipedia/commons/7/70/AAMarkov.jpg)

## Markov Chains

**Andrey Markov:**

The mathematician behind Markov chains.

**Definition:**
> A stochastic model describing a sequence of possible events in which the probability of each event depends only on the state attained in the previous event

***

Lets break that down a little bit...

In short, a stochastic model is a model that is randomly determined, and cannot be precisely predicted.

So in other words, this model predicts a 'path' of random events, and this path is only dependent on what we encountered last.

Wherever we are currently, determines where we go next. And so on and so forth...

However, I've only been describing a first-order Markov chain. We can increase the complexity!

Now, I must introduce nth ordered Markov chains. When we have a 2nd order chain, we take the last two states into account. In a 3rd order chain, we consider the previous three states. Whatever 'n' is, we consider that many previous states. This can strengthen our model greatly in most circumstances.

***
**Relevant applications for Markov-Chains:**

Language processing (NLP):
* Twitter Tweet-Bot
* Texting app word completion
* Support Chat-Bots
* Random Essay Generator? (*prolly not... :/*)

Other uses:
* Modeling many real world scenarios that can be described with probabilities
  * Financial markets
  * Gene synthesizing

Okay, enough of that... Now to the data structures that I used!

***

## Data Structures

***

### Graph:
I built a graph sorta similar to this one...

![Word Graph](https://i.stack.imgur.com/1mbny.png)

This is the main data structure utilized for almost any application of Markov chains. It's relatively simple to store multiple 'states' in the vertices, and weight the edges in a specific way.

For me, each vertex in the graph holds a

```cpp
struct WordVertex;
```
*among other things...* each `WordVertex` contains an adjacency matrix of

```cpp
struct WordEdge;
```

I implemented different 'levels' of edges, and then these edges were also weighted.
***
**e.g.**

> I like all food...

**I** *'s* adjacency list looks like this:
1. like (weight = 1)
2. all (weight = 1)
3. food (weight = 1)
4. ... (weight = 1)

***

### Hash Table:
I used a hash table to store the word vertices...

I did this so it would be quick to go from vertex to vertex.

My hash function was the **DJB2** algorithm from assignment #7, and I used **chaining** with **linked-lists** to deal with collisions.

```cpp
/* DJB2 Hash Function */
int hashFunc(string word) {
  int hash = 5381;
  for (auto character : word) {
    hash = (hash * 33) + character;
  }
  hash = hash % hashTableSize;
  if (hash < 0) {
    hash += hashTableSize;
  }
  return hash;
}
```

My hash table would look something like this:

![hash-table](https://he-s3.s3.amazonaws.com/media/uploads/0e2c706.png)

***

### Queues
Queues were important when developing my Markov Chain algorithm to store the specified number of words in the correct order. For example, if I'm running a 3rd order Markov chain on some text, the last three words are in the queue in reverse order...

***
**e.g.**
> I would love to buy a new computer!

If we're only dealing with one sentence, my Markov chain algorithm would produce:

>I would like

our 3rd order Markov chain would produce the following queue:


| love | would | I |
|:-----|:------|:--|
|0|1|2|

then, my algorithm gives us

> to

so the sentence becomes:

> I would love to

the queue would become:

| to | love | would |
|:-----|:------|:--|
|0|1|2|

***

### Vector (Resizable Array):
I used vectors to:

1. store the adjacency matrix of the edges in each word vertex.
2. store the contents of the tweets taken from a file. The file's contents are tokenized and added to the vector.
3. store all of the words that started a sentence in the file.
4. store the contents of the 'message' when the Markov Chain is going along its path.
5. complete other various tasks where indexing and iteration were important.

Basically, as you can see, vectors were crucial to almost every aspect of my program.

***

### Struct:

I used a lot of structs as well...
```cpp
struct {};
```

I used them for structuring certain data together in a logical format.

***

## Challenges
1. Building my graph perfectly
   - Vertices
   - Edges
2. Developing an algorithm for scraping all of the useful information from the text file
   - The struggle was real coming up with an efficient solution...
3. Adding nuanced changes to my code to try to mimic human generated text
   - Capitalization
   - Punctuation

***

## Program Notes:
Currently, my program goes out, gets Tweets from a specified user. Then it writes those tweets to a file, and calls the C++ to run on that file. After the C++ has interacted with the file and creates the graph, the user can prompt a random Tweet to be generated.

1. It works better with a smaller number of tweets collected... (This shouldn't necessarily be the case :/)
2. I am currently working on perfecting the GUI version
   * Making it look more appealing
   * Making it run better (not getting hung)
3. I am also currently working on turning the CLI version into an executable so it can be run on any machine.

***

## Next Steps

- Making my GUI work perfectly, and have an appealing design
- Looking at ways to optimize the C++

***
