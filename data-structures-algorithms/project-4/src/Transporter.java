import java.util.ArrayList;
/**
 * Transporters carries the gifts to the sink.
 * They are grouped by their type (train or a deer) and by their destination
 * (green region or red region)
 * @author Deniz Ünal
 *
 */
public class Transporter extends Vertice {
	/**
	 * The total number of gifts a transporter can carry.
	 */
	final public int capacity;
	
	static private ArrayList<Transporter> redRegionTrains = new ArrayList<>();
	static private ArrayList<Transporter> greenRegionTrains = new ArrayList<>();
	static private ArrayList<Transporter> redRegionDeers = new ArrayList<>();
	static private ArrayList<Transporter> greenRegionDeers = new ArrayList<>();
	/**
	 * This arraylist contains all transporters regardless of their classification.
	 */
	static private ArrayList<Transporter> transporters =new ArrayList<>();
	
	public Transporter(int capacity) {
		this.capacity = capacity;
	}

	public static ArrayList<Transporter> getGreenRegionTrains() {
		return greenRegionTrains;
	}

	public static ArrayList<Transporter> getRedRegionTrains() {
		return redRegionTrains;
	}

	public static ArrayList<Transporter> getRedRegionDeers() {
		return redRegionDeers;
	}

	public static ArrayList<Transporter> getGreenRegionDeers() {
		return greenRegionDeers;
	}

	public static ArrayList<Transporter> getTransporters() {
		return transporters;
	}
}
