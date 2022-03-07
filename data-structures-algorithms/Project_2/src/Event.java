import java.util.PriorityQueue;
/**
 * Events are the processes of arriving to a service or exiting from one.
 * Holds information regarding event such as player and time.
 * @author Deniz Ünal
 *
 */
public abstract class Event implements Comparable<Event> {

  final public Player player;

  final public double time;
  /**
   * Shows that if the service for the event is training, physiotherapy or massage.
   */
  final public String type;
  
  public static double currentTime;
  
  private static PriorityQueue<Event> events = new PriorityQueue<Event>();

  public Event(Player player, double time, String type){
    this.time = time;
    this.player = player;
    this.type = type;
  }
  /**
   * Carries out the processes that should happen in the event time.
   */
  public abstract void initializeEvent();
  /**
   * The events are ordered so that the event with the smallest time will happen first.
   * If the times of the events are equal, the event with the lowest player id will happen first.
   */
  public int compareTo(Event other) {
		if(this.time > other.time)
			return 1;
		else if(this.time < other.time)
			return -1;
		else
			return this.player.id - other.player.id;
  }
  
  public static PriorityQueue<Event> getEvents(){
	  return events;
  }

}
