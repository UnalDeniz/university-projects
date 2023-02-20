/**
 * ExitEvent is the process of exiting from a service.
 * Holds information regarding exit such as the player, time and the session.
 * @author Deniz Ünal
 *
 */
public class ExitEvent extends Event {
	/**
	 * The service session that the player will exit from.
	 */
	final private Session session;
	
	public ExitEvent(Player player, double time, Session session, String type) {
		super(player, time, type);
		this.session = session;
	}
	/**
	 * Carries out the processes that should happen when a player exits from a service.
	 * Makes the player and the staff for the session available, creates an physiotherapy 
	 * request for the players that exit from training sessions and starts next sessions 
	 * if there is any requests from players and necessary staff for it.
	 */
	public void initializeEvent() {
		Event.currentTime = time;
		player.busy = false;
		
		if(type.equals("t")) {
			TrainingCoach.getTrainingCoaches().add((TrainingCoach) session.staff);
			player.lastTrainingDuration = session.duration;
			Event.getEvents().add(new StartEvent(player, time, time, "p"));
		} else if(type.equals("p")) {
			Physiotherapist.getPhysiotherapists().add((Physiotherapist) session.staff);
		} else if(type.equals("m")) {
			Masseur.getMasseurs().add((Masseur) session.staff);
		}	
		
		Session.startSessions();
	}

}
