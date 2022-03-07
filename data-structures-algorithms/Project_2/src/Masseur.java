import java.util.PriorityQueue;
/**
 * Masseurs are the staff members that handle the massage sessions.
 * @author Deniz Ünal
 *
 */
public class Masseur extends Staff {

    private static PriorityQueue<Masseur> masseurs = new PriorityQueue<Masseur>();
	  
    public Masseur(int id) {
		super(id);
	}
  
	public static PriorityQueue<Masseur> getMasseurs(){
	  return masseurs;
	}
}
