# mai

A graph oriented C++ computing engine which
* allows user to form ideas into a graph, with node pointing to STL resources.
* performs calculation in process, but also persist/recover data to/from disk asynchronously.

Everything is in the graph.

\* **mai** refers to 脉. 


###Design Note
- `Context` - maintain a hash of resources.
- `Graph` - keeps a dynamic cache of nodes and provides calculation shortcuts.