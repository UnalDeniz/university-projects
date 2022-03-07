import java.util.ArrayList;
/**
 * Sessions are the processes that the players will get their services.
 * Holds informations about the session such as the staff that will handle the session and duration.
 * @author Deniz Ünal
 *
 */
public class Session {
	
	final public Player player;
	final public double duration;
	final public Staff staff;
	
	private static ArrayList<Session> trainingSessions = new ArrayList<Session>();
	private static ArrayList<Session> physiotherapySessions = new ArrayList<Session>();
	private static ArrayList<Session> massageSessions = new ArrayList<Session>();
	
	public Session(Player player, double duration, Staff staff) {
		this.player = player;
		this.duration = duration;
		this.staff = staff;
	}
	/**
	 * Starts new sessions if there is any requests from players and necessary staff for it.
	 */
	public static void startSessions() {
		while(!Player.getQueue("t").isEmpty() && !TrainingCoach.getTrainingCoaches().isEmpty()) {
			Player player = Player.getQueue("t").poll();
			player.increaseSpentTime(Event.currentTime - player.queueEntryTime, "t");
			TrainingCoach coach = TrainingCoach.getTrainingCoaches().poll();
			Session session = new Session(player, player.nextSessionDuration, coach);
			trainingSessions.add(session);
			Event.getEvents().add(new ExitEvent(player, Event.currentTime + player.nextSessionDuration, session, "t"));
		}
		
		while(!Player.getQueue("p").isEmpty() && !Physiotherapist.getPhysiotherapists().isEmpty()) {
			Player player = Player.getQueue("p").poll();
			player.increaseSpentTime(Event.currentTime - player.queueEntryTime, "p");
			Physiotherapist physiotherapist = Physiotherapist.getPhysiotherapists().poll();
			Session session = new Session(player, physiotherapist.serviceTime, physiotherapist);
			physiotherapySessions.add(session);
			Event.getEvents().add(new ExitEvent(player, Event.currentTime + physiotherapist.serviceTime, session, "p"));
		}
		
		while(!Player.getQueue("m").isEmpty() && !Masseur.getMasseurs().isEmpty()) {
			Player player = Player.getQueue("m").poll();
			player.increaseSpentTime(Event.currentTime - player.queueEntryTime, "m");
			Masseur masseur = Masseur.getMasseurs().poll();
			Session session = new Session(player, player.nextSessionDuration, masseur);
			massageSessions.add(session);
			Event.getEvents().add(new ExitEvent(player, Event.currentTime + player.nextSessionDuration, session, "m"));
		}
		
	}
	/**
	 * Average session time is calculated by summing all the session durations and dividing it by the session count.
	 * @param type shows if the session time is for the massage, training or the physiotherapy service
	 * @return average session time for a particular service
	 */
	public static double getAverageSessionTime(String type) {
		double totalSessionTime = 0;
		if(type.equals("t")) {
			for(Session t: trainingSessions)
				totalSessionTime += t.duration;
			if(trainingSessions.size() == 0)
				return 0;
			return totalSessionTime / trainingSessions.size();
		} else if(type.equals("p")) {
			for(Session p: physiotherapySessions)
				totalSessionTime += p.duration;
			if(physiotherapySessions.size() == 0)
				return 0;
			return totalSessionTime / physiotherapySessions.size();
		} else {
			for(Session m: massageSessions)
				totalSessionTime += m.duration;
			if(massageSessions.size() == 0)
				return 0;
			return totalSessionTime / massageSessions.size();
		}
	}
}
