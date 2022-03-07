
//DO_NOT_EDIT_ANYTHING_ABOVE_THIS_LINE

package main;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Scanner;

import containers.*;
import ports.Port;
import ships.Ship;
	/**
	 * This class will read instructions from the file such as port, container, ship creation 
	 * or refueling, sailing, loading containers on the ship. After reading the instructions it will 
	 * print informations about ships and ports to another file.
	 * @author deniz ünal
	 *
	 */
public class Main {
	/**
	 * This method will read instructions from the file such as port, container, ship creation 
	 * or refueling, sailing, loading containers on the ship. After reading the instructions it will 
	 * print informations about ships and ports to another file.
	 * @param args input file, output file.
	 * @throws FileNotFoundException
	 */
	public static void main(String[] args) throws FileNotFoundException {
		
		//
		// Main receives two arguments: path to input file and path to output file.
		// You can assume that they will always be provided, so no need to check them.
		// Scanner and PrintStream are already defined for you.
		// Use them to read input and write output.
		// 
		// Good Luck!
		// 
		
		Scanner in = new Scanner(new File(args[0]));
		PrintStream out = new PrintStream(new File(args[1]));
		
		
		ArrayList<Container> containers = new ArrayList<Container>();
		ArrayList<Port> ports = new ArrayList<Port>();
		ArrayList<Ship> ships = new ArrayList<Ship>();
		
		int N = in.nextInt();
		
		int nextContainerID = 0;
		int nextShipID = 0;
		int nextPortID = 0;
		
		for(int i = 0; i < N; i++) {
			int nextEvent = in.nextInt();
			
			if(nextEvent == 1) {
				int portID = in.nextInt();
				int weight = in.nextInt();
				if(in.hasNext("L")) {
					in.next();
					containers.add(new LiquidContainer(nextContainerID, weight));
				} else if(in.hasNext("R")){
					in.next();
					containers.add(new RefrigeratedContainer(nextContainerID, weight));
				} else if(weight > 3000) {
					containers.add(new HeavyContainer(nextContainerID, weight));
				} else {
					containers.add(new BasicContainer(nextContainerID, weight));
				}
				
				ports.get(portID).getContainers().add(containers.get(nextContainerID));
				nextContainerID++;
			} 
			
			else if(nextEvent == 2){
				int portID = in.nextInt();
				int maxContainerWeight = in.nextInt();
				int maxContainerCount = in.nextInt();
				int maxHeavyCount = in.nextInt();
				int maxRefrigeratedCount = in.nextInt();
				int maxLiquidCount = in.nextInt();
				double fuelConsumption = in.nextDouble();
				ships.add(new Ship(nextShipID,ports.get(portID),maxContainerWeight,maxContainerCount,maxHeavyCount,
						maxRefrigeratedCount,maxLiquidCount,fuelConsumption));
				nextShipID++;
			}
			
			else if(nextEvent == 3) {
				double X = in.nextDouble();
				double Y = in.nextDouble();
				ports.add(new Port(nextPortID, X, Y));
				nextPortID++;
			}
			
			else if(nextEvent == 4) {
				int shipID = in.nextInt();
				int containerID = in.nextInt();
				ships.get(shipID).load(containers.get(containerID));
			}
			
			else if(nextEvent == 5) {
				int shipID = in.nextInt();
				int containerID = in.nextInt();
				ships.get(shipID).unLoad(containers.get(containerID));
			}
			
			else if(nextEvent == 6) {
				int shipID = in.nextInt();
				int portID = in.nextInt();
				ships.get(shipID).sailTo(ports.get(portID));
			}
			
			else if(nextEvent == 7) {
				int shipID = in.nextInt();
				double fuel = in.nextDouble();
				ships.get(shipID).reFuel(fuel);
			}
		}
		
		for(Port p:ports) {
			out.println("Port "+ports.indexOf(p)+": " + p.getCoordinates());
			if(p.getBasicContainers().size() > 0) {
				out.print("  BasicContainer:");
				for(Container c:p.getBasicContainers()) {
					out.print(" "+c.getID());
				}
				out.println();
			}
			if(p.getOnlyHeavyContainers().size() > 0) {
				out.print("  HeavyContainer:");
				for(Container c:p.getOnlyHeavyContainers()) {
					out.print(" "+c.getID());
				}
				out.println();
			}
			if(p.getRefrigeratedContainers().size() > 0) {
				out.print("  RefrigeratedContainer:");
				for(Container c:p.getRefrigeratedContainers()) {
					out.print(" "+c.getID());
				}
				out.println();
			}
			if(p.getLiquidContainers().size() > 0) {
				out.print("  LiquidContainer:");
				for(Container c:p.getLiquidContainers()) {
					out.print(" "+c.getID());
				}
				out.println();
			}
			
			for(Ship s:p.getCurrent()) {
				out.println("  Ship "+s.getID()+": "+s.getFuel());
				if(s.getBasicContainers().size() > 0) {
					out.print("    BasicContainer:");
					for(Container c:s.getBasicContainers()) {
						out.print(" "+c.getID());
					}
					out.println();
				}
				if(s.getOnlyHeavyContainers().size() > 0){
					out.print("    HeavyContainer:");
					for(Container c:s.getOnlyHeavyContainers()) {
						out.print(" "+c.getID());
					}
					out.println();
				}
				if(s.getRefrigeratedContainers().size() > 0){
					out.print("    RefrigeratedContainer:");
					for(Container c:s.getRefrigeratedContainers()) {
						out.print(" "+c.getID());
					}
					out.println();
				}
				if(s.getLiquidContainers().size() > 0){
					out.print("    LiquidContainer:");
					for(Container c:s.getLiquidContainers()) {
						out.print(" "+c.getID());
					}
					out.println();
				}
			}
			
		}
		
		
		in.close();
		out.close();
	}
}



//DO_NOT_EDIT_ANYTHING_BELOW_THIS_LINE

