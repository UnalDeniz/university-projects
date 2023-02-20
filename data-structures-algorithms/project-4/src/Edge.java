/**
 * Edges connect the vertices.
 * Each edge has a maximum capacity of gifts that can be distributed from that edge.
 * @author Deniz Ünal
 *
 */
public class Edge {
	/**
	 * The number of gifts that are currently distributed from this edge.
	 */
	public int currentFlow = 0;
	public int remainingCapacity;
	
	final public Vertice startingPoint;
	final public Vertice endPoint;
	
	public Edge(int capacity, Vertice endpoint, Vertice startpoint) {
		remainingCapacity = capacity;
		this.endPoint = endpoint;
		this.startingPoint = startpoint;
	}

}
