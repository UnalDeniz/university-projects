import java.util.ArrayList;
/**
 * Bags holds the gifts before they are distributed.
 * Each bag has its restrictions regarding the distribution of gifts.
 * @author Deniz Ünal
 *
 */
public class Bag extends Vertice{
	
	final public int giftCount;
	/**
	 * The restrictions regarding the distribution of gifts.
	 */
	final public String bagType;
	
	static private ArrayList<Bag> bags = new ArrayList<Bag>();
	
	public Bag(int giftCount, String type) {
		this.giftCount = giftCount;
		bagType = type;
	}

	public static ArrayList<Bag> getBags() {
		return bags;
	}

}
