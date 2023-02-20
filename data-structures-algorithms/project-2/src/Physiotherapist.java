import java.util.PriorityQueue;
/**
 * Physiotherapists are the staff members that handle the physiotherapy sessions.
 * Each of them have their personal service time.
 * @author Deniz Ünal
 *
 */
public class Physiotherapist extends Staff {

  final public double serviceTime;

  private static PriorityQueue<Physiotherapist> pyhsiotherapists = new PriorityQueue<Physiotherapist>();

  public Physiotherapist(int id, double serviceTime){
	super(id);
    this.serviceTime = serviceTime;
  }
  
  public static PriorityQueue<Physiotherapist> getPhysiotherapists(){
	  return pyhsiotherapists;
  }

}
