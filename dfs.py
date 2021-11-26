# P
# 
# 
# ython3 implementation of the approach
adj = [[0,1,1,0,0,1,0],[1,0,0,1,1,1,0],[1,0,0,1,1,0,1],[0,1,1,0,1,0,0],[0,1,1,1,0,0,1],[1,1,0,0,0,0,0],[0,0,1,0,1,0,0]]

# using datetime module
import datetime;
  
# ct stores current time
ct = datetime.datetime.now()
print("current time:-", ct)
  
# ts store timestamp of current time
ts = ct.timestamp()

class Graph:
	


	# Function to fill empty adjacency matrix
	def __init__(self, v, e):
		
		self.v = v
		self.e = e
		Graph.adj = [[0 for i in range(v)]
						for j in range(v)]

	# Function to add an edge to the graph
	def addEdge(self, start, e):
		
		# Considering a bidirectional edge
		Graph.adj[start][e] = 1
		Graph.adj[e][start] = 1

	# Function to perform DFS on the graph
	def DFS(self, start, visited):
		
		# Print current node
		curr_ts = datetime.datetime.now().timestamp()
		print(start, end = ' ')
		print(str(curr_ts-ts))

		# Set current node as visited
		visited[start] = True

		# For every node of the graph
		for i in range(self.v):
			
			# If some node is adjacent to the
			# current node and it has not
			# already been visited
			if (Graph.adj[start][i] == 1 and
					(not visited[i])):
				self.DFS(i, visited)

# Driver code
v, e = 8, 12

# Create the graph
G = Graph(v, e)
G.addEdge(1, 2)
G.addEdge(1, 3)
G.addEdge(3, 7)
G.addEdge(7, 5)
G.addEdge(5, 4)
G.addEdge(3, 4)
G.addEdge(1, 6)
G.addEdge(6, 2)
G.addEdge(2, 5)
G.addEdge(5, 3)
G.addEdge(5, 7)

# Visited vector to so that a vertex
# is not visited more than once
# Initializing the vector to false as no
# vertex is visited at the beginning
visited = [False] * v

# Perform DFS
G.DFS(1, visited);

# This code is contributed by ng24_7

