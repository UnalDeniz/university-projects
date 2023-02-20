import java.util.ArrayDeque;
import java.util.ArrayList;
/**
 * Graph is the class that the operations regarding the graph is made.
 * @author Deniz Ünal
 *
 */
abstract public class Graph {
	/**
	 * santa is an imaginary vertice that is created to use as a source for the max-flow problem.
	 */
	static private Vertice santa;
	/**
	 * regions is an imaginary vertice that is created to use as a sink for the max-flow problem.
	 */
	static private Vertice regions;
	/**
	 * This method combines the bags that has the same restrictions.
	 * The bags with the restriction "a" is not combined.
	 * This is done as a optimization so that the number of edges and the vertices in the graph is reduced.
	 */
	static public void combineBags() {
		ArrayList<Bag> combinedBags = new ArrayList<>();
		ArrayList<String> previousTypes = new ArrayList<>();
		boolean noMoreBags = false;
		String type = "";
		while(true) {
			int giftCount = 0;
			noMoreBags = true;
			for(Bag b: Bag.getBags()) {
				if(!b.bagType.contains("a") && !previousTypes.contains(b.bagType)) {
					type = b.bagType;
					previousTypes.add(type);
					noMoreBags = false;
					break;
				}
			}
			if(noMoreBags)
				break;
			for(Bag b: Bag.getBags()) {
				if(b.bagType.equals(type)) {
					giftCount += b.giftCount;
				}
			}
			combinedBags.add(new Bag(giftCount, type));
		}
		for(Bag b: Bag.getBags()) {
			if(b.bagType.contains("a")) {
				combinedBags.add(b);
			}
		}
		Bag.getBags().clear();
		Bag.getBags().addAll(combinedBags);
	}
	/**
	 * This method creates the edges between vertices.
	 */
	static public void construct() {
		santa = new Vertice();
		regions = new Vertice();
		
		for(Bag b: Bag.getBags()) {
			santa.getOutgoingEdges().add(new Edge(b.giftCount, b, santa));
			
			if(!b.bagType.contains("c")){
				if(!b.bagType.contains("e")) {
					if(b.bagType.contains("a")) {
					for(Transporter t: Transporter.getGreenRegionTrains()) {
							b.getOutgoingEdges().add(new Edge(1, t, b));
						}	
					} else {
						for(Transporter t: Transporter.getGreenRegionTrains()) {
							b.getOutgoingEdges().add(new Edge(t.capacity, t, b));
						}
					}
				} 
				if(!b.bagType.contains("d")) {
					if(b.bagType.contains("a")) {
						for(Transporter t: Transporter.getGreenRegionDeers()) {
							b.getOutgoingEdges().add(new Edge(1, t, b));
						}	
					} else {
						for(Transporter t: Transporter.getGreenRegionDeers()) {
							b.getOutgoingEdges().add(new Edge(t.capacity, t, b));
						}
					}
				}
			}
			if(!b.bagType.contains("b")) {
				if(!b.bagType.contains("e")) {
					if(b.bagType.contains("a")) {
						for(Transporter t: Transporter.getRedRegionTrains()) {
							b.getOutgoingEdges().add(new Edge(1, t, b));
						}	
					} else {
						for(Transporter t: Transporter.getRedRegionTrains()) {
							b.getOutgoingEdges().add(new Edge(t.capacity, t, b));
						}
					}
				} 
				if(!b.bagType.contains("d")) {
					if(b.bagType.contains("a")) {
						for(Transporter t: Transporter.getRedRegionDeers()) {
							b.getOutgoingEdges().add(new Edge(1, t, b));
						}	
					} else {
						for(Transporter t: Transporter.getRedRegionDeers()) {
							b.getOutgoingEdges().add(new Edge(t.capacity, t, b));
						}
					}
				}
			}
		}
		
		for(Transporter t: Transporter.getTransporters()) {
			t.getOutgoingEdges().add(new Edge(t.capacity, regions, t));
		}
	}
	/**
	 * This method implements the Ford-Fulkerson algorithm to solve max-flow problem. 
	 * @return max-flow of the graph.
	 */
	static public int findMaxFlow() {
		ArrayDeque<Vertice> vertices = new ArrayDeque<Vertice>();
		ArrayList<Edge> path = new ArrayList<Edge>();
		ArrayList<Vertice> deadEnds = new ArrayList<Vertice>();
		vertices.add(santa);
		int lowestCapacityInPath = Integer.MAX_VALUE;
		
		while(!vertices.isEmpty()) {
			Vertice currentVertice = vertices.poll();
			if(currentVertice.equals(regions)) {
				vertices.add(santa);
				for(Edge e:path) {
					if(e.remainingCapacity < lowestCapacityInPath)
						lowestCapacityInPath = e.remainingCapacity;
				}
				for(Edge e: path) {
					if(e.endPoint.getOutgoingEdges().size() == 0) {
						e.endPoint.getOutgoingEdges().add(new Edge(lowestCapacityInPath, e.startingPoint, e.endPoint));
					}
					else if(e.endPoint.getOutgoingEdges().get(e.endPoint.getOutgoingEdges().size()-1).endPoint.equals(e.startingPoint)){
						e.endPoint.getOutgoingEdges().get(e.endPoint.getOutgoingEdges().size()-1).remainingCapacity += lowestCapacityInPath;
					} else {
						e.endPoint.getOutgoingEdges().add(new Edge(lowestCapacityInPath, e.startingPoint, e.endPoint));	
					}
					e.currentFlow += lowestCapacityInPath;
					e.remainingCapacity -= lowestCapacityInPath;
					e.startingPoint.visited = false;
				}
				for(Vertice v: deadEnds)
					v.visited = false;
				deadEnds.clear();
				path.clear();
				lowestCapacityInPath = Integer.MAX_VALUE;
				continue;
			}
			currentVertice.visited = true;
			boolean foundAWay = false;
			for(Edge e: currentVertice.getOutgoingEdges()) {
				if(e.remainingCapacity != 0 && !e.endPoint.visited) {
					foundAWay = true;
					vertices.add(e.endPoint);
					path.add(e);
					break;
				}	
			}
			if(!foundAWay && path.size() != 0) {
				deadEnds.add(currentVertice);
				vertices.add(path.get(path.size()-1).startingPoint);
				path.remove(path.size()-1);
			}
		}
		
		int maxFlow = 0;
		for(Edge e: santa.getOutgoingEdges()) {
			maxFlow += e.currentFlow;
		}
		
		for(Bag b: Bag.getBags()) {
			for(Edge e: b.getOutgoingEdges()) {
				if(e.endPoint.equals(santa))
					maxFlow -= e.currentFlow;
			}
		}
		
		return maxFlow;
	}
}
