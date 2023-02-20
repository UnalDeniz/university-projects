import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Scanner;

/**
 * Main class takes the input from a file and prints the shortest path and tax cost to the output file. 
 * @author Deniz Ünal
 *
 */
public class project3main {

	/**
	 * Main method takes the input from a file and prints the shortest path and tax cost to the output file. 
	 * @param args input file, output file
	 */
	public static void main(String[] args) throws FileNotFoundException {
		File input = new File(args[0]);
		File output = new File(args[1]);
		
		Scanner in = new Scanner(input);
		PrintStream out = new PrintStream(output);
		
		int timeLimit = in.nextInt();
		int cityCount = in.nextInt();
		
		City.mecnunCityName = in.next();
		City.leylaCityName = in.next();
		in.nextLine();		
		for(int i = 0; i < cityCount; i++) {
			String line = in.nextLine();
			String[] lineArray = line.split(" ");
			ArrayList<String> lineList = new ArrayList<String>();
			for(String s:lineArray) {
				lineList.add(s);
			}
			City city = new City(lineList.get(0));
			if(lineList.get(0).charAt(0) == 'c')
				City.cCities.add(city);
			else
				City.dCities.add(city);
			for(int j = 1; j < lineList.size(); j+=2) {
				if(!lineList.get(0).equals(lineList.get(j)))
					city.outgoingRoads.add(new Road(lineList.get(j), Integer.parseInt(lineList.get(j+1))));
			}
		}
		/*
		 * Since Leyla and Mecnun travels by foot at the left side of the country, roads are made two way with this loop.
		 */
		for(City d: City.dCities) {
			for(Road r: d.outgoingRoads) {
				City destination;
				if(r.destination.charAt(0) == 'c')
					destination = City.cCities.get(Integer.parseInt(r.destination.substring(1))-1);
				else 
					destination = City.dCities.get(Integer.parseInt(r.destination.substring(1))-1);
				destination.outgoingRoads.add(new Road(d.name, r.length));
			}
		}
		
		out.println(City.returnRoadToLeyla());
		out.print(City.returnHoneymoonCost(timeLimit));
		
		in.close();
		out.close();
	}

}
